#include "mandelbrot.h"

MandelbrotWidget::MandelbrotWidget(double real, double imag, double xmin, double xmax, double ymin, double ymax, int maxIterations, QWidget *parent)
    : QWidget(parent) {
    this->real = real;
    this->imag = imag;
    this->xmin = xmin;
    this->xmax = xmax;
    this->ymin = ymin;
    this->ymax = ymax;
    this->zoomFactor = 0.51;
    this->maxIterations = maxIterations;
    setFixedSize(1000, 800);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

MandelbrotWidget::~MandelbrotWidget() {}

void MandelbrotWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QImage mandelbrotImage = generateFractal(real, imag, xmin, xmax, ymin, ymax, width(), height(), maxIterations);

    painter.drawImage(0, 0, mandelbrotImage);
}

void MandelbrotWidget::wheelEvent(QWheelEvent *event) {
    QPoint pos = event->pos();
    int mouseX = pos.x();
    int mouseY = pos.y();

    double scaleFactor = (event->angleDelta().y() > 0) ? 1.1 : 0.9;
    double zoom = zoomFactor * scaleFactor;

    double dx = (xmax - xmin) * (1.0 / zoom - 1.0) / 2.0;
    double dy = (ymax - ymin) * (1.0 / zoom - 1.0) / 2.0;

    double relativeX = static_cast<double>(mouseX) / width();
    double relativeY = static_cast<double>(mouseY) / height();

    double centerX = xmin + (xmax - xmin) * relativeX;
    double centerY = ymin + (ymax - ymin) * relativeY;
    xmin = centerX - dx;
    xmax = centerX + dx;
    ymin = centerY - dy;
    ymax = centerY + dy;

    update();
    event->accept();
}

QImage MandelbrotWidget::generateFractal(double pReal, double pImag, double xmin, double xmax, double ymin, double ymax, int width, int height, int maxIterations) {
    QImage image(width, height, QImage::Format_RGB32);

    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    int rowsPerThread = height / numThreads;

    auto workerFunction = [&](int startRow, int endRow) {
        for (int y = startRow; y < endRow; ++y) {
            for (int x = 0; x < width; ++x) {
                double real = xmin + (xmax - xmin) * x / (width - 1);
                double imag = ymin + (ymax - ymin) * y / (height - 1);
                std::complex<double> z(0, 0), c(real, imag), p(pReal, pImag);
                int iterations = 0;

                while (abs(z) < 2.0 && iterations < maxIterations) {
                    if (pReal == 2.0 && pImag == 0.0) {
                        z = z * z + c;
                    }   else z = pow(z, p) + c;
                    ++iterations;
                }

                QColor color = colorForIterations(iterations, maxIterations);
                image.setPixelColor(x, y, color);
            }
        }
    };

    for (int i = 0; i < numThreads - 1; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i + 1) * rowsPerThread;
        threads.emplace_back(workerFunction, startRow, endRow);
    }
    threads.emplace_back(workerFunction, (numThreads - 1) * rowsPerThread, height);

    for (auto& thread : threads) {
        thread.join();
    }

    return image;
}

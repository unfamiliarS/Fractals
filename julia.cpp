#include "julia.h"

JuliaWidget::JuliaWidget(double real, double imag, double xmin, double xmax, double ymin, double ymax, int maxIterations, QWidget *parent)
    : QWidget(parent), real(real), imag(imag), xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax), zoomFactor(0.51), maxIterations(maxIterations) {
    setFixedSize(1000, 800);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

void JuliaWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Генерируем изображение фрактала Мандельброта
    QImage juliaImage = generateFractal(real, imag, xmin, xmax, ymin, ymax, width(), height(), maxIterations);

    // Рисуем изображение на виджете
    painter.drawImage(0, 0, juliaImage);
}

void JuliaWidget::wheelEvent(QWheelEvent *event) {
    // Получаем позицию курсора мыши в координатах виджета
    QPoint pos = event->pos();
    int mouseX = pos.x();
    int mouseY = pos.y();

    double scaleFactor = (event->angleDelta().y() > 0) ? 1.1 : 0.9;
    double zoom = zoomFactor * scaleFactor;

    // Обновляем границы фрактала и перерисовываем его
    double dx = (xmax - xmin) * (1.0 / zoom - 1.0) / 2.0;
    double dy = (ymax - ymin) * (1.0 / zoom - 1.0) / 2.0;

    // Вычисляем позицию курсора относительно размеров виджета
    double relativeX = static_cast<double>(mouseX) / width();
    double relativeY = static_cast<double>(mouseY) / height();

    // Вычисляем новые границы фрактала с учетом позиции курсора
    double centerX = xmin + (xmax - xmin) * relativeX;
    double centerY = ymin + (ymax - ymin) * relativeY;
    xmin = centerX - dx;
    xmax = centerX + dx;
    ymin = centerY - dy;
    ymax = centerY + dy;

    update();
    event->accept(); // Принимаем событие, чтобы оно не распространялось дальше
}

QImage JuliaWidget::generateFractal(double cReal, double cImag, double xmin, double xmax, double ymin, double ymax, int width, int height, int maxIterations) {
    QImage image(width, height, QImage::Format_RGB32);

    const int numThreads = std::thread::hardware_concurrency();

    // Функция для вычисления значений пикселей в заданной строке
    auto computePixelsInRow = [&](int startRow, int endRow) {
        for (int y = startRow; y < endRow; ++y) {
            for (int x = 0; x < width; ++x) {
                std::complex<double> z, c;
                double dx = (xmax - xmin) / width;
                double dy = (ymax - ymin) / height;

                c.real(cReal);
                c.imag(cImag);

                z.real(xmin + x * dx);
                z.imag(ymin + y * dy); // Преобразование экранных координат в комплексные

                int iterations = 0;
                while (iterations < maxIterations && abs(z) < 2) {
                    z = z * z + c;
                    ++iterations;
                }

                QColor color = colorForIterations(iterations, maxIterations);
                image.setPixelColor(x, y, color);
            }
        }
    };

    // Создание и запуск потоков
    std::vector<std::thread> threads;
    int rowsPerThread = height / numThreads;

    for (int i = 0; i < numThreads - 1; ++i) {
        int startRow = i * rowsPerThread;
        int endRow = (i + 1) * rowsPerThread;
        threads.emplace_back(computePixelsInRow, startRow, endRow);
    }
    threads.emplace_back(computePixelsInRow, (numThreads - 1) * rowsPerThread, height);

    // Ожидание завершения всех потоков
    for (auto& thread : threads) {
        thread.join();
    }

    return image;
}

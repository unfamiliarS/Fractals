#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->mandelbrot, &QPushButton::clicked, this, &MainWindow::onCreateMandelbrotFractalButtonClicked);
    connect(ui->julia, &QPushButton::clicked, this, &MainWindow::onCreateJuliaFractalButtonClicked);
    connect(&settingsDialog, &Setting::appliedParameters, this, &MainWindow::useEmitParameters);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCreateJuliaFractalButtonClicked() {
    lastFractalType = Julia;
    defaultReal = 0.38;
    defaultImg = 0.25;
    defaultXmin = -1.5;
    defaultXmax = 1.5;
    defaultYmin = -1.5;
    defaultYmax = 1.5;
    defaultMaxIterations = 100;
    settingsDialog.setDefaultParameters(defaultReal, defaultImg, defaultXmin, defaultXmax, defaultYmin, defaultYmax, defaultMaxIterations);
    settingsDialog.show();

    this->hide();
}

void MainWindow::onCreateMandelbrotFractalButtonClicked() {
    lastFractalType = Mandelbrot;
    defaultReal = 2.0;
    defaultImg = 0.0;
    defaultXmin = -2.0;
    defaultXmax = 1.0;
    defaultYmin = -1.5;
    defaultYmax = 1.5;
    defaultMaxIterations = 100;
    settingsDialog.setDefaultParameters(defaultReal, defaultImg, defaultXmin, defaultXmax, defaultYmin, defaultYmax, defaultMaxIterations);
    settingsDialog.show();

    this->hide();
}

void MainWindow::useEmitParameters(double real, double img, double xmin, double xmax, double ymin, double ymax, int maxIterations) {
    if (lastFractalType == Julia) {
        JuliaWidget juliaWidget(real, img, xmin, xmax, ymin, ymax, maxIterations, nullptr);
        juliaWidget.show();
        while (juliaWidget.isVisible()) {
            QCoreApplication::processEvents();
        }
    } else if (lastFractalType == Mandelbrot) {
        MandelbrotWidget mandelbrotWidget(real, img, xmin, xmax, ymin, ymax, maxIterations, nullptr);
        mandelbrotWidget.show();
        while (mandelbrotWidget.isVisible()) {
            QCoreApplication::processEvents();
        }
    }
    this->show();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}


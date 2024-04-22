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
    connect(&fractalDialog, &Setting::appliedParameters, this, &MainWindow::onApplyParameters);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onCreateJuliaFractalButtonClicked() {
    // Установка параметров фрактала по умолчанию
    lastFractalType = Julia;
    defaultReal = 0.38;
    defaultImg = 0.25;
    defaultXmin = -1.5;
    defaultXmax = 1.5;
    defaultYmin = -1.5;
    defaultYmax = 1.5;
    defaultMaxIterations = 100;
    fractalDialog.setDefaultParameters(defaultReal, defaultImg, defaultXmin, defaultXmax, defaultYmin, defaultYmax, defaultMaxIterations);
    fractalDialog.show();
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
    fractalDialog.setDefaultParameters(defaultReal, defaultImg, defaultXmin, defaultXmax, defaultYmin, defaultYmax, defaultMaxIterations);
    fractalDialog.show();
}

void MainWindow::onApplyParameters(double real, double img, double xmin, double xmax, double ymin, double ymax, int maxIterations) {
    if (lastFractalType == Julia) {
        JuliaWidget *juliaWidget = new JuliaWidget(real, img, xmin, xmax, ymin, ymax, maxIterations, parentWidget());
        juliaWidget->show();
    } else if (lastFractalType == Mandelbrot) {
        MandelbrotWidget *mandelbrotWidget = new MandelbrotWidget(real, img, xmin, xmax, ymin, ymax, maxIterations, parentWidget());
        mandelbrotWidget->show();
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}


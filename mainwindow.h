#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "setting.h"
#include "mandelbrot.h"
#include "julia.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCreateMandelbrotFractalButtonClicked();
    void onCreateJuliaFractalButtonClicked();
    void useEmitParameters(double real, double img, double xmin, double xmax, double ymin, double ymax, int maxIterations);

private:
    Ui::MainWindow *ui;
    double defaultReal, defaultImg, defaultXmin, defaultXmax, defaultYmin, defaultYmax;
    int defaultMaxIterations;
    Setting settingsDialog;
    enum FractalType { Julia, Mandelbrot };
    FractalType lastFractalType;
};

#endif // MAINWINDOW_H

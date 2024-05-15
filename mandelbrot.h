#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "fractal.h"

class MandelbrotWidget : public QWidget, public Fractal {
    Q_OBJECT

public:
    MandelbrotWidget(double real, double imag, double xmin, double xmax, double ymin, double ymax, int maxIterations, QWidget *parent = nullptr);
    ~MandelbrotWidget() override;
    QImage generateFractal(double pReal, double pImag, double xmin, double xmax, double ymin, double ymax, int width, int height, int maxIterations) override;

private:

    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};

#endif // MANDELBROT_H

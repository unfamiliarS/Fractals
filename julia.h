#ifndef JULIA_H
#define JULIA_H

#include "fractal.h"

#include <vector>

class JuliaWidget : public QWidget, public Fractal {
    Q_OBJECT

public:
    JuliaWidget(double real, double imag, double xmin, double xmax, double ymin, double ymax, int maxIterations, QWidget *parent = nullptr);

protected:
    QImage generateFractal(double cReal, double cImag, double xmin, double xmax, double ymin, double ymax, int width, int height, int maxIterations) override;
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    double real, imag, xmin, xmax, ymin, ymax, zoomFactor;
    int maxIterations;
};

#endif // JULIA_H

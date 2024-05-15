#ifndef JULIA_H
#define JULIA_H

#include "fractal.h"

class JuliaWidget : public QWidget, public Fractal {
    Q_OBJECT

public:
    JuliaWidget(double real, double imag, double xmin, double xmax, double ymin, double ymax, int maxIterations, QWidget *parent = nullptr);
    ~JuliaWidget() override;
    QImage generateFractal(double cReal, double cImag, double xmin, double xmax, double ymin, double ymax, int width, int height, int maxIterations) override;

private:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
};

#endif // JULIA_H

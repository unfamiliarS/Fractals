#ifndef FRACTAL_H
#define FRACTAL_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QColor>
#include <QWheelEvent>
#include <thread>
#include <complex>
#include <cmath>

class Fractal {
protected:
    double real, imag, xmin, xmax, ymin, ymax, zoomFactor;
    int maxIterations;

    virtual QImage generateFractal(double Real, double Imag, double xmin, double xmax, double ymin, double ymax, int width, int height, int maxIterations) = 0;
    virtual ~Fractal() = default;

    QColor colorForIterations(int iterations, int maxIterations) {
        if (iterations == maxIterations) {
            return QColor(0, 0, 0);
        } else {
            int brightness = iterations * 255 / maxIterations;
            return QColor(brightness, brightness, brightness);
        }
    }
};

#endif // FRACTAL_H

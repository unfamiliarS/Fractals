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
public:
    virtual QImage generateFractal(double Real, double Imag, double xmin, double xmax, double ymin, double ymax, int width, int height, int maxIterations) = 0;
    virtual ~Fractal();

    QColor colorForIterations(int iterations, int maxIterations) {
        if (iterations == maxIterations) {
            // Если точка не вышла за пределы множества Мандельброта, окрасить в черный цвет
            return QColor(0, 0, 0);
        } else {
            // Вычисляем оттенок серого в зависимости от числа итераций
            int brightness = iterations * 255 / maxIterations;
            return QColor(brightness, brightness, brightness);
        }
    }
};

#endif // FRACTAL_H

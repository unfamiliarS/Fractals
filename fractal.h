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
            int brightness = 255 - iterations * 255 / maxIterations;
            return QColor(brightness, brightness, brightness);
        }
    }
    QColor colorForIterations1(int iterations, int maxIterations) {
        const int nmax = maxIterations;
        const int coloffset = 0;
        const int colwidth = 3;

        if (iterations == nmax) {
            // Если точка не вышла за пределы множества Мандельброта, окрасить в черный цвет
            return QColor(0, 0, 0);
        } else {
            iterations = (iterations + coloffset) % (3 * colwidth);
            int n = iterations;

            if (n / colwidth == 0) {
                // Голубой
                int blue = 116 + 139 * n / colwidth;
                int green = 11 + 244 * n / colwidth;
                int red = 237 * n / colwidth;
                return QColor(red, green, blue);
            } else if (n / colwidth == 1) {
                // Белый
                n -= colwidth;
                int blue = 255 - 253 * n / colwidth;
                int green = 255 - 123 * n / colwidth;
                int red = 238;
                return QColor(red, green, blue);
            } else {
                // Рыжий
                n -= 2 * colwidth;
                int blue = 2 + 114 * n / colwidth;
                int green = 132 - 121 * n / colwidth;
                int red = 239 - 239 * n / colwidth;
                return QColor(red, green, blue);
            }
        }
    }

};

#endif // FRACTAL_H

#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

    // Функция для установки параметров фрактала по умолчанию
    void setDefaultParameters(double Real, double Imag, double xmin, double xmax, double ymin, double ymax, int maxIterations);

private slots:
    // Слот для обработки нажатия кнопки "Применить"
    void onApplyButtonClicked();

signals:
    void appliedParameters(double real, double img, double xmin, double xmax, double ymin, double ymax, int maxIterations);

private:
    Ui::Setting *ui;
};

#endif // SETTING_H

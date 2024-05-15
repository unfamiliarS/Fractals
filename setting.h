#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QRegExpValidator>

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    Setting(QWidget *parent = nullptr);
    ~Setting();

    void setDefaultParameters(double Real, double Imag, double xmin, double xmax, double ymin, double ymax, int maxIterations);

private slots:
    void onApplyButtonClicked();
    void onLineEditEditingFinished();

signals:
    void appliedParameters(double real, double img, double xmin, double xmax, double ymin, double ymax, int maxIterations);

private:
    QRegExp regExp;
    QValidator *validator;
    Ui::Setting *ui;
};

#endif // SETTING_H

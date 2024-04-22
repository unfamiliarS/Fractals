#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    connect(ui->applyButton, &QPushButton::clicked, this, &Setting::onApplyButtonClicked);
}

Setting::~Setting()
{
    delete ui;
}

void Setting::setDefaultParameters(double Real, double Imag, double xmin, double xmax, double ymin, double ymax, int maxIterations)
{
    ui->realLineEdit->setText(QString::number(Real));
    ui->imgLineEdit->setText(QString::number(Imag));
    ui->xminLineEdit->setText(QString::number(xmin));
    ui->xmaxLineEdit->setText(QString::number(xmax));
    ui->yminLineEdit->setText(QString::number(ymin));
    ui->ymaxLineEdit->setText(QString::number(ymax));
    ui->maxIterations->setValue(maxIterations);
}

void Setting::onApplyButtonClicked()
{
    double real = ui->realLineEdit->text().toDouble();
    double img = ui->imgLineEdit->text().toDouble();
    double xmin = ui->xminLineEdit->text().toDouble();
    double xmax = ui->xmaxLineEdit->text().toDouble();
    double ymin = ui->yminLineEdit->text().toDouble();
    double ymax = ui->ymaxLineEdit->text().toDouble();
    int maxIterations = ui->maxIterations->value();

    emit appliedParameters(real, img, xmin, xmax, ymin, ymax, maxIterations);

    close();
}

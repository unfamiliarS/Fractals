#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    connect(ui->applyButton, &QPushButton::clicked, this, &Setting::onApplyButtonClicked);
    connect(ui->realLineEdit, &QLineEdit::editingFinished, this, &Setting::onLineEditEditingFinished);
    connect(ui->imgLineEdit, &QLineEdit::editingFinished, this, &Setting::onLineEditEditingFinished);
    connect(ui->xminLineEdit, &QLineEdit::editingFinished, this, &Setting::onLineEditEditingFinished);
    connect(ui->xmaxLineEdit, &QLineEdit::editingFinished, this, &Setting::onLineEditEditingFinished);
    connect(ui->yminLineEdit, &QLineEdit::editingFinished, this, &Setting::onLineEditEditingFinished);
    connect(ui->ymaxLineEdit, &QLineEdit::editingFinished, this, &Setting::onLineEditEditingFinished);
}

Setting::~Setting()
{
    delete ui;
    delete validator;
}

void Setting::setDefaultParameters(double Real, double Imag, double xmin, double xmax, double ymin, double ymax, int maxIterations)
{
    regExp.setPattern("[0-9]*\\.?[0-9]*");
    validator = new QRegExpValidator(regExp, this);
    ui->realLineEdit->setValidator(validator);
    ui->imgLineEdit->setValidator(validator);
    ui->xminLineEdit->setValidator(validator);
    ui->xmaxLineEdit->setValidator(validator);
    ui->yminLineEdit->setValidator(validator);
    ui->ymaxLineEdit->setValidator(validator);
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

    close();

    emit appliedParameters(real, img, xmin, xmax, ymin, ymax, maxIterations);
}

void Setting::onLineEditEditingFinished() {
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender());
    if (lineEdit && lineEdit->text().isEmpty()) {
        lineEdit->setText("0");
    }
}

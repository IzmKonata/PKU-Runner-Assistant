#include "runplandialog.h"
#include "ui_runplandialog.h"
#include <QDate>

runplandialog::runplandialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::runplandialog)
{
    ui->setupUi(this);

    // 初始化默认值
    QDate defaultDate = QDate::currentDate().addDays(7);
    ui->weightSpinBox->setValue(65.0);
    ui->heightSpinBox->setValue(170.0);
    ui->kmDoubleSpinBox->setValue(10.0);
    ui->maxTimeSpinBox->setValue(60);
    ui->dateEdit->setDate(defaultDate);
}

runplandialog::~runplandialog()
{
    delete ui;
}

double runplandialog::weight(double defaultValue) const
{
    return ui->weightSpinBox->value() > 0 ? ui->weightSpinBox->value() : defaultValue;
}

double runplandialog::height(double defaultValue) const
{
    return ui->heightSpinBox->value() > 0 ? ui->heightSpinBox->value() : defaultValue;
}

double runplandialog::remainingKm(double defaultValue) const
{
    return ui->kmDoubleSpinBox->value() > 0 ? ui->kmDoubleSpinBox->value() : defaultValue;
}

int runplandialog::maxDailyMinutes(int defaultValue) const
{
    return ui->maxTimeSpinBox->value() > 0 ? ui->maxTimeSpinBox->value() : defaultValue;
}

QDate runplandialog::targetDate() const
{
    return ui->dateEdit->date();
}

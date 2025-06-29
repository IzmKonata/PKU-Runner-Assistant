#include "scheduledialog.h"
#include "ui_scheduledialog.h"
#include <QDateTime>
#include <QTime>

ScheduleDialog::ScheduleDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScheduleDialog)
{
    ui->setupUi(this);

    // 初始化时间控件
    QDateTime current = QDateTime::currentDateTime();
    ui->dateEdit->setDate(current.date());
    ui->timeEdit->setTime(QTime(current.time().hour(), 0)); // 强制整点

    // 设置时间选择参数
    ui->timeEdit->setDisplayFormat("HH:00");
}

ScheduleDialog::~ScheduleDialog()
{
    delete ui;
}

QDateTime ScheduleDialog::startDateTime() const
{
    // 合并日期和时间（强制分钟为0）
    return QDateTime(
        ui->dateEdit->date(),
        QTime(ui->timeEdit->time().hour(), 0)
        );
}

int ScheduleDialog::duration() const
{
    return ui->durationSpinBox->value();
}

QString ScheduleDialog::task() const
{
    return ui->taskEdit->text();
}

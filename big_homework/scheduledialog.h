#ifndef SCHEDULEDIALOG_H
#define SCHEDULEDIALOG_H

#include <QDialog>

namespace Ui {
class ScheduleDialog;
}

class ScheduleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScheduleDialog(QWidget *parent = nullptr);
    ~ScheduleDialog();

    // 获取参数方法
    QDateTime startDateTime() const;
    int duration() const;
    QString task() const;

private:
    Ui::ScheduleDialog *ui;
};

#endif // SCHEDULEDIALOG_H

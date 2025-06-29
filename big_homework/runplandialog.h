#pragma once

#include <QDialog>

namespace Ui {
class runplandialog;
}

class runplandialog : public QDialog
{
    Q_OBJECT

public:
    explicit runplandialog(QWidget *parent = nullptr);
    ~runplandialog();

    // 参数获取方法（带默认值）
    double weight(double defaultValue = 65.0) const;
    double height(double defaultValue = 170.0) const;
    double remainingKm(double defaultValue = 10.0) const;
    int maxDailyMinutes(int defaultValue = 60) const;
    QDate targetDate() const;

private:
    Ui::runplandialog *ui;
};

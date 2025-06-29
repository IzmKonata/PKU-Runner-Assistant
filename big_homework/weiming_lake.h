#ifndef WEIMING_LAKE_H
#define WEIMING_LAKE_H

#include <QDialog>
#include "placerecommend.h"

namespace Ui {
class weiming_lake;
}

class weiming_lake : public QDialog
{
    Q_OBJECT

public:
    explicit weiming_lake(PlaceRecommend *parent = nullptr);
    ~weiming_lake();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::weiming_lake *ui;
    PlaceRecommend *m_parent;
};

#endif // WEIMING_LAKE_H

#ifndef FIVEFOURPLAYGROUND_H
#define FIVEFOURPLAYGROUND_H

#include <QDialog>
#include "placerecommend.h"

namespace Ui {
class fivefourplayground;
}

class fivefourplayground : public QDialog
{
    Q_OBJECT

public:
    explicit fivefourplayground(PlaceRecommend *parent = nullptr);
    ~fivefourplayground();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::fivefourplayground *ui;
    PlaceRecommend *m_parent;
};

#endif // FIVEFOURPLAYGROUND_H

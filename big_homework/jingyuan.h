#ifndef JINGYUAN_H
#define JINGYUAN_H

#include <QDialog>
#include "placerecommend.h"

namespace Ui {
class jingyuan;
}

class jingyuan : public QDialog
{
    Q_OBJECT

public:
    explicit jingyuan(PlaceRecommend *parent = nullptr);
    ~jingyuan();
    PlaceRecommend * m_parent;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::jingyuan *ui;
};

#endif // JINGYUAN_H

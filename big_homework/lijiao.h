#ifndef LIJIAO_H
#define LIJIAO_H

#include <QDialog>
#include "placerecommend.h"

namespace Ui {
class lijiao;
}

class lijiao : public QDialog
{
    Q_OBJECT

public:
    explicit lijiao(PlaceRecommend *parent = nullptr);
    ~lijiao();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::lijiao *ui;
    PlaceRecommend * m_parent;
};

#endif // LIJIAO_H

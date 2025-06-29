#ifndef LANGRUN_H
#define LANGRUN_H

#include <QDialog>
#include "placerecommend.h"

namespace Ui {
class langrun;
}

class langrun : public QDialog
{
    Q_OBJECT

public:
    explicit langrun(PlaceRecommend *parent = nullptr);
    ~langrun();
    PlaceRecommend * m_parent;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::langrun *ui;
};

#endif // LANGRUN_H

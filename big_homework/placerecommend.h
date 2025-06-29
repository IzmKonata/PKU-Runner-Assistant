#ifndef PLACERECOMMEND_H
#define PLACERECOMMEND_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class PlaceRecommend;
}
QT_END_NAMESPACE

class PlaceRecommend : public QMainWindow
{
    Q_OBJECT

public:
    PlaceRecommend(QWidget *parent = nullptr);
    ~PlaceRecommend();
    int page;
    Ui::PlaceRecommend * get_ui()
    {
        return ui;
    }
    Ui::PlaceRecommend *ui;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();



    void on_pushButton_8_clicked();
};
#endif // PLACERECOMMEND_H

#ifndef MYDIALOG_H
#define MYDIALOG_H
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QPixmap>
#include <QDialog>

namespace Ui {
class MYDialog;
}

class MYDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MYDialog(QWidget *parent = nullptr);
    ~MYDialog();


private slots:
    void on_pushButton_2_clicked();

private:
    Ui::MYDialog *ui;
};

#endif // MYDIALOG_H

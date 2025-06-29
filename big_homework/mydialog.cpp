#include "mydialog.h"
#include "ui_mydialog.h"
#include<iostream>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QVector>
#include <QDebug>
using namespace std;
MYDialog::MYDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MYDialog)
{
    ui->setupUi(this);
}

MYDialog::~MYDialog()
{
    delete ui;
}

void MYDialog::on_pushButton_2_clicked()
{
    const QList<QLineEdit*>lineedits=findChildren<QLineEdit*>();
    QVector<QString>vec;
    for(QLineEdit* a:lineedits){
        vec.append(a->text());
    }
}


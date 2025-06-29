#include "ModuleWidget.h"
#include <QVBoxLayout>
#include<QPixmap>
#include<QLabel>
#include<iostream>
#include<QScrollArea>
#include"placerecommend.h"
#include"module3main.h"
#include<QWidget>
#include<QMainWindow>
#include"RunningCalendarModule.h"
#include"mainwindow.h"
ModuleWidget::ModuleWidget(QMainWindow *parent) : QMainWindow(parent) {
    QWidget *centrallWidget = new QWidget(this);
    setCentralWidget(centrallWidget);

    buttonModule1 = new QPushButton("地点推荐", this);
    buttonModule2 = new QPushButton("我的运动日历", this);
    buttonModule3 = new QPushButton("音乐推荐", this);
    homepage=new QPushButton("我的主页",this);
    allinhere=new QStackedWidget(centrallWidget);
    A=new PlaceRecommend(this);
    B=new RunningCalendarModule(MainWindow::getUserName(),this);
    C=new module3main(this);
    D=nullptr;

    allinhere->addWidget(A);
    allinhere->addWidget(B);
    allinhere->addWidget(C);

    setStyleSheet("background-color: transparent;");
    layout = new QVBoxLayout(centrallWidget);
    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap(":/new/prefix1/images/bkgd.png"); // 使用资源文件中的图片路径
    if (!pixmap.isNull()) {
        imageLabel->setPixmap(pixmap);
        imageLabel->setScaledContents(true);
        imageLabel->setFixedWidth(1200);
        imageLabel->lower();
        imageLabel->setFixedHeight(1000);
    } else {
        imageLabel->setText("图片加载失败");
    }
    QLabel *labelone = new QLabel(this);
    QPixmap pixmap1(":/new/prefix1/images/OIP.jpg"); // 替换为你的图片路径

    //labelone->setPixmap(pixmap1);
    //labelone->setScaledContents(true);
    // 设置标签和按钮的大小和位置以使它们中心重合
    //buttonModule1->setGeometry(50, 150, 100, 100);
    // buttonModule1->setText("查看我的日历");
    //labelone->setGeometry(50, 150, 100, 100);
    //labelone->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    layout->addWidget(buttonModule1);
    layout->addWidget(buttonModule2);
    layout->addWidget(buttonModule3);
    layout->addWidget(homepage);
    layout->addWidget(allinhere);

    imageLabel->lower();

    connect(buttonModule1, &QPushButton::clicked, this, &ModuleWidget::onModule1Clicked);
    connect(buttonModule2, &QPushButton::clicked, this, &ModuleWidget::onModule2Clicked);
    connect(buttonModule3, &QPushButton::clicked, this, &ModuleWidget::onModule3Clicked);
    connect(homepage,&QPushButton::clicked,this,&ModuleWidget::onhomepageclicked);
    allinhere->setCurrentWidget(centrallWidget);
}

void ModuleWidget::createhome(){


    B->setAccountName(MainWindow::getUserName());
}
void ModuleWidget::onModule1Clicked() {
    allinhere->setCurrentWidget(A);

    emit module1Clicked();
}

void ModuleWidget::onModule2Clicked() {
    allinhere->setCurrentWidget(B);
    emit module2Clicked();
}

void ModuleWidget::onModule3Clicked() {

    allinhere->setCurrentWidget(C);

    emit module3Clicked();
}
void ModuleWidget::onhomepageclicked(){
    if (D)
    {
        delete D;
    }
    D=new Homepage(allinhere);
    allinhere->addWidget(D);

    D->show();
}

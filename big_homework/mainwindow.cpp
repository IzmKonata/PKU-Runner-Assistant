#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include<iostream>
#include"ModuleWidget.h"
#include <QApplication>
#include "xlsxdocument.h"
QString usrnamet;
float heightt;
float weightt;
void appendData(QXlsx::Document& xlsx, const QString& name,const QString &password,const QString&height,const QString& weight,const QString&gender,const QStringList& musicgenre) {
    // 检查是否已有表头
    if (xlsx.dimension().rowCount() == 0) {
        // 写入表头
        xlsx.write(1, 1, "用户名");
        xlsx.write(1, 2, "密码");
        xlsx.write(1, 3, "身高");
        xlsx.write(1, 4, "体重");
        xlsx.write(1, 5, "性别");
    }
    int lastRow = xlsx.dimension().rowCount() + 1;
    xlsx.write(lastRow, 1, name);     // A列
    xlsx.write(lastRow, 2, password); // B列
    xlsx.write(lastRow, 3, height);   // C列
    xlsx.write(lastRow, 4, weight);   // D列
    xlsx.write(lastRow, 5, gender);
    int row=6;    // E列
    for ( const QString&str:musicgenre){
        xlsx.write(lastRow,row,str);
        row++;
    }



}
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    this->setWindowTitle("PKU Runner Assistant");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    stackedWidget = new QStackedWidget(centralWidget);

    loginWidget = new LoginWidget(this);
    registerWidget = new RegisterWidget(this);
    modulewidget=new ModuleWidget(this);

    homeWidget = new QWidget(this);
    labelWelcome = new QLabel("欢迎，未登录", homeWidget);
    buttonLogout = new QPushButton("退出登录", homeWidget);

    QVBoxLayout *homeLayout = new QVBoxLayout(homeWidget);
    homeLayout->addWidget(labelWelcome);
    homeLayout->addWidget(buttonLogout);

    stackedWidget->addWidget(loginWidget);
    stackedWidget->addWidget(registerWidget);
    stackedWidget->addWidget(homeWidget);
    stackedWidget->addWidget(modulewidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(stackedWidget);

    connect(loginWidget, &LoginWidget::loginClicked, this, &MainWindow::onLoginClicked);
    connect(loginWidget, &LoginWidget::registerClicked, this, &MainWindow::onRegisterClicked);
    connect(registerWidget, &RegisterWidget::registerCompleted, this, &MainWindow::onRegisterCompleted);
    connect(registerWidget, &RegisterWidget::backToLoginClicked, this, &MainWindow::onBackToLoginClicked);
    connect(registerWidget->getChartWidget(), &ChartWidget::pointClicked, this, &MainWindow::onPointClicked);
    connect(buttonLogout, &QPushButton::clicked, this, &MainWindow::onBackToLoginClicked);

    stackedWidget->setCurrentWidget(loginWidget);
}

MainWindow::~MainWindow() {
}

void MainWindow::onLoginClicked(const QString &username, const QString &password) {
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "登录失败", "用户名和密码不能为空！");
        return;
    }
    this->modulewidget->createhome();
    stackedWidget->setCurrentWidget(modulewidget);
}

void MainWindow::onRegisterClicked() {
    stackedWidget->setCurrentWidget(registerWidget);
}


void MainWindow::onRegisterCompleted(const QString &username, const QString &password,
                                     const QStringList &musicGenres, const QString &gender,
                                     const QString &height, const QString &weight)
{
    // 获取可执行文件所在目录
    QString appDir = QCoreApplication::applicationDirPath();
    QString filePath = appDir + "/userdata.xlsx";
    std::cout<<filePath.toLocal8Bit().data()<<std::endl;
    qDebug() << "尝试保存到:" << filePath;

    // 创建或打开Excel文件
    QXlsx::Document xlsx(filePath);

    // 如果文件存在，加载它
    if (QFile::exists(filePath)) {
        std::cout<<"hello exists"<<std::endl;
    } else {
        std::cout << "文件不存在，将创建新文件";
    }

    // 追加数据
    appendData(xlsx, username, password, height, weight, gender,musicGenres);
    xlsx.saveAs(filePath);


    stackedWidget->setCurrentWidget(loginWidget);
}


void MainWindow::onBackToLoginClicked() {
    stackedWidget->setCurrentWidget(loginWidget);
}

void MainWindow::onPointClicked(double x, double y) {

}

QString MainWindow::getUserName()
{
    QString name=usrnamet;
    return name;
}

float MainWindow::getUserHeight()
{
    float a=heightt;
    return a;
}

float MainWindow::getUserWeight()
{
    float a=weightt;
    return a;
}

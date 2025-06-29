#include "loginwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QFont>
#include<QCoreApplication>
#include<QPalette>
#include<QFile>
#include"xlsxdocument.h"
#include"mainwindow.h"
LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent) {
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::white);
    setPalette(palette);
    setAutoFillBackground(true);
    QLabel *labelUser = new QLabel("用户名:", this);
    QLabel *labelPass = new QLabel("密码:", this);
    QFont font = labelUser->font(); // 获取当前字体
    font.setFamily("Arial"); // 设置字体系列
    font.setPointSize(10); // 设置字体大小
    font.setBold(true); // 设置加粗
    font.setItalic(true); // 设置斜体
    labelUser->setFont(font); // 应用字体设置
    labelPass->setFont(font);
    labelUser->setStyleSheet("color: black; background-color: white;");
    labelPass->setStyleSheet("color: black; background-color: white;");
    lineEditUser = new QLineEdit(this);
    lineEditPass = new QLineEdit(this);
    lineEditPass->setEchoMode(QLineEdit::Password);

    // 设置输入框样式
    lineEditUser->setStyleSheet(
        "QLineEdit {"
        "    background-color: grey;"
        "    border-radius: 10px;"
        "    padding: 10px;"
        "    margin: 0px;"
        "}"
        );
    lineEditPass->setStyleSheet(
        "QLineEdit {"
        "    background-color: grey;"
        "    border-radius: 10px;"
        "    padding: 10px;"
        "    margin: 0px;"
        "}"
        );

    buttonLogin = new QPushButton("登录", this);
    buttonRegister = new QPushButton("注册", this);
    // 设置图片
    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap(":/new/prefix1/images/jogging.jpg"); // 使用资源文件中的图片路径
    if (!pixmap.isNull()) {
        imageLabel->setPixmap(pixmap);
        imageLabel->setScaledContents(false);
        imageLabel->setFixedHeight(500);
    } else {
        imageLabel->setText("图片加载失败");
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    QVBoxLayout *layoutUser = new QVBoxLayout(); // 改为垂直布局
    QVBoxLayout *layoutPass = new QVBoxLayout(); // 改为垂直布局
    QHBoxLayout *layoutButtons = new QHBoxLayout();

    layout->setSizeConstraint(QLayout::SetMinimumSize);
    layoutUser->addWidget(labelUser);
    layoutUser->addWidget(lineEditUser);
    layout->addWidget(imageLabel); // 添加图片标签
    layoutPass->addWidget(labelPass);
    layoutPass->addWidget(lineEditPass);
    layout->setSpacing(0);



    layoutButtons->addWidget(buttonLogin);
    layoutButtons->addWidget(buttonRegister);

    layout->addLayout(layoutUser);
    layout->addLayout(layoutPass);
    layout->addLayout(layoutButtons);

    connect(buttonLogin, &QPushButton::clicked, this, &LoginWidget::onLoginClicked);
    connect(buttonRegister, &QPushButton::clicked, this, &LoginWidget::onRegisterClicked);

}
bool LoginWidget::verifyUserFromExcel(const QString &username,const QString & password){
    QString appDir = QCoreApplication::applicationDirPath();
    QString filePath = appDir + "/userdata.xlsx";


    QXlsx::Document xlsx(filePath);
    int row = 2;
    while (true) {
        QString storedUser = xlsx.read(row, 1).toString(); // B列用户名
        QString storedPass = xlsx.read(row, 2).toString(); // C列密码

        // 检查是否到达数据末尾
        if (storedUser.isEmpty()) break;

        // 检查用户名和密码是否匹配
        if (storedUser == username && storedPass == password) {
            heightt=xlsx.read(row,3).toFloat();
            weightt=xlsx.read(row,4).toFloat();
            return true; // 找到匹配用户
        }

        row++;
    }

    return false; // 未找到匹配用户
}
void LoginWidget::onLoginClicked() {
    QString username = lineEditUser->text();
    QString password = lineEditPass->text();

    // 验证输入是否为空
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "登录失败", "用户名和密码不能为空！");
        return;
    }

    // 从Excel验证用户
    bool isValid = verifyUserFromExcel(username, password);

    if (isValid) {
        usrnamet=username;
        emit loginClicked(username, password);
    } else {
        // 验证失败，清空密码框并提示
        lineEditPass->clear();
        QMessageBox::warning(this, "登录失败", "用户名或密码错误，请重新输入！");
    }
}

void LoginWidget::onRegisterClicked() {
    emit registerClicked();
}

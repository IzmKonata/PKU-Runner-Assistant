#include "registerwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>



RegisterWidget::RegisterWidget(QWidget *parent) : QWidget(parent) {
    QLabel *labelUser = new QLabel("用户名:", this);
    QLabel *labelPass = new QLabel("密码:", this);
    QLabel *labelConfirmPass = new QLabel("确认密码:", this);
    QLabel *labelMusic = new QLabel("音乐偏好:", this);
    QLabel *labelGender = new QLabel("性别:", this);
    QLabel *labelHeight = new QLabel("身高 (cm):", this);
    QLabel *labelWeight = new QLabel("体重 (kg):", this);

    lineEditUser = new QLineEdit(this);
    lineEditPass = new QLineEdit(this);
    lineEditPass->setEchoMode(QLineEdit::Password);
    lineEditConfirmPass = new QLineEdit(this);
    lineEditConfirmPass->setEchoMode(QLineEdit::Password);
    lineEditHeight = new QLineEdit(this);
    lineEditWeight = new QLineEdit(this);

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
    lineEditConfirmPass->setStyleSheet(
        "QLineEdit {"
        "    background-color: grey;"
        "    border-radius: 10px;"
        "    padding: 10px;"
        "    margin: 0px;"
        "}"
        );
    lineEditHeight->setStyleSheet(
        "QLineEdit {"
        "    background-color: grey;"
        "    border-radius: 10px;"
        "    padding: 10px;"
        "    margin: 0px;"
        "}"
        );
    lineEditWeight->setStyleSheet(
        "QLineEdit {"
        "    background-color: grey;"
        "    border-radius: 10px;"
        "    padding: 10px;"
        "    margin: 0px;"
        "}"
        );



    buttonRegister = new QPushButton("注册", this);
    buttonBackToLogin = new QPushButton("返回登录", this);

    checkBoxPop = new QCheckBox("流行音乐", this);
    checkBoxRock = new QCheckBox("摇滚音乐", this);
    checkBoxJazz = new QCheckBox("爵士音乐", this);
    checkBoxClassic = new QCheckBox("古典音乐", this);
    checkBoxElectronic = new QCheckBox("电子音乐", this);

    radioButtonMale = new QRadioButton("男", this);
    radioButtonFemale = new QRadioButton("女", this);
    radioButtonOther = new QRadioButton("其他", this);
    radioButtonMale->setChecked(true);

    chartWidget = new ChartWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *layoutUser = new QHBoxLayout();
    QHBoxLayout *layoutPass = new QHBoxLayout();
    QHBoxLayout *layoutConfirmPass = new QHBoxLayout();
    QHBoxLayout *layoutMusic = new QHBoxLayout();
    QHBoxLayout *layoutGender = new QHBoxLayout();
    QHBoxLayout *layoutHeight = new QHBoxLayout();
    QHBoxLayout *layoutWeight = new QHBoxLayout();
    QHBoxLayout *layoutButtons = new QHBoxLayout();

    layoutUser->addWidget(labelUser);
    layoutUser->addWidget(lineEditUser);
    layoutPass->addWidget(labelPass);
    layoutPass->addWidget(lineEditPass);
    layoutConfirmPass->addWidget(labelConfirmPass);
    layoutConfirmPass->addWidget(lineEditConfirmPass);
    layoutMusic->addWidget(labelMusic);
    layoutMusic->addWidget(checkBoxPop);
    layoutMusic->addWidget(checkBoxRock);
    layoutMusic->addWidget(checkBoxJazz);
    layoutMusic->addWidget(checkBoxClassic);
    layoutMusic->addWidget(checkBoxElectronic);
    layoutGender->addWidget(labelGender);
    layoutGender->addWidget(radioButtonMale);
    layoutGender->addWidget(radioButtonFemale);
    layoutGender->addWidget(radioButtonOther);
    layoutHeight->addWidget(labelHeight);
    layoutHeight->addWidget(lineEditHeight);
    layoutWeight->addWidget(labelWeight);
    layoutWeight->addWidget(lineEditWeight);
    layoutButtons->addWidget(buttonRegister);
    layoutButtons->addWidget(buttonBackToLogin);

    layout->addLayout(layoutUser);
    layout->addLayout(layoutPass);
    layout->addLayout(layoutConfirmPass);
    layout->addLayout(layoutMusic);
    layout->addLayout(layoutGender);
    layout->addLayout(layoutHeight);
    layout->addLayout(layoutWeight);
    layout->addLayout(layoutButtons);
    layout->addWidget(chartWidget);
    QList<QPair<double, int>> tempoYearData = {

        {25, 1916},
        {25,1947},
        {25,1978},
        {25,2009},
        {75, 1916},
        {75,1947},
        {75,1978},
        {75,2009},
        {125, 1916},
        {125,1947},
        {125,1978},
        {125,2009},
        {175, 1916},
        {175,1947},
        {175,1978},
        {175,2009},
    };

    for (const auto &data : tempoYearData) {
        chartWidget->addData(data.first, data.second);
    }

    connect(buttonRegister, &QPushButton::clicked, this, &RegisterWidget::onRegisterClicked);
    connect(buttonBackToLogin, &QPushButton::clicked, this, &RegisterWidget::onBackToLoginClicked);
}

ChartWidget* RegisterWidget::getChartWidget() const {
    return chartWidget;
}

void RegisterWidget::onRegisterClicked() {
    QString username = lineEditUser->text();
    QString password = lineEditPass->text();
    QString confirmPassword = lineEditConfirmPass->text();
    QString height = lineEditHeight->text();
    QString weight = lineEditWeight->text();

    QStringList musicGenres;
    if (checkBoxPop->isChecked()) musicGenres << "流行音乐";
    if (checkBoxRock->isChecked()) musicGenres << "摇滚音乐";
    if (checkBoxJazz->isChecked()) musicGenres << "爵士音乐";
    if (checkBoxClassic->isChecked()) musicGenres << "古典音乐";
    if (checkBoxElectronic->isChecked()) musicGenres << "电子音乐";

    QString gender;
    if (radioButtonMale->isChecked()) gender = "男";
    else if (radioButtonFemale->isChecked()) gender = "女";
    else gender = "其他";

    if (password != confirmPassword) {
        QMessageBox::warning(this, "注册失败", "两次输入的密码不一致！");
        return;
    }

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "注册失败", "用户名和密码不能为空！");
        return;
    }

    if (musicGenres.isEmpty()) {
        QMessageBox::warning(this, "注册失败", "请至少选择一个音乐偏好！");
        return;
    }

    if (height.isEmpty() || weight.isEmpty()) {
        QMessageBox::warning(this, "注册失败", "身高和体重不能为空！");
        return;
    }

    QList<QPair<double, int>> tempoYearData = {
        {25, 1916},
        {25,1947},
        {25,1978},
        {25,2009},
        {75, 1916},
        {75,1947},
        {75,1978},
        {75,2009},
        {125, 1916},
        {125,1947},
        {125,1978},
        {125,2009},
        {175, 1916},
        {175,1947},
        {175,1978},
        {175,2009},
    };

    for (const auto &data : tempoYearData) {
        chartWidget->addData(data.first, data.second);
    }

    emit registerCompleted(username, password, musicGenres, gender, height, weight);
}

void RegisterWidget::onBackToLoginClicked() {
    emit backToLoginClicked();
}

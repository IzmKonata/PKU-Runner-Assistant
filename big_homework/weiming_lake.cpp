#include "weiming_lake.h"
#include "ui_placerecommend.h"
#include "ui_weiming_lake.h"
#include "placerecommend.h"

weiming_lake::weiming_lake(PlaceRecommend *parent)
    : QDialog(parent)
    , ui(new Ui::weiming_lake)
{
    ui->setupUi(this);
    m_parent = parent;

    // 设置窗口背景为白色
    this->setStyleSheet("background-color: white;"
                        "QLabel, QPushButton { color: black;}");


    // 设置所有QLabel和QPushButton的字体颜色为黑色
    // this->setStyleSheet("QLabel, QPushButton { color: black; }");
}

weiming_lake::~weiming_lake()
{
    delete ui;
}

void weiming_lake::on_pushButton_2_clicked()
{
    this->accept();
}


void weiming_lake::on_pushButton_clicked()
{
    QPixmap map_img(":/new/prefix1/map_imgs/lake.jpg");
    if (m_parent)
    {
        m_parent->get_ui()->prensent_img->setPixmap(map_img);
        QString st = "未名湖步道";
        m_parent->get_ui()->present_text->setText(st);
    }
    this->accept();
}


#include "lijiao.h"
#include "ui_lijiao.h"
#include "placerecommend.h"
#include "ui_placerecommend.h"

lijiao::lijiao(PlaceRecommend *parent)
    : QDialog(parent)
    , ui(new Ui::lijiao)
{
    ui->setupUi(this);
    m_parent = parent;

    // 设置窗口背景为白色
    this->setStyleSheet("background-color: white;"
                        "QLabel, QPushButton { color: black;}");

    // 设置所有QLabel和QPushButton的字体颜色为黑色
    // this->setStyleSheet("QLabel, QPushButton { color: black; }");
}

lijiao::~lijiao()
{
    delete ui;
}

void lijiao::on_pushButton_2_clicked()
{
    this->accept();
}


void lijiao::on_pushButton_clicked()
{
    QPixmap map_img(":/new/prefix1/map_imgs/lijiao.jpeg");
    if (m_parent)
    {
        m_parent->get_ui()->prensent_img->setPixmap(map_img);
        QString st = "理教环路";
        m_parent->get_ui()->present_text->setText(st);
    }
    this->accept();
}


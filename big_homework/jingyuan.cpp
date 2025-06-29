#include "jingyuan.h"
#include "ui_jingyuan.h"
#include "placerecommend.h"
#include "ui_placerecommend.h"

jingyuan::jingyuan(PlaceRecommend *parent)
    : QDialog(parent)
    , ui(new Ui::jingyuan)
{
    ui->setupUi(this);
    m_parent = parent;

    // 设置窗口背景为白色
    this->setStyleSheet("background-color: white;"
                        "QLabel, QPushButton { color: black;}");


    // 设置所有QLabel和QPushButton的字体颜色为黑色
    // this->setStyleSheet("QLabel, QPushButton { color: black; }");
}

jingyuan::~jingyuan()
{
    delete ui;
}

void jingyuan::on_pushButton_2_clicked()
{
    this->accept();
}


void jingyuan::on_pushButton_clicked()
{
    QPixmap map_img(":/new/prefix1/map_imgs/jingyuan.jpg");
    if (m_parent)
    {
        m_parent->get_ui()->prensent_img->setPixmap(map_img);
        QString st = "静园周边";
        m_parent->get_ui()->present_text->setText(st);
    }
    this->accept();
}


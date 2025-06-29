#include "fivefourplayground.h"
#include "ui_fivefourplayground.h"
#include "ui_placerecommend.h"
#include"placerecommend.h"

fivefourplayground::fivefourplayground(PlaceRecommend *parent) :
    QDialog(parent),
    ui(new Ui::fivefourplayground)
{
    ui->setupUi(this);
    m_parent = parent;

    // 设置窗口背景为白色
    this->setStyleSheet("background-color: white;"
                        "QLabel, QPushButton { color: black;}");


    // 设置所有QLabel和QPushButton的字体颜色为黑色
    // this->setStyleSheet("QLabel, QPushButton { color: black; }");
}

fivefourplayground::~fivefourplayground()
{
    delete ui;
}

void fivefourplayground::on_pushButton_clicked()
{
    QPixmap map_img(":/new/prefix1/map_imgs/R-C.jpg");
    if (m_parent)
    {
        m_parent->get_ui()->prensent_img->setPixmap(map_img);
        QString s = "五四体育场";
        m_parent->get_ui()->present_text->setText(s);
    }
    this->accept();
}


void fivefourplayground::on_pushButton_2_clicked()
{
    this->accept();
}


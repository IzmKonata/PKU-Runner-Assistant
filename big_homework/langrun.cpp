#include "langrun.h"
#include "ui_langrun.h"
#include "placerecommend.h"
#include "ui_placerecommend.h"

langrun::langrun(PlaceRecommend *parent)
    : QDialog(parent)
    , ui(new Ui::langrun)
{
    ui->setupUi(this);
    m_parent = parent;

    // 设置窗口背景为白色
    this->setStyleSheet("background-color: white;"
                        "QLabel, QPushButton { color: black;}");

    // 设置所有QLabel和QPushButton的字体颜色为黑色
    // this->setStyleSheet("QLabel, QPushButton { color: black; }");
}

langrun::~langrun()
{
    delete ui;
}

void langrun::on_pushButton_2_clicked()
{
    this->accept();
}



void langrun::on_pushButton_clicked()
{
    QPixmap map_img(":/new/prefix1/map_imgs/langrun.jpg");
    if (m_parent)
    {
        m_parent->get_ui()->prensent_img->setPixmap(map_img);
        QString st = "朗润园-镜春园";
        m_parent->get_ui()->present_text->setText(st);
    }
    this->accept();
}


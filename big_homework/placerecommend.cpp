#include "placerecommend.h"
#include "ui_placerecommend.h"
#include "fivefourplayground.h"
#include "weiming_lake.h"
#include "lijiao.h"
#include "jingyuan.h"
#include "langrun.h"
#include <random>
#include <QTimer>

PlaceRecommend::PlaceRecommend(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlaceRecommend)
{
    ui->setupUi(this);

    //构造时显示图片
    QPixmap map_img(":/new/prefix1/map_imgs/snapshot.png");
    ui->school_map->setPixmap(map_img);
    QPixmap bg_img(":/new/prefix1/map_imgs/bg.jpg");
    ui->background->setPixmap(bg_img);
    QPixmap bg_2_img(":/new/prefix1/map_imgs/bg_2.png");
    ui->background_2->setPixmap(bg_2_img);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);

    page = 0;

}

PlaceRecommend::~PlaceRecommend()
{
    delete ui;
}

void PlaceRecommend::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void PlaceRecommend::on_pushButton_2_clicked()
{
    fivefourplayground fg(this);
    fg.exec();
}


void PlaceRecommend::on_pushButton_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    QString str_tab[5] = {"朗润园-镜春园","未名湖步道","静园周边","理教环路","五四体育场"};
    QString pic_tab[5] = {"langrun.jpg","lake.jpg","jingyuan.jpg","lijiao.jpeg","R-C.jpg"};

    // 初始化评分 (0-4分别对应5个场地)
    std::vector<double> scores(5, 0.0);

    // 随机数生成器 (用于添加扰动)
    static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_real_distribution<double> dist(-3.0, 3.0);

    // 1. 天气因素评分
    if (this->ui->comboBox->currentText() == "小雨") {
        scores[0] -= 3;  // 原生态路面易滑
        scores[2] -= 2;  // 砖石路面较滑
        scores[4] += 2;  // 塑胶跑道防滑
    }
    else if (this->ui->comboBox->currentText() == "大风") {
        scores[0] -= 3;  // 树林区域危险
        scores[1] -= 1;  // 湖边风力较大
        scores[3] += 1;  // 建筑群挡风
        scores[4] += 2;  // 开阔场地安全
    }

    // 2. 时段因素评分
    if (this->ui->comboBox_3->currentText() == "清晨") {
        scores[1] += 3;  // 湖景晨光最佳
        scores[0] += 2;  // 清晨幽静氛围
    }
    else if (this->ui->comboBox_3->currentText() == "傍晚") {
        scores[1] += 2;  // 夕阳湖景
        scores[2] += 1;  // 古建黄昏光影
    }
    else if (this->ui->comboBox_3->currentText() == "夜间") {
        scores[3] += 3;  // 照明充足
        scores[4] += 3;  // 专业灯光
        scores[0] -= 2;  // 光线不足
        scores[2] -= 2;  // 光线不足
    }

    // 3. 星期因素 (周末偏好调整)
    if (this->ui->comboBox_2->currentText() == "周六" || this->ui->comboBox_2->currentText() == "周日") {  // 周末 (5=周六, 6=周日)
        scores[0] += 1;  // 探索型场地
        scores[1] += 2;  // 热门景点
    }
    else {  // 工作日
        scores[3] += 2;  // 教学区效率高
        scores[4] += 1;  // 专业训练
    }

    // 4. 核心优势恒定加分
    scores[1] += 2;  // 标志性景观
    scores[4] += 2;  // 专业跑道

    // 5. 添加随机扰动并找出最高分
    std::vector<double> finalScores;
    for (double score : scores) {
        finalScores.push_back(score + dist(rng));
    }

    // 6. 找出最高分索引
    int bestIndex = 0;
    for (int i = 1; i < finalScores.size(); i++) {
        if (finalScores[i] > finalScores[bestIndex]) {
            bestIndex = i;
        }
    }

    // 7. 处理同分情况 (收集所有最高分索引)
    std::vector<int> bestIndices;
    for (int i = 0; i < finalScores.size(); i++) {
        if (finalScores[i] == finalScores[bestIndex]) {
            bestIndices.push_back(i);
        }
    }

    // 8. 多个同分时随机选择
    std::uniform_int_distribution<int> idxDist(0, bestIndices.size() - 1);
    int random_number = bestIndices[idxDist(rng)];

    QString str = str_tab[random_number];
    QString pic = pic_tab[random_number];
    QString add = ":/new/prefix1/map_imgs/";
    add += pic;
    QPixmap img(add);
    ui->label_11->setPixmap(img);
    ui->label_12->setText(str);


}


void PlaceRecommend::on_pushButton_6_clicked()
{
    weiming_lake wm(this);
    wm.exec();
}


void PlaceRecommend::on_pushButton_7_clicked()
{
    lijiao lj(this);
    lj.exec();
}


void PlaceRecommend::on_pushButton_9_clicked()
{
    jingyuan jy(this);
    jy.exec();
}


void PlaceRecommend::on_pushButton_10_clicked()
{
    langrun lr(this);
    lr.exec();
}


void PlaceRecommend::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
}


void PlaceRecommend::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
    QString str = ui->label_12->text();
    QString add = ":/new/prefix1/map_imgs/";
    QString str_tab[5] = {"朗润园-镜春园","未名湖步道","静园周边","理教环路","五四体育场"};
    QString pic_tab[5] = {"langrun.jpg","lake.jpg","jingyuan.jpg","lijiao.jpeg","R-C.jpg"};
    for (int i=0;i<5;i++)
    {
        if (str == str_tab[i])
        {
            add += pic_tab[i];
            break;
        }
    }
    QPixmap img(add);
    ui->present_text->setText(str);
    ui->prensent_img->setPixmap(img);
}

void PlaceRecommend::on_pushButton_8_clicked()
{
    QLabel *message = new QLabel("快去跑步吧！", this);
    message->setAlignment(Qt::AlignCenter);
    message->setMinimumSize(300, 80);
    message->setStyleSheet("background-color: white; border: 1px solid #3498db; padding: 15px;");
    message->move(width()/2 - 150, height()/2 - 40);
    message->show();

    // 3秒后自动关闭
    QTimer::singleShot(3000, message, &QLabel::deleteLater);
}


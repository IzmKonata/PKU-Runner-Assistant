#include"module3.h"
#include<QVBoxLayout>
#include<iostream>
#include<cmath>
#include<QPushButton>
#include <QPropertyAnimation>
#include"purefunction.h"



module3::module3(QWidget *parent) : QWidget(parent) {
    // 创建圆点图片（红色圆形）
    dotPixmap = QPixmap(20, 20);
    dotPixmap.fill(Qt::transparent);

    QPainter painter(&dotPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::red);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(dotPixmap.rect());

    series = new QScatterSeries();
    series->setName("音乐偏好");

    // 创建指示器标签（初始隐藏） - 这是关键修复！
    clickIndicator = new QLabel(this); // 添加这行
    clickIndicator->setPixmap(dotPixmap);
    clickIndicator->setFixedSize(dotPixmap.size());
    clickIndicator->hide();

    chart = new QChart();
    chart->addSeries(series);
    QFont font;
    font.setFamily("Arial");  // 设置字体为 Arial
    font.setPointSize(16);    // 设置字号为 16
    font.setBold(true); // 设置加粗
    chart->setTitleFont(font);  // 应用自定义字体到标题
    chart->setTitle("音乐推荐");
    chart->legend()->hide();

    axisX = new QValueAxis();
    axisX->setLabelFormat("%d");
    axisX->setTitleText("配速（分钟/千米）");
    axisX->setRange(3, 15);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setLabelFormat("%d");
    axisY->setTitleText("心情");
    axisY->setRange(-100, 100);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    axisX->setLabelFormat("%i"); // 设置标签格式
    axisX->setTickCount(5);      // 设置刻度数量
    axisX->setGridLineVisible(false); // 隐藏网格线

    // 设置 Y 轴的属性
    axisY->setLabelFormat("%i");
    axisY->setTickCount(5);
    axisY->setGridLineVisible(false);

    // 将坐标轴添加到图表
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);


    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setInteractive(true);
    chartView->setParent(this);

    QPixmap pixmap(":/new/prefix1/images/014 Amy Crisp.png");
    QPixmap scaledPixmap = pixmap.scaled(700, 700, Qt::AspectRatioMode::KeepAspectRatio);
    QBrush brush(scaledPixmap);
    chart->setBackgroundBrush(brush);
    ans=new QLabel(this);
    // ans->setStyleSheet("background-color: black; color: white;");

    ans->setStyleSheet(
        "background-color: white;"  // 不知道什么色背景
        "color: royalblue;"            // 亮黄色文字
        "font-size: 24px;"           // 加大字号
        "font-weight: bold;"         // 加粗
        "border: 2px solid lightblue;" // 橙色边框
        "border-radius: 10px;"       // 圆角
        "padding: 12px 20px;"        // 内边距
        );
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(chartView);
    layout->addWidget(ans);
    setFixedSize(600,600);

    // 确保指示器在最上层
    clickIndicator->raise(); // 添加这行

    connect(this,&module3::pointClicked,this,&module3::handlePointclicked);
}

void module3::addData(double x, double y) {
    series->setMarkerSize(0);

    series->append(x, y);

    double maxTempo = axisX->max();
    if (x > maxTempo) {
        axisX->setRange(0, x + 50);
    }

    int maxYear = axisY->max();
    if (static_cast<int>(y) > maxYear) {
        axisY->setRange(1900, static_cast<int>(y) + 10);
    }
}

void module3::mousePressEvent(QMouseEvent *event) {
    // 在鼠标点击处显示圆点 - 添加这行
    showClickIndicatorAtMousePosition(event->pos());

    // 将视图坐标转换为场景坐标
    QPointF clickPos = chartView->mapToScene(event->pos());

    // 将场景坐标转换为图表的数据坐标
    QPointF chartCoords = chartView->chart()->mapToValue(clickPos);
    emit pointClicked(chartCoords.x(), chartCoords.y());
}
void module3::handlePointclicked(float x,float y){
    float mood=x,path=y;
    float speed=60/path;//将配速转化为速度
    MusicPreference t=conversion(choosemood(mood),speed);
    musicinfo song=findyoursong((t.maxBPM+t.minBPM)/2,(t.startDecade+t.endDecade)/2);
    QString texyt = "推荐音乐：";
    texyt += song.name;
    ans->setText(texyt);
}

// 新函数：在鼠标点击位置显示圆点
void module3::showClickIndicatorAtMousePosition(const QPoint& mousePos) {
    // 隐藏之前的指示器
    clickIndicator->hide();

    // 计算位置（使圆点中心对准鼠标点击位置）
    int x = mousePos.x() - clickIndicator->width() / 2;
    int y = mousePos.y() - clickIndicator->height() / 2;

    // 移动并显示新指示器
    clickIndicator->move(x, y);
    clickIndicator->show();
    clickIndicator->raise(); // 确保在最上层

    // 添加淡出动画
    QPropertyAnimation *fadeOut = new QPropertyAnimation(clickIndicator, "windowOpacity");
    fadeOut->setDuration(1000);  // 1秒动画
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);
    fadeOut->start(QAbstractAnimation::DeleteWhenStopped);

    // 动画结束后隐藏圆点(不需要隐藏圆点，故注释掉一部分)
    connect(fadeOut, &QPropertyAnimation::finished, [this]() {
        //clickIndicator->hide();
        clickIndicator->setWindowOpacity(1.0);  // 重置透明度
    });
}

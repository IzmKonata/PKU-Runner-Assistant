#include "chartwidget.h"
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QDebug>
#include <iostream>

ChartWidget::ChartWidget(QWidget *parent) : QWidget(parent) {
    // 创建圆点图片（红色圆形）
    dotPixmap = QPixmap(20, 20);
    dotPixmap.fill(Qt::transparent);

    QPainter painter(&dotPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::red);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(dotPixmap.rect());

    // 创建指示器标签（初始隐藏）
    clickIndicator = new QLabel(this);
    clickIndicator->setPixmap(dotPixmap);
    clickIndicator->setFixedSize(dotPixmap.size());
    clickIndicator->hide();

    series = new QScatterSeries();
    series->setName("音乐偏好");

    chart = new QChart();
    chart->addSeries(series);
    QFont font;
    font.setFamily("Arial");  // 设置字体为 Arial
    font.setPointSize(16);    // 设置字号为 16
    font.setBold(true); // 设置加粗
    chart->setTitleFont(font);  // 应用自定义字体到标题
    chart->setTitle("用户音乐偏好");
    chart->legend()->hide();

    axisX = new QValueAxis();
    axisX->setLabelFormat("%d");
    axisX->setTitleText("歌曲节奏 (BPM)");
    axisX->setRange(0, 200);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis();
    axisY->setLabelFormat("%d");
    axisY->setTitleText("歌曲年代");
    axisY->setRange(1900, 2025);
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

    // 确保clickIndicator显示在图表上方
    clickIndicator->raise();

    QPixmap pixmap(":/new/prefix1/images/024 Near Moon.png");
    QPixmap scaledPixmap = pixmap.scaled(700, 700, Qt::AspectRatioMode::KeepAspectRatio);
    QBrush brush(scaledPixmap);
    chart->setBackgroundBrush(brush);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setFixedSize(600,600);
}

void ChartWidget::addData(double x, double y) {
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

void ChartWidget::mousePressEvent(QMouseEvent *event) {
    // 在鼠标点击处显示圆点（直接使用点击位置）
    showClickIndicatorAtMousePosition(event->pos());

    // 将视图坐标转换为场景坐标
    QPointF clickPos = chartView->mapToScene(event->pos());

    // 将场景坐标转换为图表的数据坐标
    QPointF chartCoords = chartView->chart()->mapToValue(clickPos);

    std::cout << "Mouse position (relative to widget): "
              << event->pos().x() << ", " << event->pos().y() << std::endl;
    std::cout << "Mouse position (in chart coordinates): "
              << chartCoords.x() << ", " << chartCoords.y() << std::endl;

    // 遍历图表中的所有数据系列
    QList<QAbstractSeries *> seriesList = chart->series();
    for (QAbstractSeries *abstractSeries : seriesList) {
        // 检查是否为散点系列
        QScatterSeries *scatterSeries = qobject_cast<QScatterSeries *>(abstractSeries);
        if (scatterSeries) {
            QVector<QPointF> points = scatterSeries->pointsVector();
            for (int i = 0; i < points.size(); ++i) {
                QPointF point = points[i];
                // 计算点击位置与数据点之间的距离
                double distance = abs(chartCoords.x()-point.x())+abs(chartCoords.y()-point.y());
                std::cout << "Distance to point " << i << ": " << distance << std::endl;

                // 如果距离小于阈值，发出信号
                if (distance < 45) {
                    // 使用更合理的阈值
                    std::cout << "Clicked point: ("
                              << point.x() << ", " << point.y()
                              << "), Index: " << i << std::endl;

                    // 保留原有的信号发射
                    emit pointClicked(point.x(), point.y(), i);
                    break;
                }
            }
        }
    }
}

// 新函数：在鼠标点击位置显示圆点
void ChartWidget::showClickIndicatorAtMousePosition(const QPoint& mousePos) {
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

    // 动画结束后隐藏圆点
    connect(fadeOut, &QPropertyAnimation::finished, [this]() {
        //clickIndicator->hide();
        clickIndicator->setWindowOpacity(1.0);  // 重置透明度
    });
}

// 保留原有的showClickIndicator函数
void ChartWidget::showClickIndicator(double x, double y, int index) {
    // 这个函数可以保持为空，或者用于其他目的
    // 因为我们不再使用它来显示圆点
}

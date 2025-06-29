#include "homepage.h"
#include "ui_homepage.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include "RunningRecordManager.h"
#include "mainwindow.h"

Homepage::Homepage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Homepage)
{
    ui->setupUi(this);
    RunningRecordManager manager(MainWindow::getUserName(),this);
    auto recentData = manager.getLastFiveDaysData();
    // 创建数据系列
    QLineSeries *series = new QLineSeries();
    series->append(0, recentData[6]);
    series->append(1, recentData[5]);
    series->append(2, recentData[4]);
    series->append(3, recentData[3]);
    series->append(4, recentData[2]);
    series->append(5, recentData[1]);
    series->append(6, recentData[0]);


    // 创建图表对象
    QChart *chart = new QChart();
    chart->addSeries(series);

    // 设置主标题（带格式）
    chart->setTitle("近一周里程统计");
    chart->setTitleFont(QFont("Arial", 14, QFont::Bold));  // 设置字体
    chart->setTitleBrush(QBrush(Qt::darkBlue));            // 文字颜色

    // 调整用户信息
    ui->nameLabel->setText(MainWindow::getUserName());
    QString heightMessage = "身高: ";
    heightMessage += QString::number(MainWindow::getUserHeight(),'f',1);
    heightMessage += " cm";
    ui->heightLabel->setText(heightMessage);
    QString weightMessage = "体重: ";
    weightMessage += QString::number(MainWindow::getUserWeight(),'f',1);
    weightMessage += " kg";
    ui->weightLabel->setText(weightMessage);
    QString bmiMessage = "BMI: ";
    float bmi = MainWindow::getUserWeight()*10000/MainWindow::getUserHeight()/MainWindow::getUserHeight();
    bmiMessage += QString::number(bmi,'f',1);

    if (bmi>=18.5&&bmi<=24)
    {
        bmiMessage += "(正常)";
    }
    else if (bmi<18.5)
    {
        bmiMessage += "(偏低)";
    }
    else if (bmi>28)
    {
        bmiMessage += "(肥胖)";
    }
    else
    {
        bmiMessage += "(超重)";
    }

    ui->bmiLabel->setText(bmiMessage);


    // 创建并配置X轴
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("天数");                      // X轴名称
    axisX->setTitleFont(QFont("微软雅黑", 10));             // 坐标轴标签字体
    axisX->setLabelsColor(Qt::darkGreen);                  // 标签颜色
    axisX->setRange(0, 6);                                // 坐标范围
    axisX->setTickCount(7);      // (max - min + 1) → 显示 0,1,2,...,10
    axisX->setLabelFormat("%.0f"); // 格式化为无小数位
    chart->setAxisX(axisX, series);                        // 关联到数据系列
    // 创建并配置Y轴
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("里程数(km)");                     // Y轴名称
    axisY->setTitleFont(QFont("微软雅黑", 10));
    axisY->setLabelsAngle(-45);                            // 标签旋转角度
    axisY->setLabelsColor(Qt::darkRed);
    axisY->setRange(0, 10);
    chart->setAxisY(axisY, series);

    // 将图表绑定到视图
    ui->chartView->setChart(chart);
    QPixmap img(":/new/prefix1/images/retouch_2024112900065258.png");
    ui->avatarLabel->setPixmap(img);

    // 设置窗口标题
    setWindowTitle("运动健康中心");


    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(ui->chartView);
    //layout->addWidget(placeholder);
    layout->setContentsMargins(10, 10, 10, 10);

    // 连接按钮信号
    connect(ui->logoutButton, &QPushButton::clicked,
            this, &Homepage::onHistoryButtonClicked);

    // 设置窗口背景为白色
    this->setStyleSheet("background-color: white;"
                        "QLabel, QPushButton { color: black;}");
}

void Homepage::onHistoryButtonClicked()
{
    this->close();
}

Homepage::~Homepage()
{
    delete ui;
}

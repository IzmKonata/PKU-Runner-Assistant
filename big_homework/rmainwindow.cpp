
#include "ui_rmainwindow.h"
#include "scheduledialog.h"
#include "runplandialog.h"
#include <QMessageBox>
#include <QModelIndexList>
#include <random>
#include <cmath>
#include <algorithm>
#include<QMainWindow>
#include"runplandialog.h"
RMainWindow::RMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RMainWindow)
    , model(new ScheduleModel(this))
{
    ui->setupUi(this);

    // 初始化主界面
    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->setDefaultSectionSize(40);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // 连接信号槽
    connect(ui->addButton, &QPushButton::clicked, this, &RMainWindow::onAddButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &RMainWindow::onDeleteSelected);
    connect(ui->generateButton, &QPushButton::clicked, this, &RMainWindow::generateRunningPlan);
    weekLabel = new QLabel(this);
    ui->statusBar->addWidget(weekLabel);

    QToolButton *prevBtn = new QToolButton;
    prevBtn->setText("◀");
    connect(prevBtn, &QToolButton::clicked, this, &RMainWindow::onPrevWeek);

    QToolButton *nextBtn = new QToolButton;
    nextBtn->setText("▶");
    connect(nextBtn, &QToolButton::clicked, this, &RMainWindow::onNextWeek);

    ui->statusBar->addPermanentWidget(prevBtn);
    ui->statusBar->addPermanentWidget(nextBtn);
    updateWeekLabel();
    model->setCurrentWeek(QDate::currentDate().addDays(-(QDate::currentDate().dayOfWeek()-1)));
}

RMainWindow::~RMainWindow()
{
    delete ui;
}

void RMainWindow::onAddButtonClicked()
{
    ScheduleDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        QDateTime start = dlg.startDateTime();
        int duration = dlg.duration();
        QString task = dlg.task();

        if (task.isEmpty()) {
            QMessageBox::warning(this, tr("警告"), tr("任务内容不能为空！"));
            return;
        }

        model->addSchedule(ScheduleItem(start, duration, task));
    }
}

void RMainWindow::onDeleteSelected()
{
    QModelIndexList selected = ui->tableView->selectionModel()->selectedRows();
    if(!selected.isEmpty()) {
        int row = selected.first().row();
        model->removeSchedule(row);
    }
}

double RMainWindow::calculatePace(double weight, double height)
{
    // 计算VO2Max估计值（简化版）
    double bmi = weight / ((height/100)*(height/100));
    double vo2max = 50.0 - 0.3 * bmi; // 基础VO2Max

    // 根据VO2Max计算配速（分钟/公里）
    double pace = 3.0 + (50.0 - vo2max) * 0.2;

    // 限制在合理范围内 (4-10 min/km)
    return qBound(4.0, pace, 10.0);
}

QList<TrainingDay> RMainWindow::generateScientificPlan(double totalKm, int days, double maxDaily)
{
    QList<TrainingDay> plan;
    plan.reserve(days);

    // 基础参数
    const int baseDays = qMax(7, days); // 至少7天周期
    const int weeks = ceil(static_cast<double>(days) / 7.0);
    const double weeklyIncrease = 0.1; // 每周跑量增加10%

    // 训练周期模板 (3周循环: 积累-强度-恢复)
    const QVector<Trainingintensity> weeklyTemplate = {
        // 周一, 周二, 周三, 周四, 周五, 周六, 周日
        REST, EASY_RUN, TEMPO_RUN, EASY_RUN, REST, LONG_RUN, REST,
        REST, INTERVAL, EASY_RUN, TEMPO_RUN, REST, LONG_RUN, REST,
        REST, EASY_RUN, EASY_RUN, EASY_RUN, REST, EASY_RUN, REST  // 恢复周
    };

    // 计算基础周跑量
    double baseWeeklyKm = totalKm / (weeks * (1 + weeklyIncrease * (weeks - 1) / 2.0));

    // 生成每日计划
    double remainingKm = totalKm;
    for (int week = 0; week < weeks; ++week) {
        double weeklyKm = baseWeeklyKm * (1.0 + weeklyIncrease * week);
        weeklyKm = qMin(weeklyKm, remainingKm);

        // 分配周内跑量
        double longRunPercent = 0.25 + 0.05 * (week % 3); // 长距离跑占25-30%
        double tempoRunPercent = 0.20;
        double intervalPercent = 0.15;
        double easyRunPercent = 1.0 - longRunPercent - tempoRunPercent - intervalPercent;

        double longRunKm = weeklyKm * longRunPercent;
        double tempoRunKm = weeklyKm * tempoRunPercent;
        double intervalKm = weeklyKm * intervalPercent;
        double easyRunKm = weeklyKm * easyRunPercent;

        for (int dayInWeek = 0; dayInWeek < 7; ++dayInWeek) {
            int globalDay = week * 7 + dayInWeek;
            if (globalDay >= days) break;

            Trainingintensity intensity = weeklyTemplate[(week % 3) * 7 + dayInWeek];
            TrainingDay day;
            day.intensity = intensity;

            switch (intensity) {
            case LONG_RUN:
                day.distance = qMin(longRunKm, maxDaily);
                day.description = "长距离跑";
                longRunKm -= day.distance;
                break;
            case TEMPO_RUN:
                day.distance = qMin(tempoRunKm, maxDaily * 0.8); // 节奏跑距离稍短
                day.description = "节奏跑";
                tempoRunKm -= day.distance;
                break;
            case INTERVAL:
                day.distance = qMin(intervalKm, maxDaily * 0.6); // 间歇跑距离最短
                day.description = "间歇训练";
                intervalKm -= day.distance;
                break;
            case EASY_RUN:
                day.distance = qMin(easyRunKm, maxDaily * 0.7); // 轻松跑中等距离
                day.description = "轻松跑";
                easyRunKm -= day.distance;
                break;
            case REST:
            default:
                day.distance = 0.0;
                day.description = "休息日";
                break;
            }

            // 确保距离合理
            day.distance = qBound(0.0, day.distance, maxDaily);
            plan.append(day);
            remainingKm -= day.distance;
        }
    }

    // 最后一天确保完成总距离
    if (remainingKm > 0.1) {
        TrainingDay& lastDay = plan.last();
        if (lastDay.intensity != REST) {
            lastDay.distance += qMin(remainingKm, maxDaily - lastDay.distance);
            remainingKm -= qMin(remainingKm, maxDaily - lastDay.distance);
        }
    }

    // 分配剩余里程（如有）
    if (remainingKm > 0.1) {
        // 优先分配到轻松跑日
        for (int i = plan.size() - 1; i >= 0 && remainingKm > 0.1; --i) {
            if (plan[i].intensity == EASY_RUN && plan[i].distance < maxDaily * 0.9) {
                double canAdd = qMin(remainingKm, maxDaily * 0.9 - plan[i].distance);
                plan[i].distance += canAdd;
                remainingKm -= canAdd;
            }
        }

        // 其次分配到节奏跑日
        for (int i = plan.size() - 1; i >= 0 && remainingKm > 0.1; --i) {
            if (plan[i].intensity == TEMPO_RUN && plan[i].distance < maxDaily * 0.85) {
                double canAdd = qMin(remainingKm, maxDaily * 0.85 - plan[i].distance);
                plan[i].distance += canAdd;
                remainingKm -= canAdd;
            }
        }
    }

    return plan;
}

void RMainWindow::generateRunningPlan()
{
    runplandialog dlg(this);
    if(dlg.exec() == QDialog::Accepted) {
        // 获取参数
        double weight = dlg.weight();
        double height = dlg.height();
        double remainingKm = dlg.remainingKm();
        int maxMinutes = dlg.maxDailyMinutes();
        QDate endDate = dlg.targetDate();

        // 验证日期
        int totalDays = QDate::currentDate().daysTo(endDate);
        if(totalDays < 1) {
            QMessageBox::warning(this, "错误", "目标日期必须晚于当前日期");
            return;
        }

        // 计算配速和能力
        double pace = calculatePace(weight, height);
        double maxDailyKm = maxMinutes * pace / 60.0; // 单日最大距离(km)

        // 生成科学训练计划
        QList<TrainingDay> dailyPlan = generateScientificPlan(remainingKm, totalDays, maxDailyKm);

        // 清空现有计划并添加新计划
        model->clearSchedules();

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> hourDist(17, 19); // 17-19点之间
        std::uniform_int_distribution<> colorDist(100, 200);

        for(int i = 0; i < totalDays; ++i) {
            const TrainingDay& day = dailyPlan[i];
            if(day.distance > 0.1) {
                QDate runDate = QDate::currentDate().addDays(i);

                // 根据训练类型生成不同时间
                int hour = 17;
                switch(day.intensity) {
                case LONG_RUN: hour = 8;  // 长距离跑安排在上午
                    break;
                case TEMPO_RUN: hour = 18; // 节奏跑傍晚
                    break;
                case INTERVAL: hour = 17; // 间歇训练下午
                    break;
                case EASY_RUN: hour = hourDist(gen); // 轻松跑随机时间
                    break;
                default: hour = hourDist(gen);
                }

                QTime runTime(hour, 0);

                // 根据训练类型生成颜色
                QColor runColor;
                switch(day.intensity) {
                case LONG_RUN: runColor = QColor(65, 105, 225); // 蓝色
                    break;
                case TEMPO_RUN: runColor = QColor(220, 20, 60); // 红色
                    break;
                case INTERVAL: runColor = QColor(255, 140, 0);  // 橙色
                    break;
                case EASY_RUN: runColor = QColor(34, 139, 34);  // 绿色
                    break;
                default: runColor = QColor(200, 200, 200);      // 灰色
                }

                // 计算训练时间
                int minutes = qMin(maxMinutes, static_cast<int>(day.distance / pace * 60.0));

                // 创建计划项
                ScheduleItem item(
                    QDateTime(runDate, runTime),
                    minutes,
                    QString("%1：%2km (%3分钟)").arg(day.description).arg(day.distance, 0, 'f', 1).arg(minutes),
                    runColor
                    );

                model->addSchedule(item);
            }
        }

        // 刷新模型
        model->setCurrentWeek(model->currentWeekStart());
        adjustWeekDisplay();

        // 显示成功消息
        QMessageBox::information(this, "计划生成",
                                 QString("已生成科学的跑步训练计划！\n总距离：%1km\n训练天数：%2/%3")
                                     .arg(remainingKm, 0, 'f', 1)
                                     .arg(model->getSchedules().size())
                                     .arg(totalDays));
    }
}

void RMainWindow::adjustWeekDisplay()
{
    QDate firstRunDate = QDate::currentDate();
    QDate weekStart = firstRunDate.addDays(-firstRunDate.dayOfWeek() + 1);
    model->setCurrentWeek(weekStart);
    updateWeekLabel();
}

void RMainWindow::onPrevWeek()
{
    QDate newWeek = model->currentWeekStart().addDays(-7);
    model->setCurrentWeek(newWeek);
    updateWeekLabel();
}

void RMainWindow::onNextWeek()
{
    QDate newWeek = model->currentWeekStart().addDays(7);
    model->setCurrentWeek(newWeek);
    updateWeekLabel();
}

void RMainWindow::updateWeekLabel()
{
    QDate end = model->currentWeekStart().addDays(6);
    weekLabel->setText(QString("当前显示周次：%1 - %2")
                           .arg(model->currentWeekStart().toString("yyyy-MM-dd"))
                           .arg(end.toString("yyyy-MM-dd")));
}

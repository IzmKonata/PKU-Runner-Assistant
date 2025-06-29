#include "RunningCalendarModule.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDoubleValidator>
#include <QDate>

RunningCalendarModule::RunningCalendarModule(const QString &accountName, QWidget *parent)
    : QWidget(parent)
    , calendar(nullptr)
    , m_currentDate(QDate::currentDate())
    , m_recordManager(accountName) // 使用账号名初始化记录管理器
{
    createUI();
    setupConnections();

    // 初始化日历
    refreshCalendar();

    // 选择当前日期
    calendar->setSelectedDate(m_currentDate);
    onDateSelected(m_currentDate);
}

RunningCalendarModule::~RunningCalendarModule()
{
    // UI 元素会自动被父对象删除
}

void RunningCalendarModule::setAccountName(const QString &accountName)
{
    m_recordManager.setAccountName(accountName);
    refreshCalendar();
    onDateSelected(m_currentDate);
    accountLabel->setText("账号: " + accountName);
}

void RunningCalendarModule::createUI()
{
    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // 添加账号显示标签
    accountLabel = new QLabel("账号: " + m_recordManager.accountName(), this);
    accountLabel->setAlignment(Qt::AlignRight);
    QFont accountFont = accountLabel->font();
    accountFont.setBold(true);
    accountLabel->setFont(accountFont);
    accountLabel->setStyleSheet("color: #2c3e50;");

    // 日历和数据输入区域（水平布局）
    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->setSpacing(15);

    // 左侧：日历
    QGroupBox *calendarGroup = new QGroupBox("跑步日历", this);
    QVBoxLayout *calendarLayout = new QVBoxLayout(calendarGroup);
    calendar = new RunningCalendarWidget(calendarGroup);
    calendarLayout->addWidget(calendar);
    contentLayout->addWidget(calendarGroup, 2); // 2/3宽度

    // 右侧：数据输入
    QGroupBox *dataGroup = new QGroupBox("跑步数据", this);
    QVBoxLayout *dataLayout = new QVBoxLayout(dataGroup);
    dataLayout->setSpacing(10);

    // 日期标签
    dateLabel = new QLabel(m_currentDate.toString("yyyy年MM月dd日 dddd"), dataGroup);
    QFont dateFont = dateLabel->font();
    dateFont.setPointSize(14);
    dateFont.setBold(true);
    dateLabel->setFont(dateFont);
    dateLabel->setAlignment(Qt::AlignCenter);

    // 距离输入
    QHBoxLayout *distanceLayout = new QHBoxLayout();
    distanceLayout->addWidget(new QLabel("跑步距离 (公里):", dataGroup));
    distanceEdit = new QLineEdit(dataGroup);
    distanceEdit->setPlaceholderText("输入跑步距离...");
    distanceEdit->setValidator(new QDoubleValidator(0, 100, 1, this)); // 限制0-100，1位小数
    distanceLayout->addWidget(distanceEdit);

    // 备注
    QVBoxLayout *notesLayout = new QVBoxLayout();
    notesLayout->addWidget(new QLabel("备注:", dataGroup));
    notesEdit = new QTextEdit(dataGroup);
    notesEdit->setPlaceholderText("记录跑步心得或路线...");
    notesLayout->addWidget(notesEdit);

    // 按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    saveButton = new QPushButton("保存数据", dataGroup);
    deleteButton = new QPushButton("删除数据", dataGroup);
    exportButton = new QPushButton("导出数据", dataGroup);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(exportButton);

    dataLayout->addWidget(dateLabel);
    dataLayout->addLayout(distanceLayout);
    dataLayout->addLayout(notesLayout);
    dataLayout->addLayout(buttonLayout);
    contentLayout->addWidget(dataGroup, 1); // 1/3宽度

    // 添加账号标签到主布局
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addStretch(); // 添加弹性空间
    topLayout->addWidget(accountLabel);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(contentLayout, 4); // 4/5高度

    // 底部：统计
    QGroupBox *statsGroup = new QGroupBox("月度统计", this);
    QVBoxLayout *statsLayout = new QVBoxLayout(statsGroup);

    statsLabel = new QLabel("本月统计:  跑步天数: 0  总距离: 0公里  平均: 0公里  最长: 0公里", statsGroup);
    progressBar = new QProgressBar(statsGroup);
    progressBar->setTextVisible(true);
    progressBar->setFormat("月度完成度: %p%");

    statsLayout->addWidget(statsLabel);
    statsLayout->addWidget(progressBar);

    mainLayout->addWidget(statsGroup, 1); // 1/5高度

    // 设置按钮样式
    saveButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; }");
    deleteButton->setStyleSheet("QPushButton { background-color: #f44336; color: white; }");
    exportButton->setStyleSheet("QPushButton { background-color: #2196F3; color: white; }");

    // 进度条样式
    progressBar->setStyleSheet(
        "QProgressBar {"
        "   border: 1px solid #B0BEC5;"
        "   border-radius: 5px;"
        "   background: white;"
        "   text-align: center;"
        "}"
        "QProgressBar::chunk {"
        "   background-color: #42A5F5;"
        "   border-radius: 5px;"
        "}"
        );
}

void RunningCalendarModule::setupConnections()
{
    connect(calendar, &RunningCalendarWidget::dateClicked,
            this, &RunningCalendarModule::onDateSelected);
    connect(calendar, &QCalendarWidget::currentPageChanged,
            this, &RunningCalendarModule::onCalendarPageChanged);
    connect(saveButton, &QPushButton::clicked,
            this, &RunningCalendarModule::onSaveButtonClicked);
    connect(deleteButton, &QPushButton::clicked,
            this, &RunningCalendarModule::onDeleteButtonClicked);
    connect(exportButton, &QPushButton::clicked,
            this, &RunningCalendarModule::onExportButtonClicked);
    connect(&m_recordManager, &RunningRecordManager::dataChanged,
            this, &RunningCalendarModule::onRunDataChanged);
}

void RunningCalendarModule::refreshCalendar()
{
    int year = calendar->yearShown();
    int month = calendar->monthShown();
    calendar->setRunData(m_recordManager.getMonthlyData(year, month));
    updateStats();
}

void RunningCalendarModule::onDateSelected(const QDate &date)
{
    m_currentDate = date;
    dateLabel->setText(date.toString("yyyy年MM月dd日 dddd"));

    if (m_recordManager.hasRecord(date)) {
        distanceEdit->setText(QString::number(m_recordManager.getRunDistance(date), 'f', 1));
        notesEdit->setText(m_recordManager.getRunNotes(date));
        deleteButton->setEnabled(true);
    } else {
        distanceEdit->clear();
        notesEdit->clear();
        deleteButton->setEnabled(false);
    }
}

void RunningCalendarModule::onRunDataChanged()
{
    refreshCalendar();
    onDateSelected(m_currentDate);
}

void RunningCalendarModule::onSaveButtonClicked()
{
    bool ok;
    double distance = distanceEdit->text().toDouble(&ok);

    if (!ok || distance <= 0) {
        QMessageBox::warning(this, "输入错误", "请输入有效的跑步距离（大于0）");
        return;
    }

    QString notes = notesEdit->toPlainText();

    if (m_recordManager.hasRecord(m_currentDate)) {
        m_recordManager.updateRunRecord(m_currentDate, distance, notes);
    } else {
        m_recordManager.addRunRecord(m_currentDate, distance, notes);
    }

    deleteButton->setEnabled(true);
}

void RunningCalendarModule::onDeleteButtonClicked()
{
    if (!m_recordManager.hasRecord(m_currentDate)) {
        return;
    }

    // 创建自定义样式的消息框
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("确认删除");
    msgBox.setText("确定要删除" + m_currentDate.toString("yyyy-MM-dd") + "的跑步记录吗？");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    // 设置白色背景样式表
    msgBox.setStyleSheet(
        "QMessageBox {"
        "   background-color: white;"  // 白色背景
        "}"
        "QLabel {"
        "   color: #333333;"          // 深灰色文字
        "   font-size: 14px;"
        "}"
        "QPushButton {"
        "   background-color: #f0f0f0;"  // 按钮背景
        "   color: #333333;"             // 按钮文字
        "   border: 1px solid #cccccc;"  // 边框
        "   border-radius: 4px;"         // 圆角
        "   padding: 6px 12px;"          // 内边距
        "   min-width: 80px;"            // 最小宽度
        "}"
        "QPushButton:hover {"
        "   background-color: #e0e0e0;"  // 悬停效果
        "}"
        );

    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
        m_recordManager.removeRunRecord(m_currentDate);
    }
}

void RunningCalendarModule::onCalendarPageChanged(int year, int month)
{
    Q_UNUSED(year);
    Q_UNUSED(month);
    refreshCalendar();
}

void RunningCalendarModule::onExportButtonClicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "导出跑步数据",
                                                    QDir::homePath() + "/running_data.csv",
                                                    "CSV文件 (*.csv)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "导出错误", "无法创建文件: " + fileName);
        return;
    }

    QTextStream out(&file);
    out << "日期,距离(km),备注\n";

    auto allData = m_recordManager.getAllData();
    for (auto it = allData.constBegin(); it != allData.constEnd(); ++it) {
        out << it.key().toString("yyyy-MM-dd") << ","
            << QString::number(it.value(), 'f', 1) << ","
            << m_recordManager.getRunNotes(it.key()) << "\n";
    }

    file.close();
    QMessageBox::information(this, "导出成功", "跑步数据已成功导出到: " + fileName);
}

void RunningCalendarModule::updateStats()
{
    int year = calendar->yearShown();
    int month = calendar->monthShown();

    int daysRun = m_recordManager.monthlyDays(year, month);
    double totalDistance = m_recordManager.monthlyTotal(year, month);
    double avgDistance = m_recordManager.monthlyAverage(year, month);
    double maxDistance = m_recordManager.monthlyMax(year, month);

    statsLabel->setText(
        QString("本月统计:  跑步天数: %1  总距离: %2公里  平均: %3公里  最长: %4公里")
            .arg(daysRun)
            .arg(totalDistance, 0, 'f', 1)
            .arg(avgDistance, 0, 'f', 1)
            .arg(maxDistance, 0, 'f', 1)
        );

    // 计算月度完成度（假设目标是20天）
    int targetDays = 20;
    int progress = (daysRun * 100) / targetDays;
    if (progress > 100) progress = 100;

    progressBar->setValue(progress);
}

#include "RunningRecordManager.h"
#include <QSettings>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

RunningRecordManager::RunningRecordManager(const QString &accountName, QObject *parent)
    : QObject(parent), m_accountName(accountName)
{
    loadData();
}

// 设置账号名
void RunningRecordManager::setAccountName(const QString &accountName)
{
    if (m_accountName != accountName) {
        // 保存当前账号数据
        saveData();

        // 切换账号
        m_accountName = accountName;

        // 清除内存数据
        m_runData.clear();
        m_runNotes.clear();

        // 加载新账号数据
        loadData();

        emit dataChanged();
    }
}

// 获取账号特定的配置路径
QString RunningRecordManager::getAccountConfigPath() const
{
    // 获取应用数据存储路径
    QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    if(configPath.isEmpty()) {
        configPath = QDir::homePath() + "/.MyFitnessApp";
    }

    // 添加账号名子目录
    if (!m_accountName.isEmpty()) {
        configPath += "/accounts/" + m_accountName;
    } else {
        // 如果没有账号名，使用默认目录
        configPath += "/default";
    }

    return configPath;
}

void RunningRecordManager::addRunRecord(const QDate &date, double distance, const QString &notes)
{
    if (distance <= 0) {
        qWarning() << "Invalid distance value:" << distance;
        return;
    }

    m_runData[date] = distance;
    m_runNotes[date] = notes;
    saveData();
    emit dataChanged();
}

void RunningRecordManager::updateRunRecord(const QDate &date, double distance, const QString &notes)
{
    if (m_runData.contains(date)) {
        m_runData[date] = distance;
        m_runNotes[date] = notes;
        saveData();
        emit dataChanged(); // 发出数据变化信号
    }
}

void RunningRecordManager::removeRunRecord(const QDate &date)
{
    if (m_runData.contains(date)) {
        m_runData.remove(date);
        m_runNotes.remove(date);
        saveData();
        emit dataChanged(); // 发出数据变化信号
    }
}

double RunningRecordManager::getRunDistance(const QDate &date) const
{
    return m_runData.value(date, 0.0);
}

QString RunningRecordManager::getRunNotes(const QDate &date) const
{
    return m_runNotes.value(date, "");
}

bool RunningRecordManager::hasRecord(const QDate &date) const
{
    return m_runData.contains(date);
}

QMap<QDate, double> RunningRecordManager::getMonthlyData(int year, int month) const
{
    QMap<QDate, double> monthlyData;
    QDate startDate(year, month, 1);
    QDate endDate = startDate.addMonths(1).addDays(-1);

    for (auto it = m_runData.constBegin(); it != m_runData.constEnd(); ++it) {
        if (it.key() >= startDate && it.key() <= endDate) {
            monthlyData[it.key()] = it.value();
        }
    }

    return monthlyData;
}

QMap<QDate, double> RunningRecordManager::getAllData() const
{
    return m_runData;
}

double RunningRecordManager::monthlyTotal(int year, int month) const
{
    double total = 0.0;
    auto monthlyData = getMonthlyData(year, month);
    for (double distance : monthlyData.values()) {
        total += distance;
    }
    return total;
}

double RunningRecordManager::monthlyAverage(int year, int month) const
{
    auto monthlyData = getMonthlyData(year, month);
    if (monthlyData.isEmpty()) return 0.0;

    double total = monthlyTotal(year, month);
    return total / monthlyData.size();
}

double RunningRecordManager::monthlyMax(int year, int month) const
{
    double maxDistance = 0.0;
    auto monthlyData = getMonthlyData(year, month);
    for (double distance : monthlyData.values()) {
        if (distance > maxDistance) {
            maxDistance = distance;
        }
    }
    return maxDistance;
}

int RunningRecordManager::monthlyDays(int year, int month) const
{
    return getMonthlyData(year, month).size();
}

void RunningRecordManager::loadData()
{
    // 获取账号特定的配置路径
    QString configPath = getAccountConfigPath();

    // 确保目录存在
    QDir().mkpath(configPath);

    // 使用INI文件存储
    QSettings settings(configPath + "/running_records.ini", QSettings::IniFormat);

    qDebug() << "Loading data for account:" << m_accountName
             << "from:" << settings.fileName();

    int size = settings.beginReadArray("runRecords");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        QDate date = settings.value("date").toDate();
        double distance = settings.value("distance").toDouble();
        QString notes = settings.value("notes").toString();

        if (date.isValid() && distance > 0) {
            m_runData[date] = distance;
            m_runNotes[date] = notes;
        }
    }
    settings.endArray();

    qDebug() << "Loaded" << m_runData.size() << "records for account:" << m_accountName;
}

void RunningRecordManager::saveData() const
{
    // 获取账号特定的配置路径
    QString configPath = getAccountConfigPath();

    // 确保目录存在
    QDir().mkpath(configPath);

    QSettings settings(configPath + "/running_records.ini", QSettings::IniFormat);

    qDebug() << "Saving data for account:" << m_accountName
             << "to:" << settings.fileName();

    settings.beginWriteArray("runRecords");

    int index = 0;
    for (auto it = m_runData.constBegin(); it != m_runData.constEnd(); ++it) {
        settings.setArrayIndex(index++);
        settings.setValue("date", it.key());
        settings.setValue("distance", it.value());
        settings.setValue("notes", m_runNotes.value(it.key()));
    }

    settings.endArray();
}

std::array<float, 7> RunningRecordManager::getLastFiveDaysData() const
{
    std::array<float, 7> result = {0, 0, 0, 0, 0, 0, 0}; // 初始化为0

    QDate today = QDate::currentDate();

    // 获取最近7天日期（包括今天）
    for (int i = 0; i < 7; i++) {
        QDate date = today.addDays(-i); // 今天(0) -> 昨天(-1) -> 前天(-2) ...

        // 检查该日期是否有记录
        if (m_runData.contains(date)) {
            result[i] = static_cast<float>(m_runData[date]);
        }
        // 如果没有记录，保持0值
    }

    return result;
}

#ifndef RUNNINGRECORDMANAGER_H
#define RUNNINGRECORDMANAGER_H

#include <QObject>
#include <QMap>
#include <QDate>
#include <array>
#include <QString>

class RunningRecordManager : public QObject
{
    Q_OBJECT
public:
    // 修改构造函数，接受账号名参数
    explicit RunningRecordManager(const QString &accountName, QObject *parent = nullptr);

    // 添加账号名设置方法
    void setAccountName(const QString &accountName);

    std::array<float, 7> getLastFiveDaysData() const;

    void addRunRecord(const QDate &date, double distance, const QString &notes = "");
    void updateRunRecord(const QDate &date, double distance, const QString &notes = "");
    void removeRunRecord(const QDate &date);

    double getRunDistance(const QDate &date) const;
    QString getRunNotes(const QDate &date) const;
    bool hasRecord(const QDate &date) const;

    QMap<QDate, double> getMonthlyData(int year, int month) const;
    QMap<QDate, double> getAllData() const;

    double monthlyTotal(int year, int month) const;
    double monthlyAverage(int year, int month) const;
    double monthlyMax(int year, int month) const;
    int monthlyDays(int year, int month) const;

    void loadData();
    void saveData() const;

    // 添加获取账号名的方法
    QString accountName() const { return m_accountName; }

signals:
    void dataChanged();

private:
    QString m_accountName; // 存储账号名
    QMap<QDate, double> m_runData;
    QMap<QDate, QString> m_runNotes;

    // 获取账号特定的配置路径
    QString getAccountConfigPath() const;
};

#endif // RUNNINGRECORDMANAGER_H

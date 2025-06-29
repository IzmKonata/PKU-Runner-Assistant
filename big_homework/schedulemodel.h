#ifndef SCHEDULEMODEL_H
#define SCHEDULEMODEL_H

#include <QAbstractTableModel>
#include "ScheduleItem.h"

class ScheduleModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit ScheduleModel(QObject *parent = nullptr);

    // 必须实现的虚函数
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // 自定义方法
    void addSchedule(const ScheduleItem &item);
    void clearSchedules();
    QList<ScheduleItem> getSchedules() const;
    void removeSchedule(int index);
    void setCurrentWeek(const QDate& weekStart);
    QDate currentWeekStart() const;

private:
    QList<ScheduleItem> m_schedules;
    QDate m_currentWeekStart;
};

#endif // SCHEDULEMODEL_H

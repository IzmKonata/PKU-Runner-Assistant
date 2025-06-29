#include "schedulemodel.h"
#include <QBrush>

ScheduleModel::ScheduleModel(QObject *parent)
    : QAbstractTableModel(parent)
{}

int ScheduleModel::rowCount(const QModelIndex &) const { return 24; } // 24小时
int ScheduleModel::columnCount(const QModelIndex &) const { return 7; } // 7天

QVariant ScheduleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    const int hour = index.row();
    const int dayOfWeek = index.column() + 1; // 列索引转Qt的周日历(1=周一)
    const QDate weekEnd = m_currentWeekStart.addDays(6); // 本周日

    foreach (const ScheduleItem &item, m_schedules) {
        const QDateTime start = item.start();
        const QDate itemDate = start.date();

        // 检查是否在显示周范围内
        if(itemDate < m_currentWeekStart || itemDate > weekEnd)
            continue;

        // 检查星期是否匹配
        if(itemDate.dayOfWeek() != dayOfWeek)
            continue;

        // 检查时间段
        QTime itemStart = start.time();
        QTime itemEnd = item.endTime().time();
        QTime cellStart(hour, 0);
        QTime cellEnd(hour, 59, 59);

        if (itemStart <= cellEnd && itemEnd >= cellStart) {
            switch (role) {
            case Qt::DisplayRole:
                return item.task();
            case Qt::BackgroundRole:
                return QBrush(item.color());
            case Qt::ToolTipRole:
                return tr("%1 - %2\n%3")
                    .arg(itemStart.toString("hh:mm"))
                    .arg(itemEnd.toString("hh:mm"))
                    .arg(item.task());
            }
        }
    }
    return QVariant();
}

QVariant ScheduleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return tr("周一");
        case 1: return tr("周二");
        case 2: return tr("周三");
        case 3: return tr("周四");
        case 4: return tr("周五");
        case 5: return tr("周六");
        case 6: return tr("周日");
        }
    } else {
        return QString("%1:00").arg(section, 2, 10, QLatin1Char('0'));
    }
    return QVariant();
}

void ScheduleModel::addSchedule(const ScheduleItem &item)
{
    beginInsertRows(QModelIndex(), m_schedules.size(), m_schedules.size());
    m_schedules.append(item);
    endInsertRows();
}

void ScheduleModel::clearSchedules()
{
    beginResetModel();
    m_schedules.clear();
    endResetModel();
}

QList<ScheduleItem> ScheduleModel::getSchedules() const
{
    return m_schedules;
}

void ScheduleModel::removeSchedule(int index)
{
    if(index >=0 && index < m_schedules.size()) {
        beginRemoveRows(QModelIndex(), index, index);
        m_schedules.removeAt(index);
        endRemoveRows();
    }
}

void ScheduleModel::setCurrentWeek(const QDate &weekStart)
{
    beginResetModel();
    m_currentWeekStart = weekStart;
    endResetModel();
}

QDate ScheduleModel::currentWeekStart() const
{
    return m_currentWeekStart;
}

#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H

#include <QDateTime>
#include <QColor>

class ScheduleItem
{
public:
    ScheduleItem(QDateTime start, int duration, QString task, QColor color = Qt::cyan)
        : m_start(start), m_duration(duration), m_task(task), m_color(color) {}

    QDateTime start() const { return m_start; }
    int duration() const { return m_duration; }
    QString task() const { return m_task; }
    QColor color() const { return m_color; }

    QDateTime endTime() const {
        return m_start.addSecs(m_duration * 60); // 分钟转秒
    }

private:
    QDateTime m_start;
    int m_duration;
    QString m_task;
    QColor m_color;
};

#endif // SCHEDULEITEM_H

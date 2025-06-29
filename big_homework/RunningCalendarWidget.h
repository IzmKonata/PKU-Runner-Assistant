#ifndef RUNNINGCALENDARWIDGET_H
#define RUNNINGCALENDARWIDGET_H

#include <QCalendarWidget>
#include <QMap>
#include <QDate>
#include <QPainter>

class RunningCalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    explicit RunningCalendarWidget(QWidget *parent = nullptr);

    void setRunData(const QMap<QDate, double> &data);
    void clearRunData();

signals:
    void dateClicked(const QDate &date);

protected:
    // 修改参数类型为 QDate (值传递) 而不是 const QDate&
    void paintCell(QPainter *painter, const QRect &rect, QDate date) const override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QMap<QDate, double> m_runData;
};

#endif // RUNNINGCALENDARWIDGET_H

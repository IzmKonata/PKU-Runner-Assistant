#include "RunningCalendarWidget.h"

RunningCalendarWidget::RunningCalendarWidget(QWidget *parent)
    : QCalendarWidget(parent)
{
    setGridVisible(true);
    setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    // 添加浅色样式表
    setStyleSheet(
        "QCalendarWidget QWidget {"
        "   background-color: #FFFFFF;"
        "   color: #333333;"
        "}"
        "QCalendarWidget QToolButton {"
        "   background-color: #f0f0f0;"
        "   color: #333333;"
        "   font-weight: bold;"
        "}"
        "QCalendarWidget QMenu {"
        "   background-color: white;"
        "}"
        "QCalendarWidget QAbstractItemView:enabled {"
        "   background-color: #FFFFFF;"
        "   color: #333333;"
        "   selection-background-color: #4CAF50;"
        "   selection-color: white;"
        "}"
        "QCalendarWidget #qt_calendar_navigationbar {"
        "   background-color: #f0f0f0;"
        "}"
        );
}

void RunningCalendarWidget::setRunData(const QMap<QDate, double> &data)
{
    m_runData = data;
    updateCells();
}

void RunningCalendarWidget::clearRunData()
{
    m_runData.clear();
    updateCells();
}

// 修改参数类型为 QDate (值传递)
void RunningCalendarWidget::paintCell(QPainter *painter, const QRect &rect, QDate date) const
{
    // 首先调用基类的实现
    QCalendarWidget::paintCell(painter, rect, date);

    if (m_runData.contains(date)) {
        double distance = m_runData[date];
        QColor bgColor = QColor(173, 216, 230); // Light blue

        if (distance >= 10.0) {
            bgColor = QColor(100, 149, 237); // Cornflower blue
        } else if (distance >= 5.0) {
            bgColor = QColor(70, 130, 180); // Steel blue
        }

        painter->fillRect(rect.adjusted(1, 1, -1, -1), bgColor);

        painter->setPen(Qt::black);
        painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));

        if (distance > 0) {
            painter->setPen(Qt::darkBlue);
            QFont font = painter->font();
            font.setPointSize(8);
            painter->setFont(font);
            painter->drawText(rect, Qt::AlignBottom | Qt::AlignRight,
                              QString::number(distance, 'f', 1) + " km");
        }
    }
}

void RunningCalendarWidget::mousePressEvent(QMouseEvent *event)
{
    QCalendarWidget::mousePressEvent(event);
    QDate clickedDate = selectedDate();
    if (clickedDate.isValid()) {
        emit dateClicked(clickedDate);
    }
}

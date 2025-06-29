#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <qlabel.h>


class ChartWidget : public QWidget {
    Q_OBJECT

public:
    ChartWidget(QWidget *parent = nullptr);

    void addData(double x, double y);

signals:
    void pointClicked(double x, double y, int index);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void showClickIndicator(double x, double y, int index);  // 显示点击指示器的槽函数
    void showClickIndicatorAtMousePosition(const QPoint& mousePos);

private:
    QChart *chart;
    QChartView *chartView;
    QScatterSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QLabel *clickIndicator;  // 用于显示圆点的标签
    QPixmap dotPixmap;       // 圆点图片
};

#endif // CHARTWIDGET_H

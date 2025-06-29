#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QMainWindow>
#include <QtCharts>

namespace Ui {
class Homepage;
}

class Homepage : public QMainWindow
{
    Q_OBJECT

public:
    explicit Homepage(QWidget *parent = nullptr);
    ~Homepage();

private slots:
    void onHistoryButtonClicked();

private:
    Ui::Homepage *ui;
    QChartView *chartView;  // 对应UI中的对象
    QLineSeries *series;
    QChart *chart;
};

#endif // HOMEPAGE_H

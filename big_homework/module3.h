
#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include<QLabel>

class module3 : public QWidget {
    Q_OBJECT

public:
    module3(QWidget *parent = nullptr);

    void addData(double x, double y);
private slots:
    void handlePointclicked(float x,float y);
    void showClickIndicatorAtMousePosition(const QPoint& mousePos);
signals:
    void pointClicked(double x, double y);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QChart *chart;
    QChartView *chartView;
    QScatterSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QLabel* ans;

    QLabel *clickIndicator;  // 用于显示圆点的标签
    QPixmap dotPixmap;       // 圆点图片
};


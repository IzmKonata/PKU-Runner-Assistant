

#include <QMainWindow>
#include <QLabel>
#include "schedulemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RMainWindow; }
QT_END_NAMESPACE

// 训练强度类型
enum Trainingintensity {
    REST,
    EASY_RUN,
    TEMPO_RUN,
    INTERVAL,
    LONG_RUN
};

// 训练日结构
struct TrainingDay {
    double distance;
    Trainingintensity intensity;
    QString description;
};

class RMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RMainWindow(QWidget *parent = nullptr);
    ~RMainWindow();

private slots:
    void onAddButtonClicked();
    void onDeleteSelected();
    void generateRunningPlan();
    void onPrevWeek();
    void onNextWeek();
    void updateWeekLabel();
    void adjustWeekDisplay();
    QList<TrainingDay> generateScientificPlan(double totalKm, int days, double maxDaily);

private:
    Ui::RMainWindow *ui;
    ScheduleModel *model;
    double calculatePace(double weight, double height);
    QLabel *weekLabel;
};



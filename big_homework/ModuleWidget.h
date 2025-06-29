#ifndef MODULEWIDGET_H
#define MODULEWIDGET_H
#include<rmainwindow.h>
#include <QWidget>
#include <QPushButton>
#include"placerecommend.h"
#include<QStackedWidget>
#include"module3main.h"
#include"homepage.h"
#include"RunningCalendarModule.h"
class ModuleWidget : public QMainWindow {
    Q_OBJECT

public:
    void createhome();
    ModuleWidget(QMainWindow *parent = nullptr);
    PlaceRecommend* A;
    QStackedWidget *allinhere;
    module3main*C;
    RunningCalendarModule *B;
    Homepage *D;
    QVBoxLayout *layout;
signals:
    void module1Clicked();
    void module2Clicked();
    void module3Clicked();

private slots:
    void onModule1Clicked();
    void onModule2Clicked();
    void onModule3Clicked();
    void onhomepageclicked();

private:
    QPushButton *buttonModule1;
    QPushButton *buttonModule2;
    QPushButton *buttonModule3;
    QPushButton *homepage;
};

#endif // MODULEWIDGET_H

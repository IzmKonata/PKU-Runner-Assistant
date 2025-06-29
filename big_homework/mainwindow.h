#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "loginwidget.h"
#include "registerwidget.h"
#include"ModuleWidget.h"
#include <QString>
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    static QString getUserName();
    static float getUserHeight();
    static float getUserWeight();
    ~MainWindow();

private slots:
    void onLoginClicked(const QString &username, const QString &password);
    void onRegisterClicked();
    void onRegisterCompleted(const QString &username, const QString &password,
                             const QStringList &musicGenres, const QString &gender,
                             const QString &height, const QString &weight);
    void onBackToLoginClicked();
    void onPointClicked(double x, double y);

private:
    ModuleWidget *modulewidget;
    QStackedWidget *stackedWidget;
    LoginWidget *loginWidget;
    RegisterWidget *registerWidget;
    QWidget *homeWidget;
    QLabel *labelWelcome;
    QPushButton *buttonLogout;
    QMap<QString, QString> users;
};
extern QString usrnamet;

extern float heightt;

extern float weightt;
#endif // MAINWINDOW_H

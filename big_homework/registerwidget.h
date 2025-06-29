#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>
#include "chartwidget.h"

class RegisterWidget : public QWidget {
    Q_OBJECT

public:
    RegisterWidget(QWidget *parent = nullptr);
    ChartWidget* getChartWidget() const;

signals:
    void registerCompleted(const QString &username, const QString &password,
                           const QStringList &musicGenres, const QString &gender,
                           const QString &height, const QString &weight);
    void backToLoginClicked();

private slots:
    void onRegisterClicked();
    void onBackToLoginClicked();

private:
    QLineEdit *lineEditUser;
    QLineEdit *lineEditPass;
    QLineEdit *lineEditConfirmPass;
    QLineEdit *lineEditHeight;
    QLineEdit *lineEditWeight;
    QPushButton *buttonRegister;
    QPushButton *buttonBackToLogin;
    QCheckBox *checkBoxPop;
    QCheckBox *checkBoxRock;
    QCheckBox *checkBoxJazz;
    QCheckBox *checkBoxClassic;
    QCheckBox *checkBoxElectronic;
    QRadioButton *radioButtonMale;
    QRadioButton *radioButtonFemale;
    QRadioButton *radioButtonOther;
    ChartWidget *chartWidget;
};

#endif // REGISTERWIDGET_H

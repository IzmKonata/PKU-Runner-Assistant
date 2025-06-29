#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class LoginWidget : public QWidget {
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr);
    bool verifyUserFromExcel(const QString &username,const QString & password);
signals:
    void loginClicked(const QString &username, const QString &password);
    void registerClicked();

private slots:
    void onLoginClicked();
    void onRegisterClicked();

private:
    QLineEdit *lineEditUser;
    QLineEdit *lineEditPass;
    QPushButton *buttonLogin;
    QPushButton *buttonRegister;
};

#endif // LOGINWIDGET_H

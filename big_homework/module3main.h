#ifndef MODULE3MAIN_H
#define MODULE3MAIN_H

#include <QWidget>
#include"module3.h"
namespace Ui {
class module3main;
}

class module3main : public QWidget
{
    Q_OBJECT

public:
    module3*C;
    explicit module3main(QWidget *parent = nullptr);
    ~module3main();

private:
    Ui::module3main *ui;
};

#endif // MODULE3MAIN_H

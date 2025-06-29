#include "module3main.h"
#include "ui_module3main.h"

module3main::module3main(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::module3main)
{
    ui->setupUi(this);
    C=new module3(this);

}

module3main::~module3main()
{
    delete ui;
}

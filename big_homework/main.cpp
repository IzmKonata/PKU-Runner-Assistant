#include <QApplication>
#include "mainwindow.h"
#include<iostream>
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(800, 600);
    window.show();

    return app.exec();
}

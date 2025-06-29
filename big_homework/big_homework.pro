QT       += core gui charts  # 确保包含 charts 模块

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += \
    ModuleWidget.cpp \
    RunningCalendarModule.cpp \
    RunningCalendarWidget.cpp \
    RunningRecordManager.cpp \
    chartwidget.cpp \
    fivefourplayground.cpp \
    homepage.cpp \
    jingyuan.cpp \
    langrun.cpp \
    lijiao.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    module3.cpp \
    module3main.cpp \
    placerecommend.cpp \
    purefunction.cpp \
    registerwidget.cpp \
    rmainwindow.cpp \
    runplandialog.cpp \
    scheduledialog.cpp \
    schedulemodel.cpp \
    weiming_lake.cpp

HEADERS += \
    ModuleWidget.h \
    RunningCalendarModule.h \
    RunningCalendarWidget.h \
    RunningRecordManager.h \
    ScheduleItem.h \
    chartwidget.h \
    fivefourplayground.h \
    homepage.h \
    jingyuan.h \
    langrun.h \
    lijiao.h \
    loginwidget.h \
    mainwindow.h \
    module3.h \
    module3main.h \
    placerecommend.h \
    purefunction.h \
    registerwidget.h \
    rmainwindow.h \
    runplandialog.h \
    scheduledialog.h \
    schedulemodel.h \
    weiming_lake.h

FORMS += \
    ModuleWidget.ui \
    chartwidget.ui \
    fivefourplayground.ui \
    homepage.ui \
    jingyuan.ui \
    langrun.ui \
    lijiao.ui \
    loginwidget.ui \
    mainwindow.ui \
    module3.ui \
    module3main.ui \
    placerecommend.ui \
    registerwidget.ui \
    rmainwindow.ui \
    runplandialog.ui \
    scheduledialog.ui \
    weiming_lake.ui


# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./QXlsx/         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./QXlsx/header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./QXlsx/source/  # current QXlsx source path is ./source/
include(./QXlsx/QXlsx.pri)

TRANSLATIONS += \
    big_homework_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

RESOURCES += \
    backmodule.qrc \
    res.qrc

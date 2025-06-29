#ifndef RUNNINGCALENDARMODULE_H
#define RUNNINGCALENDARMODULE_H

#include <QWidget>
#include "RunningCalendarWidget.h"
#include "RunningRecordManager.h"

class QLabel;
class QLineEdit;
class QTextEdit;
class QPushButton;
class QProgressBar;
class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;

class RunningCalendarModule : public QWidget
{
    Q_OBJECT

public:
    explicit RunningCalendarModule(const QString &accountName, QWidget *parent = nullptr);
    ~RunningCalendarModule();

    void refreshCalendar();
    void setAccountName(const QString &accountName);

public slots:
    void onDateSelected(const QDate &date);
    void onRunDataChanged();

private slots:
    void onSaveButtonClicked();
    void onDeleteButtonClicked();
    void onCalendarPageChanged(int year, int month);
    void onExportButtonClicked();

private:
    void updateStats();
    void createUI();
    void setupConnections();

    RunningCalendarWidget *calendar;
    RunningRecordManager m_recordManager;
    QDate m_currentDate;

    // UI elements
    QLabel *accountLabel; // 添加账号标签
    QLabel *dateLabel;
    QLineEdit *distanceEdit;
    QTextEdit *notesEdit;
    QPushButton *saveButton;
    QPushButton *deleteButton;
    QPushButton *exportButton;
    QLabel *statsLabel;
    QProgressBar *progressBar;
};

#endif // RUNNINGCALENDARMODULE_H

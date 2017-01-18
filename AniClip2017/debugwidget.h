#ifndef DEBUGWIDGET_H
#define DEBUGWIDGET_H

#include <QWidget>

namespace logger {
class Logger;
}

class ClipDatabase;

namespace Ui {
class DebugWidget;
}

class DebugWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DebugWidget(logger::Logger* nLog, ClipDatabase* db, QWidget *parent = 0);
    ~DebugWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DebugWidget *ui;

    logger::Logger *log;
    ClipDatabase *clipDB;
};

#endif // DEBUGWIDGET_H

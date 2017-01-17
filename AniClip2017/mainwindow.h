#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

namespace logger {
class Logger;
}

namespace Ui {
class MainWindow;
}

class ClipDatabase;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool init(QString config_filename);
    QString getError();


private:
    Ui::MainWindow *ui;
    logger::Logger *log;

    QStackedWidget *centralStack;
    ClipDatabase *clipDatabase;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class DebugWidget;
class AddTextScreen;
class ViewScreen;

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
    void closeEvent(QCloseEvent *event);

    bool init(QString config_filename);
    QString getError();


public slots:
    //void setMainScreen();
    //void setAddScreen();
    //void setVideoAddScreen();

private:
    Ui::MainWindow *ui;
    logger::Logger *log;

    ClipDatabase *clipDatabase;

    QStackedWidget *centralStack;


    DebugWidget *debugWidget;
    AddTextScreen *addTextScreen;
    ViewScreen *viewScreen;

};

#endif // MAINWINDOW_H

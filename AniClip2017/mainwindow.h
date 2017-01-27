#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class DebugWidget;
class EditScreen;
class ViewScreen;
class MainScreen;
class AddScreen;

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
    void setEditScreen();
    void setViewScreen();
    void setMenuScreen();
    void setAddScreen();

private:
    Ui::MainWindow *ui;
    logger::Logger *log;

    ClipDatabase *clipDatabase;

    QStackedWidget *centralStack;


    DebugWidget     *debugWidget;
    EditScreen      *editScreen;
    ViewScreen      *viewScreen;
    MainScreen      *menuScreen;
    AddScreen       *addScreen;

    int             editScreen_index;
    int             viewScreen_index;
    int             menuScreen_index;
    int             addScreen_index;
};

#endif // MAINWINDOW_H

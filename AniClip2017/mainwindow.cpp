#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clipdatabase.h"
#include "logger.h"

#include "clipinfoedit.h"
#include "ui_clipinfoedit.h"

#include "debugwidget.h"
#include "ui_debugwidget.h"

#include <QStringListModel>
#include <QMessageBox>
#include <QFileDialog>

#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    log(NULL),
    clipDatabase(NULL),
    centralStack(NULL),
    debugWidget(NULL)
{
    ui->setupUi(this);
    log = new logger::Logger(this);

    centralStack = new QStackedWidget(this);
    setCentralWidget(centralStack);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* /*event*/) {

    clipDatabase->save();
}

bool MainWindow::init(QString config_filename)
{
    bool initSuccess_flag = true;

    if (log != NULL) {

        //Init Clip Database
        {
            bool clipDbSuccess_flag = false;

            clipDatabase = new ClipDatabase(log, this);
            if (clipDatabase != NULL) {
                if (clipDatabase->init(config_filename)) {
                    clipDbSuccess_flag = true;
                }
                else {
                    log->err("MainWindow.init(): Failed to initialize ClipDatabase.");
                }


                debugWidget = new DebugWidget(log, clipDatabase, this);
                centralStack->addWidget(debugWidget);
                centralStack->setCurrentIndex(0);
            }

            initSuccess_flag &= clipDbSuccess_flag;
        }
    }
    else {
        initSuccess_flag = false;
    }

    return initSuccess_flag;

}

QString MainWindow::getError() {
    QString rString = "";

    if (log != NULL) {
        rString = log->getLogError();
    }
    else {
        rString = "Logger failed to initialize.";
    }

    return  rString;
}



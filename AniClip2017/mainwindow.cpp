#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clipdatabase.h"
#include "logger.h"

#include "clipinfoedit.h"

#include "debugwidget.h"
#include "editscreen.h"
#include "viewscreen.h"
#include "tagtreewidget.h"
#include "mainscreen.h"
#include "addscreen.h"

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
    debugWidget(NULL),
    editScreen(NULL),
    viewScreen(NULL),
    menuScreen(NULL),
    addScreen(NULL),
    editScreen_index(-1),
    viewScreen_index(-1),
    menuScreen_index(-1),
    addScreen_index(-1)
{
    ui->setupUi(this);
    log = new logger::Logger(this);

    centralStack = ui->centralStack;

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


                editScreen = new EditScreen(this);
                if (editScreen->init(config_filename)) {
                    editScreen_index = centralStack->addWidget(editScreen);
                    connect(ui->editScreen_button, SIGNAL(clicked(bool)), this, SLOT(setEditScreen()));
                }

                menuScreen = new MainScreen(this);
                if (menuScreen->init(config_filename)) {
                    menuScreen_index = centralStack->addWidget(menuScreen);
                    connect(ui->menuScreen_button, SIGNAL(clicked(bool)), this, SLOT(setMenuScreen()));
                }

                viewScreen = new ViewScreen(log, this);
                if (viewScreen->init(config_filename, clipDatabase)) {
                    viewScreen_index = centralStack->addWidget(viewScreen);
                    connect(ui->viewScreen_button, SIGNAL(clicked(bool)), this, SLOT(setViewScreen()));
                }

                addScreen = new AddScreen(this);
                if (addScreen->init(config_filename)) {
                    addScreen_index = centralStack->addWidget(addScreen);
                    connect(ui->addScreen_button, SIGNAL(clicked(bool)), this, SLOT(setAddScreen()));
                }


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

void MainWindow::setEditScreen() {
    if (editScreen_index != -1) {
        centralStack->setCurrentIndex(editScreen_index);
        ui->pageTitle_label->setText("Edit Clips");
    }
}

void MainWindow::setViewScreen() {
    if (viewScreen_index != -1) {
        centralStack->setCurrentIndex(viewScreen_index);
        viewScreen->updateInfo();
        ui->pageTitle_label->setText("View Clips");
    }
}

void MainWindow::setMenuScreen() {
    if (menuScreen_index != -1) {
        centralStack->setCurrentIndex(menuScreen_index);
        ui->pageTitle_label->setText("Menu");
    }
}

void MainWindow::setAddScreen() {
    if (addScreen_index != -1) {
        centralStack->setCurrentIndex(addScreen_index);
        ui->pageTitle_label->setText("Add Clips");
    }
}

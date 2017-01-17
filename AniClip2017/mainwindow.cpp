#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clipdatabase.h"
#include "logger.h"

#include "clipinfoedit.h"
#include "ui_clipinfoedit.h"

#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    logger::Logger *log = new logger::Logger(this);

    ClipDatabase *db = new ClipDatabase(this, log);
    TimeBound temp;

    QVector<QString> list1;
    list1 << "Test List 1" << "Test List 2";

    QVector<QString> list2;
    list2 << list1 << "Test List 3";

    db->addNewClip("Test Show 1", 1, temp, list1);
    db->addNewClip("Test Show 2", 1, temp, list2);

    QStringList list;
    list << "Word1" << "Word2" << "Word3";

    QStringListModel *tagModel = new QStringListModel(this);
    tagModel->setStringList(list);

    ui->ClipEdit->setTagCompleterModel(tagModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clipinfoedit.h"
#include "ui_clipinfoedit.h"

#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

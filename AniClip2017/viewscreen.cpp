#include "viewscreen.h"
#include "ui_viewscreen.h"

#include "clipdatabase.h"
#include "logger.h"
#include "tagtreewidget.h"

ViewScreen::ViewScreen(logger::Logger *nLog, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewScreen),
    log(nLog),
    clipDb(NULL)
{
    ui->setupUi(this);

}

ViewScreen::~ViewScreen()
{
    delete ui;
}

bool ViewScreen::init(QString config_filename, ClipDatabase *nDb) {
    bool initSuccess_flag = true;

    if (nDb != NULL) {
        clipDb = nDb;

        ui->tagTreeWidget->setClipDatabase(clipDb);
        ui->tagTreeWidget->setLogger(log);
    }
    else {
        initSuccess_flag = false;
        log->err("ViewScreen.init - ClipDatabase is NULL.");
    }

    config_filename;
    return initSuccess_flag;
}

void ViewScreen::updateInfo() {
    ui->tagTreeWidget->updateTags("");
}

void ViewScreen::on_lineEdit_10_textChanged(const QString &arg1)
{
    ui->tagTreeWidget->updateTags(arg1);
}

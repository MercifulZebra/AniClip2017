#include "debugwidget.h"
#include "ui_debugwidget.h"

#include "logger.h"
#include "clipdatabase.h"

#include <QFileDialog>

DebugWidget::DebugWidget(logger::Logger* nLog, ClipDatabase *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DebugWidget),
    log(nLog),
    clipDB(db)
{
    ui->setupUi(this);
}

DebugWidget::~DebugWidget()
{
    delete ui;
}

void DebugWidget::on_pushButton_clicked()
{
        QString fileString = QFileDialog::getOpenFileName(this, "TestCaption", "", tr("Show Files (*.xml *.txt)"));

        if (!fileString.isEmpty()) {
            if (clipDB->loadShowList(fileString)) {
                log->info("Loaded Shows Successfully.");
            }
            else {
                log->err("Failed to load shows.");
            }
        }
}

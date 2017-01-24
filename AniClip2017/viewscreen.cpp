#include "viewscreen.h"
#include "ui_viewscreen.h"

ViewScreen::ViewScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewScreen)
{
    ui->setupUi(this);
}

ViewScreen::~ViewScreen()
{
    delete ui;
}

void ViewScreen::on_pushButton_7_clicked()
{
    ui->pushButton_7->hide();
    ui->sideWidget->show();
}

void ViewScreen::on_pushButton_6_clicked()
{
    ui->sideWidget->hide();
    ui->pushButton_7->show();
}

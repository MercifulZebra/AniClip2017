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

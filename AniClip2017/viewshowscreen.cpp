#include "viewshowscreen.h"
#include "ui_viewshowscreen.h"

ViewShowScreen::ViewShowScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewShowScreen)
{
    ui->setupUi(this);
}

ViewShowScreen::~ViewShowScreen()
{
    delete ui;
}

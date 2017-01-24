#include "addtextscreen.h"
#include "ui_addtextscreen.h"

AddTextScreen::AddTextScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddTextScreen)
{
    ui->setupUi(this);
}

AddTextScreen::~AddTextScreen()
{
    delete ui;
}

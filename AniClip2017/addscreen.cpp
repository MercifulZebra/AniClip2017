#include "addscreen.h"
#include "ui_addscreen.h"

AddScreen::AddScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddScreen)
{
    ui->setupUi(this);
}

AddScreen::~AddScreen()
{
    delete ui;
}

bool AddScreen::init(QString config_filename) {
    bool initSuccess_flag = true;

    return initSuccess_flag;
}

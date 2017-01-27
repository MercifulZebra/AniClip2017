#include "editscreen.h"
#include "ui_editscreen.h"

EditScreen::EditScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditScreen)
{
    ui->setupUi(this);
}

EditScreen::~EditScreen()
{
    delete ui;
}

bool EditScreen::init(QString config_filename) {
    bool initSuccess_flag = true;

    config_filename;
    return initSuccess_flag;
}

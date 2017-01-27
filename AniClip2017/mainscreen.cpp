#include "mainscreen.h"
#include "ui_mainscreen.h"

MainScreen::MainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainScreen)
{
    ui->setupUi(this);
}

MainScreen::~MainScreen()
{
    delete ui;
}

bool MainScreen::init(QString config_filename) {
    bool initSuccess_flag = true;

    config_filename;
    return initSuccess_flag;
}

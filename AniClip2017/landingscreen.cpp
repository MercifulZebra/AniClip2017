#include "landingscreen.h"
#include "ui_landingscreen.h"

LandingScreen::LandingScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LandingScreen)
{
    ui->setupUi(this);
}

LandingScreen::~LandingScreen()
{
    delete ui;
}

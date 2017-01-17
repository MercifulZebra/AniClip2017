#include "videocontrols.h"
#include "ui_videocontrols.h"

VideoControls::VideoControls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoControls)
{
    ui->setupUi(this);
}

VideoControls::~VideoControls()
{
    delete ui;
}

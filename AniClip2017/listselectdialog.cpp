#include "listselectdialog.h"
#include "ui_listselectdialog.h"

ListSelectDialog::ListSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListSelectDialog)
{
    ui->setupUi(this);
}

ListSelectDialog::~ListSelectDialog()
{
    delete ui;
}

#include "clipinfoedit.h"
#include "ui_clipinfoedit.h"

ClipInfoEdit::ClipInfoEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClipInfoEdit)
{
    ui->setupUi(this);
}

ClipInfoEdit::~ClipInfoEdit()
{
    delete ui;
}

void ClipInfoEdit::setTagCompleterModel(QAbstractItemModel *model) {
    ui->TagLineEdit->localCompleter->setModel(model);
}

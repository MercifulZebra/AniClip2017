#ifndef LISTSELECTDIALOG_H
#define LISTSELECTDIALOG_H

#include <QDialog>

namespace Ui {
class ListSelectDialog;
}

class ListSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ListSelectDialog(QWidget *parent = 0);
    ~ListSelectDialog();

private:
    Ui::ListSelectDialog *ui;
};

#endif // LISTSELECTDIALOG_H

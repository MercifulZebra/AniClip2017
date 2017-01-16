#ifndef CLIPINFOEDIT_H
#define CLIPINFOEDIT_H

#include <QWidget>
#include <QAbstractItemModel>

namespace Ui {
class ClipInfoEdit;
}

class ClipInfoEdit : public QWidget
{
    Q_OBJECT

public:
    explicit ClipInfoEdit(QWidget *parent = 0);
    ~ClipInfoEdit();


    void setTagCompleterModel(QAbstractItemModel *model);

private:
    Ui::ClipInfoEdit *ui;
};

#endif // CLIPINFOEDIT_H

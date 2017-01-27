#ifndef EDITSCREEN_H
#define EDITSCREEN_H

#include <QWidget>

namespace Ui {
class EditScreen;
}

class EditScreen : public QWidget
{
    Q_OBJECT

public:
    explicit EditScreen(QWidget *parent = 0);
    ~EditScreen();

    bool init(QString config_filename);
private:
    Ui::EditScreen *ui;
};

#endif // EDITSCREEN_H

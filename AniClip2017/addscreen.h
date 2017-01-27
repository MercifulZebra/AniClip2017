#ifndef ADDSCREEN_H
#define ADDSCREEN_H

#include <QWidget>

namespace Ui {
class AddScreen;
}

class AddScreen : public QWidget
{
    Q_OBJECT

public:
    explicit AddScreen(QWidget *parent = 0);
    ~AddScreen();

    bool init(QString config_filename);
private:
    Ui::AddScreen *ui;
};

#endif // ADDSCREEN_H

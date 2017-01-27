#ifndef ADDTEXTSCREEN_H
#define ADDTEXTSCREEN_H

#include <QWidget>

namespace Ui {
class AddTextScreen;
}

class AddTextScreen : public QWidget
{
    Q_OBJECT

public:
    explicit AddTextScreen(QWidget *parent = 0);
    ~AddTextScreen();

    bool init(QString config_filename);

private:
    Ui::AddTextScreen *ui;
};

#endif // ADDTEXTSCREEN_H

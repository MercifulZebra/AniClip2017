#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>

namespace Ui {
class MainScreen;
}

class MainScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = 0);
    ~MainScreen();

    bool init(QString config_filename);
private:
    Ui::MainScreen *ui;
};

#endif // MAINSCREEN_H

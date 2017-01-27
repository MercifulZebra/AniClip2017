#ifndef LANDINGSCREEN_H
#define LANDINGSCREEN_H

#include <QWidget>

namespace Ui {
class LandingScreen;
}

class LandingScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LandingScreen(QWidget *parent = 0);
    ~LandingScreen();

private:
    Ui::LandingScreen *ui;
};

#endif // LANDINGSCREEN_H

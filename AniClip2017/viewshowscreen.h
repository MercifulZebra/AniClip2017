#ifndef VIEWSHOWSCREEN_H
#define VIEWSHOWSCREEN_H

#include <QWidget>

namespace Ui {
class ViewShowScreen;
}

class ViewShowScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ViewShowScreen(QWidget *parent = 0);
    ~ViewShowScreen();

private:
    Ui::ViewShowScreen *ui;
};

#endif // VIEWSHOWSCREEN_H

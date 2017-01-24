#ifndef VIEWSCREEN_H
#define VIEWSCREEN_H

#include <QWidget>

namespace Ui {
class ViewScreen;
}

class ViewScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ViewScreen(QWidget *parent = 0);
    ~ViewScreen();

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::ViewScreen *ui;
};

#endif // VIEWSCREEN_H

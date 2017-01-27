#ifndef VIEWSCREEN_H
#define VIEWSCREEN_H

#include <QWidget>

namespace logger {
class Logger;
}

class ClipDatabase;

namespace Ui {
class ViewScreen;
}

class ViewScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ViewScreen(logger::Logger *nLog, QWidget *parent = 0);
    ~ViewScreen();

    bool init(QString config_filename, ClipDatabase *nDb);

    void updateInfo();
private slots:

    void on_lineEdit_10_textChanged(const QString &arg1);

private:
    Ui::ViewScreen *ui;

    logger::Logger *log;
    ClipDatabase *clipDb;
};

#endif // VIEWSCREEN_H

#include "mainwindow.h"
#include <QApplication>
#include <QStringList>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QStringList nArgs = a.arguments();
    QString config_filename = "aniclip_config.txt";

    if (nArgs.count() == 2) {
        config_filename = nArgs.at(1);
    }

    if (w.init(config_filename)) {
        w.show();
        return a.exec();
    }
    else {
        QMessageBox errBox;
        errBox.setIcon(QMessageBox::Critical);
        QString err = w.getError();

        if (err.isEmpty()) {
            err = "Unknown Initialization failure.";
        }

        err.append("\n");
        err.append("Contact author at:");
        err.append("\n");
        err.append("Github: MercifulZebra\n");
        err.append("Reddit: /u/MercifulZebra");
        errBox.setText(err);

        return errBox.exec();
    }
}

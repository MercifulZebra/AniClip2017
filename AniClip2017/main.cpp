#include "mainwindow.h"
#include <QApplication>
#include <QStringList>
#include <QMessageBox>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    a.setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    a.setPalette(darkPalette);

    a.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");


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

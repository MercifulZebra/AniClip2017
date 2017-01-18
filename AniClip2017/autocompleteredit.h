#ifndef AUTOCOMPLETEREDIT_H
#define AUTOCOMPLETEREDIT_H

#include <QLineEdit>
#include <QCompleter>

// A c++ version of DAVID ELENTOK's Python multiple item autocompleter

class AutoCompleterEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit AutoCompleterEdit(QWidget *parent = 0);

    void keyPressEvent(QKeyEvent *event);


    QString textUnderCursor();
    void updateCompleterPopupItems(QString prefix);
    bool nextCompletion();


    QCompleter *localCompleter;
signals:

public slots:
    void insertCompletion(QString);
};

#endif // AUTOCOMPLETEREDIT_H

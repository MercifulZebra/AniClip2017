#include "autocompleteredit.h"
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QTextCursor>

AutoCompleterEdit::AutoCompleterEdit(QWidget *parent) : QLineEdit(parent),
    localCompleter(NULL)
{

    localCompleter = new QCompleter(this);
    localCompleter->setWidget(this);
    localCompleter->setCompletionMode(QCompleter::PopupCompletion);
    localCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    connect(localCompleter, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
}

void AutoCompleterEdit::keyPressEvent(QKeyEvent *e) {
    if (localCompleter && localCompleter->popup()->isVisible()) {
        // The following keys are forwarded by the completer to the widget
       switch (e->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
       default:
           break;
       }
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E); // CTRL+E
    if (!localCompleter || !isShortcut) // do not process the shortcut when we have a completer
        QLineEdit::keyPressEvent(e);

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!localCompleter || (ctrlOrShift && e->text().isEmpty()))
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 3
                      || eow.contains(e->text().right(1)))) {
        localCompleter->popup()->hide();
        return;
    }

    if (completionPrefix != localCompleter->completionPrefix()) {
        localCompleter->setCompletionPrefix(completionPrefix);
        localCompleter->popup()->setCurrentIndex(localCompleter->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(localCompleter->popup()->sizeHintForColumn(0)
                + localCompleter->popup()->verticalScrollBar()->sizeHint().width());
    localCompleter->complete(cr); // popup it up!

//    if (event->key() == Qt::Key_Enter       ||
//            event->key() == Qt::Key_Tab     ||
//            event->key() == Qt::Key_Return  ||
//            event->key() == Qt::Key_Escape) {
//        event->ignore();
//    }

//    QLineEdit::keyPressEvent(event);

//    QString completionPrefix = textUnderCursor();

//    if (completionPrefix != localCompleter->completionPrefix()) {
//        updateCompleterPopupItems(completionPrefix);
//    }
//    if (event->text().length() > 0 && completionPrefix.length() > 0) {
//        localCompleter->complete();
//    }
//    else if (completionPrefix.length() == 0) {
//        localCompleter->popup()->hide();
//    }
}

QString AutoCompleterEdit::textUnderCursor() {
    QString tText = text();
    QString rText = "";

    int i = cursorPosition() - 1;

    while( i >= 0 && tText.at(i) != ' ' && tText.at(i) != ';') {
        rText = tText.at(i) + rText;
        i -=1;
    }

    return rText;
}

void AutoCompleterEdit::updateCompleterPopupItems(QString prefix) {
    localCompleter->setCompletionPrefix(prefix);
    localCompleter->setCurrentRow(0);
}

void AutoCompleterEdit::insertCompletion(QString completion) {

    if (localCompleter->widget() != this)
        return;
    int extra = completion.length() - localCompleter->completionPrefix().length();
    QString extraText = text() + completion.right(extra) + "; ";

    setText(extraText);

}

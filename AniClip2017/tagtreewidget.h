#ifndef TAGTREEWIDGET_H
#define TAGTREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>

#include "clipdatabase.h"

class TagTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TagTreeWidget(QWidget *parent = 0);

    void setClipDatabase(ClipDatabase *db);

    void clearTree();

    void testAdd();
    void testClear();

private:
    ClipDatabase *clipDB;
signals:

public slots:
    void updateTags();
};

#endif // TAGTREEWIDGET_H

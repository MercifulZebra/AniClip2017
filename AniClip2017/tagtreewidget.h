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

    QTreeWidgetItem* getTreeItem();
    QTreeWidgetItem* getTopLvl();


private:
    ClipDatabase *clipDB;

    QVector <QTreeWidgetItem*> old_top;
    QVector <QTreeWidgetItem*> old_items;

    int nTopCount;
    int nItemCount;
signals:

public slots:
    void updateTags();
};

#endif // TAGTREEWIDGET_H

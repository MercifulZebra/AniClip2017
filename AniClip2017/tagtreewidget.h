#ifndef TAGTREEWIDGET_H
#define TAGTREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>

#include "clipdatabase.h"

namespace logger {
class Logger;
}

class TagTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TagTreeWidget(logger::Logger *nLog, QWidget *parent = 0);

    void setClipDatabase(ClipDatabase *db);

    void clearTree();

    void testAdd();
    void testClear();

    QTreeWidgetItem* getTreeItem();
    QTreeWidgetItem* getTopLvl();



private:
    ClipDatabase *clipDB;
    logger::Logger *log;

    QVector <QTreeWidgetItem*> old_top;
    QVector <QTreeWidgetItem*> old_items;

    int nTopCount;
    int nItemCount;
signals:

public slots:
    void updateTags();
};

#endif // TAGTREEWIDGET_H

#include "tagtreewidget.h"

#include <QTreeWidgetItem>

#include <QDebug>
#include <QElapsedTimer>

TagTreeWidget::TagTreeWidget(QWidget *parent) : QTreeWidget(parent),
    clipDB(NULL)
{
    setColumnCount(4);

}

void TagTreeWidget::setClipDatabase(ClipDatabase *db) {
    if (clipDB != NULL) {
        clipDB = db;
        connect(clipDB, SIGNAL(infoUpdated()), this, SLOT(updateTags()));
    }


}

void TagTreeWidget::clearTree() {

}

void TagTreeWidget::updateTags() {
    TagManager *tagMan = clipDB->getTagManager();

}


void TagTreeWidget::testAdd() {

    QElapsedTimer eTimer;

    qDebug () << endl << "Existing Items:::::" << endl << "Top: " << old_top.count() << "Items: " << old_items.count();
    nItemCount = 0;
    nTopCount = 0;
    eTimer.start();
    {
        int rootCount = 10;
        int itemCount = 10;
        for (int i = 0; i < rootCount; i++)
        {
            QTreeWidgetItem *nItem = getTreeItem();
            addTopLevelItem(nItem);
            nItem->setText(0, "Parent");
            nItem->setText(1, QString("%1").arg(i));
            nItem->setText(2, "_");
            nItem->setText(3, "!!");

            for(int j =0; j < itemCount; j++) {
                QTreeWidgetItem *nChild = getTreeItem();
                nItem->addChild(nChild);
                nChild->setText(0, "Child");
                nChild->setText(1, QString("%1_%2").arg(i).arg(j));
                nChild->setText(2, "--");
                nChild->setText(3, "X");
                nItem->addChild(nChild);
            }

        }
    }

    qDebug() << "100 Objects add: "<< eTimer.elapsed();
    eTimer.restart();

    {
        int rootCount = 100;
        int itemCount = 100;
        for (int i = 0; i < rootCount; i++)
        {
            QTreeWidgetItem *nItem = getTreeItem();
            addTopLevelItem(nItem);
            nItem->setText(0, "Parent");
            nItem->setText(1, QString("%1").arg(i));
            nItem->setText(2, "_");
            nItem->setText(3, "!!");

            for(int j =0; j < itemCount; j++) {
                QTreeWidgetItem *nChild = getTreeItem();
                nItem->addChild(nChild);
                nChild->setText(0, "Child");
                nChild->setText(1, QString("%1_%2").arg(i).arg(j));
                nChild->setText(2, "--");
                nChild->setText(3, "X");
                nItem->addChild(nChild);
            }

        }
    }

    qDebug() << "10000 Objects add: "<< eTimer.elapsed();
    qDebug() << "Allocates: " << nTopCount << nItemCount;
    qDebug() << "__________________________________";
    eTimer.restart();
}

void TagTreeWidget::testClear() {

    QElapsedTimer eTimer;
    eTimer.start();
    while(topLevelItemCount() > 0) {
        QTreeWidgetItem* topLvl = takeTopLevelItem(0);

        while (topLvl->childCount() > 0) {
            QTreeWidgetItem* childs = topLvl->takeChild(0);
            old_items.append(childs);
        }
        old_items.append(topLvl);
    }

    clear();
    qDebug() << "Clear Time: "<< eTimer.elapsed();
    eTimer.restart();
}

QTreeWidgetItem* TagTreeWidget::getTopLvl() {
    QTreeWidgetItem* rItem = NULL;
    if (!old_top.isEmpty()) {
        rItem = old_top.takeFirst();
    }

    if (rItem == NULL) {
        rItem = new QTreeWidgetItem(this);
        nTopCount++;
    }

    return rItem;
}

QTreeWidgetItem* TagTreeWidget::getTreeItem() {
    QTreeWidgetItem* rItem = NULL;
    if (!old_items.isEmpty()) {
        rItem = old_items.takeFirst();
    }

    if (rItem == NULL) {
        rItem = new QTreeWidgetItem();
        nItemCount++;
    }

    return rItem;
}

#include "tagtreewidget.h"

#include "logger.h"

#include <QTreeWidgetItem>

#include <QDebug>
#include <QElapsedTimer>
#include <QtAlgorithms>

TagTreeWidget::TagTreeWidget(QWidget *parent) : QTreeWidget(parent),
    clipDB(NULL),
    log(NULL)
{
    setColumnCount(1);

}

void TagTreeWidget::setClipDatabase(ClipDatabase *db) {
    if (db != NULL) {
        clipDB = db;
        connect(clipDB, SIGNAL(infoUpdated(const QString &)), this, SLOT(updateTags(const QString &)));
    }
}

void TagTreeWidget::setLogger(logger::Logger *nLog) {
    log = nLog;
}

void TagTreeWidget::clearTree() {

}

void TagTreeWidget::updateTags(const QString &searchString) {
    QElapsedTimer nTimer;
    nTimer.start();
    TagManager *tagMan = clipDB->getTagManager();

    //qSort(tagMan->groups.begin(), tagMan->groups.end(), compareGroups);

    int numGroupsAdded = 0;
    bool addGroup_flag = false;
    bool addAllTags_flag = false;



    for (int i = 0; i < tagMan->groups.count(); i++) {
        int numTopItems = topLevelItemCount();
        QTreeWidgetItem* nItem = NULL;
        if (i >= numTopItems) {
            nItem = new QTreeWidgetItem(this);
            addTopLevelItem(nItem);
        }
        else{
            nItem = topLevelItem(i);
        }

        addGroup_flag = false;
        addAllTags_flag = false;
        if (searchString.isEmpty()) {
            addGroup_flag = true;
            addAllTags_flag = true;
        }

        if (nItem != NULL) {
            TagGroup *cGroup = tagMan->groups.at(i);
            QString cName = cGroup->getName();
            QStringList cTags = cGroup->getTags();
            int numTags = 0;

            if (cName.contains(searchString, Qt::CaseInsensitive)) {
                addGroup_flag = true;
                addAllTags_flag = true;
            }

            //qSort(cTags.begin(), cTags.end(), compareTags);

            for (int j = 0; j < cTags.count(); j++) {
                QTreeWidgetItem *nChild = NULL;
                int numItems = nItem->childCount();

                if (addAllTags_flag || cTags.contains(searchString, Qt::CaseInsensitive)) {

                    if (j >= numItems) {
                        nChild = new QTreeWidgetItem();
                        nItem->addChild(nChild);
                    }
                    else {
                        nChild = nItem->child(numTags);
                    }

                    if (nChild != NULL) {
                        nItem->addChild(nChild);
                        nChild->setText(0, cTags.at(j));
                        nChild->setHidden(false);
                        addGroup_flag = true;
                        numTags++;
                    }
                    else {
                        log->err(QString("Unable to create child for TagGroup %1").arg(cName));
                    }
                }
            }

            if (addGroup_flag) {
                log->info(QString("Showed %1 group").arg(cName));
                nItem->setHidden(false);
                if (numTags < nItem->childCount()) {
                    for (int t = numTags; t < nItem->childCount(); t++) {
                        nItem->child(t)->setHidden(true);
                    }
                }

            }
            else {
                nItem->setHidden(true);
                log->info(QString("Hid %1 group").arg(cName));
            }

            QString groupName = QString("%1 (%2 tags)").arg(cName).arg(numTags);
            nItem->setText(0, groupName);
        }
        else {
            log->err(QString("Unable to create new Top Level TagTreeItem."));
        }
    }

    log->info(QString("TagUpdate took %1 seconds").arg(nTimer.elapsed()/1000.0,4,'f',2));

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

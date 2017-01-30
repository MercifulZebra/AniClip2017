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

                if (addAllTags_flag || cTags.at(j).contains(searchString, Qt::CaseInsensitive)) {

                    if (j >= numItems) {
                        nChild = new QTreeWidgetItem();
                        nItem->addChild(nChild);
                    }
                    else {
                        nChild = nItem->child(numTags);
                    }

                    if (nChild != NULL) {
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
                nItem->setHidden(false);
                if (numTags < nItem->childCount()) {
                    for (int t = numTags; t < nItem->childCount(); t++) {
                        nItem->child(t)->setHidden(true);
                    }
                }

            }
            else {
                nItem->setHidden(true);
            }

            QString groupName = QString("%1 (%2 tags)").arg(cName).arg(numTags);
            nItem->setText(0, groupName);
        }
        else {
            log->err(QString("Unable to create new Top Level TagTreeItem."));
        }
    }

    //log->info(QString("TagUpdate took %1 seconds").arg(nTimer.elapsed()/1000.0,4,'f',2));

}

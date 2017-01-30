#include "cliptreewidget.h"
#include "logger.h"
#include "clipdatabase.h"

#include <QElapsedTimer>
#include <QDebug>
#include <QHeaderView>

ClipTreeWidget::ClipTreeWidget(QWidget *parent) : QTreeWidget(parent),
    clipDB(NULL),
    log(NULL)
{
}

void ClipTreeWidget::setClipDatabase(ClipDatabase *db) {
    if (db != NULL) {
        clipDB = db;
    }
}

void ClipTreeWidget::setLogger(logger::Logger *nLog) {
    log = nLog;
}

void ClipTreeWidget::clearSearchParams() {

    showKey.clear();
    epStartRange = 0;
    epEndRange = 0;
    seasonKey = 0;
    yearKey = 0;

    sStartTime.setHMS(0,0,0,0);
    sEndtime.setHMS(0,0,0,0);

    lengthLowBound = 0;
    lengthHighBound = 0;

    noteKey.clear();

    keyTags.clear();
    subTags.clear();

    setColumnCount(9);
    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
}

bool ClipTreeWidget::clipIsValid(Clip *nClip) {
    return true;
}

void ClipTreeWidget::updateTreeItem(QTreeWidgetItem *nItem, Clip *nClip) {
    nItem->setText(0, nClip->showName);
    nItem->setText(1, QString::number(nClip->epNum));
    nItem->setText(2, QString("Bounds"));
    nItem->setText(3, QString("Season %1").arg(nClip->year));
    nItem->setText(4, nClip->tags.join("; "));
    nItem->setText(5, QString("Link"));
    nItem->setText(6, nClip->note);
}

void ClipTreeWidget::setShowKey(QString nShow) {
    showKey = nShow;
}

void ClipTreeWidget::setEpStartRange(int nStart) {
    epStartRange = nStart;
}

void ClipTreeWidget::setEpEndRange(int nEnd) {
    epEndRange = nEnd;
}

void ClipTreeWidget::setSeason(int nSeason) {
    seasonKey = nSeason;
}

void ClipTreeWidget::setYearKey(int nYear) {
    yearKey = nYear;
}

void ClipTreeWidget::setStartTime(QString nStart) {
    sStartTime.fromString(nStart);
}

void ClipTreeWidget::setEndtime(QString nEnd) {
    sEndtime.fromString(nEnd);
}

void ClipTreeWidget::setLengthLowBound(int nLow) {
   lengthLowBound = nLow;
}

void ClipTreeWidget::setLengthHighBound(int nHigh) {
    lengthHighBound = nHigh;
}

void ClipTreeWidget::setNoteKey(QString nKey) {
    noteKey = nKey;
}

void ClipTreeWidget::addKeyTag(QString nTag) {
    keyTags.append(nTag);
}

void ClipTreeWidget::setKeyTags(QStringList nTags) {
    keyTags.clear();
    keyTags.append(nTags);
}

void ClipTreeWidget::addSubTag(QString nTag) {
    subTags.append(nTag);
}

void ClipTreeWidget::setSubTags(QStringList nTags) {
    subTags.clear();
    subTags.append(nTags);
}

void ClipTreeWidget::updateClips(const QString &searchString) {
    QElapsedTimer nTimer;
    nTimer.start();

    QVector<ClipList*> listsToShow;

    if (clipDB->main_list->isVisible()) {
        listsToShow.append(clipDB->main_list);
    }
    else {
        for (int i = 0; i < clipDB->sub_lists.count(); i++) {
            if (clipDB->sub_lists.at(i)->isVisible()) {
                listsToShow.append(clipDB->sub_lists.at(i));
            }
        }
    }

    int numLists = 0;

    for (int i = 0; i < listsToShow.count(); i++) {
        int numTopItems = topLevelItemCount();
        QTreeWidgetItem* nItem = NULL;
        if (i >= numTopItems) {
            nItem = new QTreeWidgetItem(this);
            addTopLevelItem(nItem);
        }
        else{
            nItem = topLevelItem(i);
        }

        numLists++;
        nItem->setHidden(false);

        int numShows = 0;

        for (int j = 0; j < listsToShow.at(i)->shows.count(); j++) {
            ShowList* cShow = listsToShow.at(i)->shows.at(j);
            bool addShow_flag = false;
            int numClips = 0;

            if (cShow->getName().contains(showKey, Qt::CaseInsensitive)) {
                QTreeWidgetItem *nShow = NULL;
                if (j >= nItem->childCount()) {
                    nShow = new QTreeWidgetItem();
                    nItem->addChild(nShow);
                }
                else {
                    nShow = nItem->child(j);
                }

                for (int k = 0; k < cShow->clips.count(); k++) {
                    Clip* cClip = cShow->clips.at(k);

                    if (clipIsValid(cClip)) {

                        QTreeWidgetItem *nClip = NULL;
                        if (k >= nShow->childCount()) {
                            nClip = new QTreeWidgetItem();
                            nShow->addChild(nClip);
                        }
                        else {
                            nClip = nShow->child(k);
                        }

                        if (nClip != NULL) {
                            updateTreeItem(nClip, cClip);
                            nShow->setHidden(false);
                            addShow_flag = true;
                            numClips++;
                        }

                    }
                    else {
                        nShow->child(k)->setHidden(true);
                    }
                }

                if (addShow_flag) {
                    numShows++;
                    nShow->setHidden(false);
                    nShow->setText(0, QString("%1 (%2 Clips)").arg(cShow->getName()).arg(numClips));

                    if (numClips < nShow->childCount()) {
                        for (int t = numClips; t < nShow->childCount(); t++) {
                            nShow->child(t)->setHidden(true);
                        }
                    }
                }
                else {
                    nShow->setHidden(true);
                }
            }
        }

        nItem->setText(0, QString("%1 (%2 Shows)").arg(listsToShow.at(i)->getName()).arg(numShows));
        nItem->setHidden(false);

        for (int t = numShows; t < nItem->childCount(); t++) {
            nItem->child(t)->setHidden(true);
        }
    }

    for (int t = numLists; t < topLevelItemCount(); t++) {
        topLevelItem(t)->setHidden(true);
    }

    expandAll();

}

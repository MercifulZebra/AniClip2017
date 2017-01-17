#include "clipdatabase.h"
#include "logger.h"

#include <QDebug>
#include <QString>

Clip::Clip(QObject *parent) : QObject(parent)
{

}

void Clip::setShowName(QString nShowName) {
    showName = nShowName;
}

void Clip::setEpNum(int nEpNum) {
    epNum = nEpNum;
}

void Clip::setTimeBound(TimeBound nTimeBound) {
    bounds.startTime    = nTimeBound.startTime;
    bounds.endTime      = nTimeBound.endTime;
}

ShowList::ShowList(QObject *parent) : QObject(parent)
{

}

ClipList::ClipList(QObject *parent) : QObject(parent)
{

}

bool ClipList::addClip(Clip *nClip) {
    bool addSuccess_flag = true;


    return addSuccess_flag;
}

QString ClipList::getName() {
    return listName;
}

void ClipList::setName(QString nName) {
    listName = nName;
}

ClipDatabase::ClipDatabase(QObject *parent, logger::Logger *nLog) : QObject(parent),
    log(nLog)
{

}

bool ClipDatabase::init() {
    bool initSuccess_flag = true;

    if (log != NULL) {

    }
    else {
        qDebug () << "ERROR - ClipDatabase.init :: Logger not valid.";
        initSuccess_flag = false;
    }

    return initSuccess_flag;
}

Clip* ClipDatabase::addNewClip(QString showName, int epNum, TimeBound time, QVector<QString> nLists) {

    int numListsAdded = 0;
    Clip* rClip = new Clip(this);

    rClip->setShowName(showName);
    rClip->setEpNum(epNum);
    rClip->setTimeBound(time);

    if (main_list->addClip(rClip)) {

        //Add to composite list of clips
        used_clips.append(rClip);

        QVector<ClipList*> remainingLists = sub_lists;
        QMutableVectorIterator<ClipList*> list(remainingLists);

        while(list.hasNext()) {
            list.next();
            QMutableVectorIterator<QString> tLists(nLists);
            while (tLists.hasNext()) {
                if (tLists.next() == list.value()->getName()) {
                    list.value()->addClip(rClip);
                    numListsAdded++;
                    tLists.remove();
                }
            }

        }

        if (!nLists.empty()) {
            for (int i = 0; i < nLists.count(); i++) {
                ClipList* nList = new ClipList(this);
                nList->setName(nLists.at(i));
                sub_lists.append(nList);

                QString test = QString("Created new list \"%1\".").arg(nList->getName());
                log->info(test);
                nList->addClip(rClip);
                numListsAdded++;
            }
        }

        log->info(QString("Added Clip to %1 additional lists.").arg(numListsAdded));

    }
    else {
        log->warn("Clip already exists.");

        delete rClip;
        rClip = NULL;

    }

    return rClip;
}

void  ClipDatabase::addExistingClip(Clip* nClip, QVector<ClipList*> nLists) {

}

#include "clipdatabase.h"
#include "logger.h"

#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>

TagGroup::TagGroup(logger::Logger *nLog, QObject *parent) : QObject(parent),
log(nLog)
{

}

bool TagGroup::setName(QString nName) {
    groupName = nName;
}

bool TagGroup::addTag(QString nTag) {
    bool addSuccess_flag = false;
    if (!groupTags.contains(nTag)) {
        groupTags.append(nTag);
        addSuccess_flag = true;
    }
    return addSuccess_flag;
}

bool TagGroup::removeTag(QString nTag) {
    bool removeSuccess_flag = false;
    if (groupTags.removeOne(nTag)) {
        removeSuccess_flag = true;
    }
    return removeSuccess_flag;
}

bool TagGroup::addGroup(TagGroup oGroup) {
    QStringList nTags = oGroup.getTags();
    int numAdded = 0;
    for (int i = 0; i < nTags.count(); i++) {
        if (addTag(nTags.at(i))) {
            numAdded++;
        }
    }
    log->info(QString("Added %1 new tags to %2 group").arg(numAdded).arg(groupName));

    return true;
}

QStringList TagGroup::getTags() {
    return groupTags;
}

QString TagGroup::getName() {
    return groupName;
}

TagManager::TagManager(logger::Logger *nLog, QObject *parent) : QObject(parent),
    log(nLog)
{

}

bool TagManager::readTagLine(QString line) {
    bool rFlag = true;
    QStringList split = line.split(":");

    if (split.count() == 2) {
        if (split.at(0).startsWith("name=")) {
            QString nName = split.at(0).right(split.at(0).length() - 5);
        }
    }
    else {
        log->warn(QString("Invalid tag line: \"%1\"").arg(line));
        rFlag = false;
    }

    return rFlag;
}

bool TagManager::containsGroup(QString nName) {
    bool rFlag = false;

    for (int i = 0; i < groups.count() && !rFlag; i++) {
        if (nName == groups.at(i)->getName()) {
            rFlag = true;
        }
    }

    return rFlag;
}

Clip::Clip(logger::Logger *nLog, QObject *parent) : QObject(parent),
    log(nLog)
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

ShowList::ShowList(logger::Logger *nLog, QObject *parent) : QObject(parent),
    log(nLog)
{

}

ClipList::ClipList(logger::Logger *nLog, QObject *parent) : QObject(parent),
    log(nLog)
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

ClipDatabase::ClipDatabase(logger::Logger *nLog, QObject *parent) : QObject(parent),
    log(nLog),
    main_list(NULL),
    existingShows(),
    used_clips(),
    sub_lists(),
    tagManager(NULL)
{
    tagManager = new TagManager(this);
}

bool ClipDatabase::init(QString config_filename) {
    bool initSuccess_flag = true;

    if (log != NULL) {

    }
    else {
        qDebug () << "ERROR - ClipDatabase.init :: Logger not valid.";
        initSuccess_flag = false;
    }

    return initSuccess_flag;
}

bool ClipDatabase::loadShowList(QString showList_filename) {
    bool importSuccess_flag = false;


    return importSuccess_flag;
}

bool ClipDatabase::loadTagList(QString tagList_filename) {
    bool importSuccess_flag = true;

    if (tagManager != NULL) {
        QFile tagFile(tagList_filename);
        if (tagFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            log->info(QString("Opened %1 for tag import.").arg(tagList_filename));

            QTextStream tStream(&tagFile);

            while(!tStream.atEnd()) {
                QString line = tStream.readLine();

                if (!line.isEmpty() && !line.startsWith('#')) {
                    tagManager->readTagLine(line);
                }
            }

        }
        else {
            log->warn(QString("Unable to open file \"%1\" for tag import.").arg(tagList_filename));
        }
    }
    else{
        log->err(QString("ClipDatabase.loadTagList: TagManager is NULL"));
        importSuccess_flag = false;
    }


    return importSuccess_flag;
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

#include "clipdatabase.h"
#include "logger.h"

#include <QDebug>
#include <QString>
#include <QTextStream>

#include <QFile>
#include <QDir>

TagGroup::TagGroup(logger::Logger *nLog, QObject *parent) : QObject(parent),
log(nLog)
{

}

void TagGroup::setName(QString nName) {
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

bool TagGroup::addTags(QStringList nTags) {
    bool addSuccess_flag = true;

    groupTags.append(nTags);
    groupTags.removeDuplicates();

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
        QString nName = "";
        QString nTags = "";
        QStringList tagList;

        if (split.at(0).startsWith("name=")) {
            nName = split.at(0).right(split.at(0).length() - 5);
        }

        if (split.at(1).startsWith("tags=")) {
            nTags = split.at(1).right(split.at(1).length() - 5);
            tagList = nTags.split("|");
        }

        if (!nTags.isEmpty() && !nName.isEmpty()) {
            TagGroup *nGroup = new TagGroup(log, this);
            nGroup->setName(nName);
            nGroup->addTags(tagList);
            groups.append(nGroup);
            log->info(QString("Created new TagGroup %1. Added %2 tags.").arg(nGroup->getName()).arg(nGroup->getTags().count()));
        }
    }
    else {
        log->warn(QString("Invalid tag line: \"%1\"").arg(line));
        rFlag = false;
    }

    return rFlag;
}

bool TagManager::addTag(QString tag, QString groupName) {
    if (!groupName.isEmpty()) {
        groupName = "General";
    }

    TagGroup *nGroup = getGroup(groupName);
    return nGroup->addTag(tag);
}

TagGroup* TagManager::addGroup(QString nGroupName) {
    TagGroup *rGroup = NULL;
    if (!containsGroup(nGroupName)) {
        TagGroup *nGroup = new TagGroup(log, this);
        nGroup->setName(nGroupName);
        groups.append(nGroup);
        rGroup = nGroup;
    }

    return rGroup;
}

TagGroup* TagManager::getGroup(QString groupName) {
    TagGroup *rGroup = NULL;
    bool rFlag = false;

    for (int i = 0; i < groups.count() && !rFlag; i++) {
        if (groupName == groups.at(i)->getName()) {
            rGroup = groups.at(i);
            rFlag = true;
        }
    }

    if (rGroup == NULL) {
        rGroup = addGroup(groupName);
    }

    return rGroup;
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
    log(nLog),
    showName()
{

}

QString ShowList::getName() {
    return showName;
}

ClipList::ClipList(logger::Logger *nLog, QObject *parent) : QObject(parent),
    log(nLog)
{

}

bool ClipList::addClip(Clip* /*nClip*/) {
    bool addSuccess_flag = true;


    return addSuccess_flag;
}

QString ClipList::getName() {
    return listName;
}

void ClipList::setName(QString nName) {
    listName = nName;
}

ShowList* ClipList::getShowList(QString show_name) {
    ShowList *rShow = NULL;
    bool rFlag = false;

    for (int i = 0; i < shows.count() && !rFlag; i++) {
        ShowList *cShow = shows.at(i);

        if (cShow->getName() == show_name) {
            rFlag = true;
            rShow = cShow;
        }
    }

    return rShow;
}

ClipDatabase::ClipDatabase(logger::Logger *nLog, QObject *parent) : QObject(parent),
    log(nLog),
    main_list(NULL),
    existingShows(),
    used_clips(),
    sub_lists(),
    tagManager(NULL),
    clips_filename(),
    tags_filename(),
    shows_filename()
{
    tagManager = new TagManager(nLog, this);
    tags_filename = "activeTagList.txt";
    shows_filename = "activeShowList.txt";
    clips_filename = "activeClipDB.txt";
}

bool ClipDatabase::init(QString config_filename) {
    bool initSuccess_flag = true;

    if (log != NULL) {

        if (readConfig(config_filename)) {
            log->info("ClipDatabase.init: Read config file.");
        }
        else {
            log->err("ClipDatabase.init: Failed to read config file");
            initSuccess_flag = false;
        }

        if (loadTagList(tags_filename)) {
            log->info(QString("ClipDatabase.init: Loaded Tag file \"%1\"").arg(tags_filename));
        }
        else {
            log->warn(QString("ClipDatabase.init: Failed to load Tag File \"%1\".").arg(tags_filename));
        }

        if (loadShowList(shows_filename)) {
            log->info(QString("Clipdatabase.init: Loaded Show File \"%1\"").arg(shows_filename));
        }
        else {
            log->warn(QString("ClipDatabase.init: Failed to load Show File \"%1\".").arg(shows_filename));
        }
    }
    else {
        qDebug () << "ERROR - ClipDatabase.init :: Logger not valid.";
        initSuccess_flag = false;
    }

    return initSuccess_flag;
}

bool ClipDatabase::readConfig(QString config_filename) {
    bool readSuccess_flag = true;

    QFile dbConfig(config_filename);
    if (dbConfig.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream tStream(&dbConfig);

        while(!tStream.atEnd()) {
            QString line = tStream.readLine();

            if (!line.isEmpty() && !line.startsWith('#')) {
                QStringList lineSplit = line.split(QRegExp("\\s+"));

                if (lineSplit.count() >= 2) {
                    QString id = lineSplit.at(0).trimmed();
                    QString input = lineSplit.at(1).trimmed();

                    if (id == "clips_filename") {
                        clips_filename = input;
                    }
                    else if(id == "tags_filename") {
                        tags_filename = input;
                    }
                    else if (id == "shows_filename") {
                        shows_filename = input;
                    }

                }
            }
        }

    }
    else {
        log->err(QString("Clipdatabase.init: Failed to open config file \"%1\".").arg(config_filename));
        readSuccess_flag = false;
    }

    return readSuccess_flag;

}

void ClipDatabase::selfTest() {
    // Add new Tag - no group

    // Add new Tag - 1 group

    // Add new Tag - multiple groups

    // Add new Clip - no lists

    // Add new Clip - multiple lists

    // Add new show
}

void ClipDatabase::save() {

    saveClips();
    saveShows();
    saveTags();

    writeBackup();
}

void ClipDatabase::saveClips() {
    log->info(QString("Saving ClipDatabase to file %1.").arg(clips_filename));
    QFile clipFile(clips_filename);
    if (clipFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&clipFile);

        out << "#ClipList | " << QDateTime::currentDateTime().toString("dd MMM YYYY mm:ss") << endl;
        clipFile.close();
    }
}

void ClipDatabase::saveShows() {
    log->info(QString("Saving ShowList to file %1.").arg(shows_filename));
    QFile showFile(shows_filename);
    if (showFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&showFile);

        out << "#ShowList | " << QDateTime::currentDateTime().toString("dd MMM YYYY mm:ss") << endl;
        for (int i = 0; i < existingShows.count(); i++) {
            out << existingShows.at(i) << endl;
        }
        showFile.close();
    }
}

void ClipDatabase::saveTags() {
    log->info(QString("Saving TagList to file %1.").arg(tags_filename));
    QFile tagsFile(tags_filename);
    if (tagsFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&tagsFile);

        out << "#TagList | " << QDateTime::currentDateTime().toString("dd MMM YYYY mm:ss") << endl << endl;

        for (int i = 0; i < tagManager->groups.count(); i++) {
            TagGroup* cGroup = tagManager->groups.at(i);
            out << "name=" <<cGroup->getName() << ":tags=";
            QStringList tags = cGroup->getTags();
            out << tags.at(0);
            for (int j = 1; j < tags.count(); j++) {
                out <<"|" << tags.at(j);
            }
            out << endl;

        }

        tagsFile.close();
    }
}

void ClipDatabase::writeBackup() {
    QDir cDir;
    QString tBackup = QString("/backup");
    QString nBackup = QString("/backup_%1").arg(QDateTime::currentDateTime().toString("ddMMyy_mmss"));
    cDir.setPath(QDir::currentPath() + tBackup);

    if (!cDir.exists()) {
        if (!cDir.mkdir(".")) {
            log->err(QString("Unable to create backup folder \"%1\"").arg(tBackup));
        }
    }

    cDir.setPath(QDir::currentPath() + tBackup + nBackup);
    if (!cDir.mkdir(".")) {
        log->err(QString("Unable to create backup folder \"%1\"").arg(nBackup));
    }

    QFile clipFile(clips_filename);
    if (clipFile.exists()) {
        QString bFile = QString(QDir::currentPath() + tBackup + nBackup + "/" + clips_filename);
        log->info(QString("Backup %1").arg(bFile));
        if (!clipFile.copy(bFile)) {
            log->err(QString("Unable to backup ClipDB %1").arg(bFile));
        }
    }
    else {
        log->err(QString("Could not find file \"%1\" for backup.").arg(clips_filename));
    }

    QFile tagsFile(tags_filename);
    if (tagsFile.exists()) {
        QString bFile = QString(QDir::currentPath() + tBackup + nBackup + "/" + tags_filename);
        if (!tagsFile.copy(bFile)) {
            log->err(QString("Unable to backup TagList %1").arg(bFile));
        }
    }
    else {
        log->err(QString("Could not find file \"%1\" for backup.").arg(tags_filename));
    }

    QFile showsFile(shows_filename);
    if (showsFile.exists()) {
        QString bFile =QString(QDir::currentPath() + tBackup + nBackup + "/" + shows_filename);
        if (!showsFile.copy(bFile)) {
            log->err(QString("Unable to backup ShowList %1").arg(bFile));
        }
    }
    else {
        log->err(QString("Could not find file \"%1\" for backup.").arg(shows_filename));
    }

}

bool ClipDatabase::loadClips(QString clipList_filename) {
    bool importSuccess_flag = true;

    if (!clipList_filename.isEmpty()) {
        QFile clipsFile(clipList_filename);
        if (clipsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream nStream(&clipsFile);

            while(!nStream.atEnd()) {
                QString line = tStream.readLine();
            }
        }
    }
    else {
        log->warn(QString("ClipDatabase.loadClips: Filename is empty"));
    }

    return importSuccess_flag;
}

bool ClipDatabase::loadShowList(QString showList_filename) {
    bool importSuccess_flag = false;

    if (showList_filename.endsWith(".xml")) {
        log->info(QString("Attempting to load shows from MAL xml file %1.").arg(showList_filename));
        int startCount = existingShows.count();

        QFile nFile(showList_filename);
        if (nFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            importSuccess_flag = true;
            QTextStream nStream(&nFile);

            while (!nStream.atEnd()) {

                QString line = nStream.readLine();
                if (!line.isEmpty() && line.contains(QString("<series_title>"))) {
                    int startBound = line.indexOf("<![CDATA[");
                    int boundLength = 9;
                    int endBound = line.indexOf("]]></series_title");

                    QString title = line.mid(startBound + boundLength, endBound - (startBound + boundLength));
                    existingShows.append(title);
                }
            }
        }

        existingShows.removeDuplicates();
        int diff = existingShows.count() - startCount;
        log->info(QString("Added %1 new shows.").arg(diff));
    }
    else if (showList_filename.endsWith(".txt")) {
        log->info(QString("Attempting to load shows from txt file %1").arg(showList_filename));
        int startCount = existingShows.count();

        QFile showFile(showList_filename);
        if (showFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            importSuccess_flag = true;

            QTextStream tStream(&showFile);

            while(!tStream.atEnd()) {
                QString line = tStream.readLine();

                if (!line.isEmpty() && !line.startsWith('#')) {
                    existingShows.append(line.trimmed());
                }
            }
        }

        existingShows.removeDuplicates();
        int diff = existingShows.count() - startCount;
        log->info(QString("Added %1 new shows.").arg(diff));
    }
    else {
        log->warn(QString("Unrecognized Show file type in file %1").arg(showList_filename));
    }


    return importSuccess_flag;
}

bool ClipDatabase::loadTagList(QString tagList_filename) {
    bool importSuccess_flag = true;

    if (tagManager != NULL) {
        if (!tagList_filename.isEmpty()) {
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
                log->warn(QString("ClipDatabase.loadTagList: Unable to open file \"%1\" for tag import.").arg(tagList_filename));
                importSuccess_flag = false;
            }
        }
        else {
            log->warn(QString("ClipDatabase.loadTagList: No TagList in config file"));
            importSuccess_flag = false;
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
    Clip* rClip = new Clip(log, this);

    rClip->setShowName(showName);
    rClip->setEpNum(epNum);
    rClip->setTimeBound(time);

    if (!existingShows.contains(showName)) {
        existingShows.append(showName);
    }

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
                ClipList* nList = new ClipList(log, this);
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

void  ClipDatabase::addExistingClip(Clip* /*nClip*/, QVector<ClipList*> /*nLists*/) {

}

Clip* ClipDatabase::clipExists(Clip *test_clip) {

}

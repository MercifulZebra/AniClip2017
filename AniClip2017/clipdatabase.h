#ifndef CLIPDATABASE_H
#define CLIPDATABASE_H

#include <QObject>
#include <QVector>
#include <QTime>
#include <QStringList>

namespace logger {
    class Logger;
}

struct TimeBound {
    QTime startTime;
    QTime endTime;
};

class TagGroup : public QObject
{
    Q_OBJECT
public:
    explicit TagGroup(logger::Logger *nLog, QObject *parent = 0);

    void setName(QString nName);

    bool addTag(QString nTag);
    bool addTags(QStringList nTags);
    bool removeTag(QString nTag);

    QStringList getTags();
    QString getName();

    bool addGroup(TagGroup oGroup);


private:
    logger::Logger *log;

    QString     groupName;
    QStringList groupTags;

signals:

public slots:

};

class TagManager : public QObject
{
    Q_OBJECT
public:
    explicit TagManager(logger::Logger *nLog, QObject *parent = 0);

    bool readTagLine(QString line);
    bool addTag(QString tag, QString groupName = "");
    TagGroup* addGroup(QString nGroupName);
    TagGroup* getGroup(QString groupName);

    QVector<TagGroup*> groups;

private:
    logger::Logger *log;

    bool containsGroup(QString nName);


signals:

public slots:

};

class Clip : public QObject
{
    Q_OBJECT
public:
    explicit Clip(logger::Logger *nLog, QObject *parent = 0);

    void setShowName(QString nShowName);
    void setEpNum(int nEpNum);
    void setTimeBound(TimeBound nTimeBound);

private:
    logger::Logger *log;

    QString     showName;
    int         epNum;
    TimeBound   bounds;
signals:

public slots:
};


class ShowList : public QObject
{
    Q_OBJECT
public:
    explicit ShowList(logger::Logger *nLog, QObject *parent = 0);

    QString getName();

private:
    logger::Logger *log;

    QString showName;
    QVector<Clip*> clips;
signals:

public slots:
};

class ClipList : public QObject
{
    Q_OBJECT
public:
    explicit ClipList(logger::Logger *nLog, QObject *parent = 0);

    bool addClip(Clip* nClip);

    //Get Functions
    QString getName();
    void setName(QString nName);

    ShowList* getShowList(QString show_name);

private:
    logger::Logger *log;

    QString listName;
    QVector<ShowList*> shows;

signals:

public slots:
};

class ClipDatabase : public QObject
{
    Q_OBJECT
public:
    explicit ClipDatabase(logger::Logger *nLog, QObject *parent = 0);

    bool init(QString config_filename);
    bool readConfig(QString config_filename);
    void selfTest();

    void save();
    void saveClips();
    void saveShows();
    void saveTags();
    void writeBackup();

    bool loadClips(QString clipList_filename);
    bool loadShowList(QString showList_filename);
    bool loadTagList(QString tagList_filename);

    Clip* addNewClip(QString showName, int epNum, TimeBound time, QVector<QString> nLists);
    void  addExistingClip(Clip* nClip, QVector<ClipList*> nLists);

private:
    Clip* clipExists(Clip* test_clip);

    logger::Logger *log;

    ClipList* main_list;
    QStringList existingShows;

    QVector<Clip*> used_clips;
    QVector<ClipList*> sub_lists;

    TagManager *tagManager;

    QString clips_filename;
    QString tags_filename;
    QString shows_filename;

signals:

public slots:
};

#endif // CLIPDATABASE_H

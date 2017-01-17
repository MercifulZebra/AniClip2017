#ifndef CLIPDATABASE_H
#define CLIPDATABASE_H

#include <QObject>
#include <QVector>
#include <QTime>

namespace logger {
    class Logger;
}

struct TimeBound {
    QTime startTime;
    QTime endTime;
};

class Clip : public QObject
{
    Q_OBJECT
public:
    explicit Clip(QObject *parent = 0);

    void setShowName(QString nShowName);
    void setEpNum(int nEpNum);
    void setTimeBound(TimeBound nTimeBound);

private:
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
    explicit ShowList(QObject *parent = 0);

private:
    QString showName;
signals:

public slots:
};

class ClipList : public QObject
{
    Q_OBJECT
public:
    explicit ClipList(QObject *parent = 0);

    bool addClip(Clip* nClip);

    //Get Functions
    QString getName();
    void setName(QString nName);

private:
    QString listName;

signals:

public slots:
};

class ClipDatabase : public QObject
{
    Q_OBJECT
public:
    explicit ClipDatabase(QObject *parent = 0, logger::Logger *nLog = 0);

    bool init();

    Clip* addNewClip(QString showName, int epNum, TimeBound time, QVector<QString> nLists);
    void  addExistingClip(Clip* nClip, QVector<ClipList*> nLists);

private:

    logger::Logger *log;

    ClipList* main_list;

    QVector<Clip*> used_clips;
    QVector<ClipList*> sub_lists;

signals:

public slots:
};

#endif // CLIPDATABASE_H

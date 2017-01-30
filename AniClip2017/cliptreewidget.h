#ifndef CLIPTREEWIDGET_H
#define CLIPTREEWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QTime>

class ClipDatabase;
class Clip;

namespace logger {
class Logger;
}

class ClipTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ClipTreeWidget(QWidget *parent = 0);

    void setClipDatabase(ClipDatabase *db);
    void setLogger(logger::Logger *nLog);

    void clearSearchParams();
    bool clipIsValid(Clip* nClip);

    void updateTreeItem(QTreeWidgetItem* nItem, Clip* nClip);

    void setShowKey(QString nShow);
    void setEpStartRange(int nStart);
    void setEpEndRange(int nEnd);

    void setSeason(int nSeason);
    void setYearKey(int nYear);

    void setStartTime(QString nStart);
    void setEndtime(QString nEnd);

    void setLengthLowBound(int nLow);
    void setLengthHighBound(int nHigh);

    void setNoteKey(QString nKey);

    void addKeyTag(QString nTag);
    void setKeyTags(QStringList nTags);

    void addSubTag(QString nTag);
    void setSubTags(QStringList nTags);

private:
    ClipDatabase *clipDB;
    logger::Logger *log;

    QString showKey;
    int epStartRange;
    int epEndRange;

    int seasonKey;
    int yearKey;

    QTime sStartTime;
    QTime sEndtime;

    int lengthLowBound;
    int lengthHighBound;

    QString noteKey;

    QStringList keyTags;
    QStringList subTags;
signals:

public slots:
    void updateClips(const QString &searchString);
};

#endif // CLIPTREEWIDGET_H

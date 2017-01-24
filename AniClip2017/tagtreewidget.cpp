#include "tagtreewidget.h"

#include <QTreeWidgetItem>

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
    {
        int rootCount = 10;
        int itemCount = 10;
        for (int i = 0; i < rootCount; i++)
        {
            QTreeWidgetItem *nItem = new QTreeWidgetItem(this);
            nItem->setText(0, "Parent");
            nItem->setText(1, QString("%1").arg(i));
            nItem->setText(2, "_");
            nItem->setText(3, "!!");

            for(int j =0; j < itemCount; i++) {
                QTreeWidgetItem *nChild = new QTreeWidgetItem();
                nChild->setText(0, "Child");
                nChild->setText(1, QString("%1_%2").arg(i).arg(j));
                nChild->setText(2, "--");
                nChild->setText(3, "X");
                nItem->addChild(nChild);
            }

        }
    }
}

void TagTreeWidget::testClear() {
    for (int i = 0; i < topLevelItemCount(); i++) {
        QTreeWidgetItem* topLvl = takeTopLevelItem(0);
        delete topLvl;
    }
}

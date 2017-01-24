#include "rotatedbutton.h"
#include <QPainter>
#include <QDebug>
RotatedButton::RotatedButton(QWidget *parent) : QPushButton(parent)
{

}

void RotatedButton::paintEvent(QPaintEvent *event) {

    QPushButton::paintEvent(event);
    QPainter painter;
    painter.begin(this);
    painter.rotate(90);
    QRect tRect = this->rect();
    tRect.setTop(-1 * this->rect().width());
    tRect.setLeft(10);
    tRect.setWidth(this->rect().height());
    tRect.setHeight(this->rect().width());
    painter.drawText(tRect, Qt::AlignVCenter, "Test");
    painter.setBrush(Qt::green);
    qDebug () << tRect;
    //painter.drawRect(tRect);
    painter.end();

}

void RotatedButton::setRotatedText(QString nText) {
    rText = nText;
}

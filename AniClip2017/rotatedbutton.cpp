#include "rotatedbutton.h"
#include <QPainter>
#include <QDebug>
RotatedButton::RotatedButton(QWidget *parent) : QPushButton(parent),
    rText(),
    rotation_deg(90)
{
    rText = "RotatedText";
}

void RotatedButton::paintEvent(QPaintEvent *event) {

    QPushButton::paintEvent(event);
    QPainter painter;
    painter.begin(this);
    painter.save();
    if (rotation_deg < 0) {
        painter.translate(this->width(), this->height());
    }
    painter.rotate(rotation_deg);
    QRect tRect = this->rect();
    tRect.setTop(-1 * this->rect().width());
    tRect.setLeft(10);
    tRect.setWidth(this->rect().height());
    tRect.setHeight(this->rect().width());
    painter.drawText(tRect, Qt::AlignVCenter, rText);
    painter.setBrush(Qt::green);
    //qDebug () << tRect;
    //painter.drawRect(tRect);
    painter.restore();
    painter.end();

}

void RotatedButton::setRotatedText(QString nText) {
    rText = nText;
}

void RotatedButton::setRotatedDeg(int nRot) {
    rotation_deg = nRot;
}

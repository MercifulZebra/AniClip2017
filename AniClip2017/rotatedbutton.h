#ifndef ROTATEDBUTTON_H
#define ROTATEDBUTTON_H

#include <QWidget>
#include <QPushButton>

class RotatedButton : public QPushButton
{
    Q_OBJECT
public:
    explicit RotatedButton(QWidget *parent = 0);

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void setRotatedText(QString nText);

private:
    QString rText;

signals:

public slots:
};

#endif // ROTATEDBUTTON_H

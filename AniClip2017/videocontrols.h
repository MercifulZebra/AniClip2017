#ifndef VIDEOCONTROLS_H
#define VIDEOCONTROLS_H

#include <QWidget>

namespace Ui {
class VideoControls;
}

class VideoControls : public QWidget
{
    Q_OBJECT

public:
    explicit VideoControls(QWidget *parent = 0);
    ~VideoControls();

private:
    Ui::VideoControls *ui;
};

#endif // VIDEOCONTROLS_H

#ifndef VOLUMEBUTTON_H
#define VOLUMEBUTTON_H

#include <QToolButton>

//Forward Declarations
QT_FORWARD_DECLARE_CLASS(QSlider)
QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QLabel)

class VolumeButton : public QToolButton
{
    Q_OBJECT
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)

public:
    //getter of volume
    int volume() const;

public:
    explicit VolumeButton(QWidget *parent = nullptr);
    QMenu *menu;
    QLabel *num;
    QSlider *volumeSlider;
    QWidget *popup;

public slots:
    void increaseVolume();
    void decreaseVolume();
    //setter of volume
    void setVolume(int volume);

signals:
    //send signals on occasion when volumeSlider's value changes
    void volumeChanged(int volume);
};

#endif // VOLUMEBUTTON_H

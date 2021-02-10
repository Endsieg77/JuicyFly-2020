#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>

QT_FORWARD_DECLARE_CLASS(TitleBar)
QT_FORWARD_DECLARE_CLASS(PlayMode)
QT_FORWARD_DECLARE_CLASS(ListButton)
QT_FORWARD_DECLARE_CLASS(VolumeButton)
QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QSlider)
QT_FORWARD_DECLARE_CLASS(QAbstractButton)
QT_FORWARD_DECLARE_CLASS(QBoxLayout)
QT_FORWARD_DECLARE_CLASS(QTableWidget)
QT_FORWARD_DECLARE_CLASS(QTableWidgetItem)
QT_FORWARD_DECLARE_CLASS(QMediaPlayer)
QT_FORWARD_DECLARE_CLASS(QMediaPlaylist)

using QTWI = QTableWidgetItem;

QT_BEGIN_NAMESPACE
namespace Ui { class MusicPlayer; }
namespace Utils { class dataPackage; }
QT_END_NAMESPACE

class MusicPlayer : public QWidget
{
    Q_OBJECT

//Member functions
public:
    explicit MusicPlayer(QWidget *parent = nullptr);
    ~MusicPlayer() override;
    bool eventFilter(QObject *wathced, QEvent *event) override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void init();
    void buildConnections();
    void buildHoverEffects(QAbstractButton *btn);
    void playMusic();

//Attributions

private:
    Ui::MusicPlayer *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QAbstractButton *openButton;
    QAbstractButton *playButton;
    QAbstractButton *prev;
    QAbstractButton *next;
    PlayMode *playMode;
    ListButton *listButton;
    VolumeButton *volumeButton;
    QSlider *sliderBar;
    QLabel *coverImage;
    QLabel *position;
    QLabel *duration;
    QLabel *title;
    QLabel *artist;
    QWidget *info;
    QWidget *mainWidget;
    TitleBar *titleBar;

public slots:
    void openFile();
    void seekForward();
    void seekBackward();
    void togglePlayState();
    void togglePlayMode();
    void setPosition(int pos);
    void updatePosition(qint64 pos);
    void updateDuration(qint64 dur);
    void updateInfo();
    void toNext();
    void toPrev();
    void itemDoubleClicked(QTWI *item);
};

#endif // MUSICPLAYER_H

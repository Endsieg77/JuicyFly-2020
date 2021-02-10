#include "musicplayer.h"
#include "titlebar.h"
#include "playmode.h"
#include "volumebutton.h"
#include "listbutton.h"
#include "ui_musicplayer.h"
#include "Utils.h"
#include <QtWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>

MusicPlayer::MusicPlayer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MusicPlayer)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setObjectName("MusicPlayer");
    setFixedSize(QSize(1000, 355));
    init();
    buildConnections();
}

MusicPlayer::~MusicPlayer()
{
    delete ui;
}

void MusicPlayer::init()
{
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    player->setPlaylist(playlist);
    playlist->setPlaybackMode(QMediaPlaylist::Sequential);

    titleBar = new TitleBar("JuicyFly 2021", this);

    coverImage = new QLabel(this);
    coverImage->setObjectName("Cover");
    coverImage->setPixmap(QPixmap(":/images/default.png"));
    coverImage->setFixedSize(QSize(260, 260));
    coverImage->setScaledContents(true);

    info = new QWidget(this);
    info->setObjectName("Info");

    srand(time(NULL));
    title = new QLabel(Utils::welcome[rand() % MAX_SIZE], info);
    title->setObjectName("title");
    title->setAlignment(Qt::AlignCenter);

    artist = new QLabel("\\(O^3^O)/", info);
    artist->setObjectName("artist");
    artist->setAlignment(Qt::AlignCenter);

    mainWidget = new QWidget(this);
    mainWidget->setObjectName("mainWidget");
    mainWidget->setFixedHeight(260);

    openButton = new QToolButton(mainWidget);
    openButton->setObjectName("open");
    openButton->setIcon(QPixmap(":/images/open.png"));
    openButton->setToolTip("Open files...");
    openButton->setIconSize(QSize(25, 25));
    openButton->installEventFilter(this);
    openButton->setShortcut(QKeySequence(QLatin1String("Ctrl+O")));

    playMode = new PlayMode(mainWidget);
    playMode->setIconSize(QSize(25, 25));
    playMode->installEventFilter(this);
    playMode->setShortcut(QKeySequence(QLatin1String("Ctrl+M")));
    connect(playMode, &QToolButton::clicked, this, &MusicPlayer::togglePlayMode);

    //刚开始未导入任何文件, 故无法直接播放
    playButton = new QToolButton(mainWidget);
    playButton->setObjectName("pause");
    playButton->setEnabled(false);
    playButton->setIcon(QPixmap(":/images/pause.png"));
    playButton->setToolTip("Pause");
    playButton->setIconSize(QSize(47, 47));
    playButton->installEventFilter(this);
    playButton->setShortcut(QKeySequence(QLatin1String("Space")));
    connect(playButton, &QToolButton::clicked, this, &MusicPlayer::togglePlayState);

    next = new QToolButton(mainWidget);
    next->setObjectName("next");
    next->setEnabled(false);
    next->setIcon(QPixmap(":/images/next.png"));
    next->setToolTip("Next Song");
    next->setIconSize(QSize(35, 35));
    next->installEventFilter(this);
    next->setShortcut(QKeySequence(QLatin1String("Ctrl+Right")));
    connect(next, &QToolButton::clicked, this, &MusicPlayer::toNext);

    prev = new QToolButton(mainWidget);
    prev->setObjectName("prev");
    prev->setEnabled(false);
    prev->setIcon(QPixmap(":/images/prev.png"));
    prev->setToolTip("Previous Song");
    prev->setIconSize(QSize(35, 35));
    prev->installEventFilter(this);
    prev->setShortcut(QKeySequence(QLatin1String("Ctrl+Left")));
    connect(prev, &QToolButton::clicked, this, &MusicPlayer::toPrev);

    sliderBar = new QSlider(Qt::Horizontal, mainWidget);
    sliderBar->setObjectName("sliderBar");
    sliderBar->setEnabled(false);
    sliderBar->setToolTip("Seek...");
    sliderBar->setMinimumSize(sliderBar->sizeHint());
    sliderBar->setMinimumHeight(sliderBar->sizeHint().height());
    /** 这里的valueChanged为什么不直接和player的setPosition connect呢? 是个好问题:
     *  因为这样会造成卡顿.
     *  只要sliderBar的值改变都会触发player的setPosition
     *  但我们需要的是什么呢? 是手动调整sliderBar时才触发这一事件.
     *  故MusicPlayer::setPosition中设置了if条件, 就是为了避免这一错误.
     */
    connect(sliderBar, &QSlider::valueChanged, this, &MusicPlayer::setPosition);

    position = new QLabel("--:-- /", mainWidget);
    position->setObjectName("position");
    position->setMinimumWidth(position->sizeHint().width());

    duration = new QLabel("--:--", mainWidget);
    duration->setObjectName("duration");
    duration->setMinimumWidth(duration->sizeHint().width());

    volumeButton = new VolumeButton(mainWidget);
    volumeButton->setToolTip("Adjust Volume");
    volumeButton->setVolume(player->volume());
    volumeButton->setEnabled(false);
    volumeButton->setIconSize(QSize(32, 32));
    //volumeButton发出volumeChanged信号, 给player的setVolume接收
    connect(volumeButton, &VolumeButton::volumeChanged, player, &QMediaPlayer::setVolume);

    listButton = new ListButton(mainWidget);
    listButton->setObjectName("list");
    listButton->setToolTip("List");
    listButton->setIconSize(QSize(25, 25));
    listButton->installEventFilter(this);
    listButton->setShortcut(QKeySequence(QLatin1String("Ctrl+L")));
    connect(listButton->list, &QTableWidget::itemDoubleClicked, this, &MusicPlayer::itemDoubleClicked);

    QBoxLayout *infoLayout = new QVBoxLayout(info);
    infoLayout->addWidget(title);
    infoLayout->addWidget(artist);

    QBoxLayout *playBarLayout = new QHBoxLayout;
    playBarLayout->addWidget(prev);
    playBarLayout->addWidget(playButton);
    playBarLayout->addWidget(next);

    QBoxLayout *toolBarLayout = new QHBoxLayout;
    toolBarLayout->addWidget(openButton);
    toolBarLayout->addWidget(playMode);
    toolBarLayout->addWidget(sliderBar);
    toolBarLayout->addWidget(position);
    toolBarLayout->addWidget(duration);
    toolBarLayout->addWidget(volumeButton);
    toolBarLayout->addWidget(listButton);

    QBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->addWidget(info);
    mainLayout->addLayout(playBarLayout);
    mainLayout->addLayout(toolBarLayout);

    QBoxLayout *decorationLayout = new QHBoxLayout;
    decorationLayout->setMargin(3);
    decorationLayout->addWidget(coverImage);
    decorationLayout->addWidget(mainWidget);
    decorationLayout->setAlignment(Qt::AlignBottom);

    QBoxLayout *GUI = new QVBoxLayout(this);
    GUI->addLayout(titleBar->titleBarLayout);
    GUI->addLayout(decorationLayout);
}

void MusicPlayer::buildConnections()
{
    connect(openButton, &QToolButton::clicked, this, &MusicPlayer::openFile);
    //player中播放的进度改变时发出信号, 更新position标签
    connect(player, &QMediaPlayer::positionChanged, this, &MusicPlayer::updatePosition);
    //同理
    connect(player, &QMediaPlayer::durationChanged, this, &MusicPlayer::updateDuration);
    connect(player, &QMediaObject::metaDataAvailableChanged, this, &MusicPlayer::updateInfo);
}

void MusicPlayer::openFile()
{
    QString title = "Open File";

    //从系统默认的音乐目录读取, 若不存在则从$HOME返回的目录读取
    QString path = QStandardPaths::standardLocations(QStandardPaths::MusicLocation).value(0, QDir::homePath());

    QString filter = "音频文件(*.mp3 *.flac *.wav *.wma *.ffmeg);;mp3文件(*.mp3);;flac文件(*.flac);;ffmeg文件(*.ffmeg);;wav文件(*.wav);;wma文件(*.wma);;所有文件(*.*)";
    auto fileList = QFileDialog::getOpenFileNames(this, title, path, filter);
    auto listLen = fileList.count();

    playButton->setObjectName("pause");

    if(!listLen) return;

    for(auto i = 0; i < listLen; ++i)
    {
        playlist->addMedia(QUrl::fromLocalFile(fileList.at(i)));
        listButton->addItem(fileList.at(i));
    }
    playMusic();
}

void MusicPlayer::playMusic()
{
    playButton->setEnabled(true);
    playButton->setIcon(QPixmap(":/images/pause.png"));
    sliderBar->setEnabled(true);
    prev->setEnabled(true);
    next->setEnabled(true);
    playMode->setEnabled(true);
    volumeButton->setEnabled(true);
    player->play();
}

void MusicPlayer::seekForward()
{
    sliderBar->triggerAction(QSlider::SliderPageStepAdd);
}

void MusicPlayer::seekBackward()
{
    sliderBar->triggerAction(QSlider::SliderPageStepSub);
}


void MusicPlayer::setPosition(int pos)
{
    if(qAbs(player->position() - pos) > 99)
        player->setPosition(pos);
}

void MusicPlayer::updatePosition(qint64 pos)
{
    sliderBar->setValue(pos);
    position->setText(Utils::formatTime(pos) + " /");
}

void MusicPlayer::updateDuration(qint64 dur)
{
    sliderBar->setRange(0, dur);
    sliderBar->setEnabled(dur > 0);
    sliderBar->setPageStep(dur / 10);
    duration->setText(Utils::formatTime(dur));
    updateInfo();
}

void MusicPlayer::updateInfo()
{
    auto curr = playlist->currentIndex();
    listButton->list->selectRow(curr);
    title->setText(listButton->list->item(curr, 1)->text());
    artist->setText(listButton->list->item(curr, 2)->text());

    if(player->isMetaDataAvailable())
    {
        QPixmap pix;
        auto img = player->metaData("ThumbnailImage").value<QImage>();
        if(!img.isNull())
        {
            pix = QPixmap::fromImage(img);
            coverImage->setPixmap(pix);
        }
        else coverImage->setPixmap(QPixmap(":/images/default.png"));
    }
}

void MusicPlayer::togglePlayState()
{
    switch (player->state())
    {
    case QMediaPlayer::PlayingState:
        player->pause();
        playButton->setObjectName("resume");
        playButton->setToolTip("Play");
        break;
    case QMediaPlayer::PausedState:
        player->play();
        playButton->setObjectName("pause");
        playButton->setToolTip("Pause");
        break;
    }
    playButton->setIcon(QPixmap(":/images/"+ playButton->objectName() +".png"));
}

void MusicPlayer::togglePlayMode()
{
    switch(playlist->playbackMode())
    {
    case QMediaPlaylist::Sequential:
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        break;
    case QMediaPlaylist::Loop:
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        break;
    case QMediaPlaylist::CurrentItemInLoop:
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        break;
    default:
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    }
}

void MusicPlayer::toNext()
{
    auto temp = playlist->playbackMode();
    if(temp != QMediaPlaylist::Random)
    {
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        playlist->next();
        playlist->setPlaybackMode(temp);
    } else
    {
        auto currentIndex = playlist->currentIndex();
        auto getARoll = 0ull;
        do {
            getARoll = rand() % listButton->list->rowCount();
        } while (getARoll == currentIndex);
        playlist->setCurrentIndex(getARoll);
    }
}

void MusicPlayer::toPrev()
{
    auto temp = playlist->playbackMode();
    if(temp != QMediaPlaylist::Random)
    {
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        playlist->previous();
        playlist->setPlaybackMode(temp);
    } else
    {
        auto currentIndex = playlist->currentIndex();
        auto getARoll = 0ull;
        do {
            getARoll = rand() % listButton->list->rowCount();
        } while (getARoll == currentIndex);
        playlist->setCurrentIndex(getARoll);
    }
}

void MusicPlayer::itemDoubleClicked(QTWI *item)
{
    playlist->setCurrentIndex(item->row());
}

bool MusicPlayer::eventFilter(QObject *watched, QEvent *event)
{
    if(openButton   == watched ||
       prev         == watched ||
       next         == watched ||
       playMode     == watched ||
       listButton   == watched ||
       volumeButton == watched ||
       playButton   == watched)
    {
        auto thisBtn = static_cast<QToolButton *>(watched);
        if(QEvent::Enter == event->type())
        {
            thisBtn->setIcon(QPixmap(":/images/" + thisBtn->objectName() + "-hover.png"));
        } else if(QEvent::Leave == event->type())
        {
            thisBtn->setIcon(QPixmap(":/images/" + thisBtn->objectName() + ".png"));
        }
    }
    return 0;
}

void MusicPlayer::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event);

    QStyleOption opt;

    opt.init(this);

    QPainter p(this);

    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}

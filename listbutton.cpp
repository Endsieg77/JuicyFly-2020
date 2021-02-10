#include "listbutton.h"
#include "titlebar.h"
#include "Utils.h"
#include <QHeaderView>
#include <QTableWidget>
#include <QBoxLayout>
#include <QMediaPlayer>
#include <QMediaMetaData>

ListButton::ListButton(QWidget *parent)
    : QToolButton(parent)
{
    setIcon(QPixmap(":/images/list.png"));

    popup = new QWidget;
    popup->setWindowFlag(Qt::FramelessWindowHint);
    popup->setFixedSize(QSize(700, 800));
    popup->setContentsMargins(5, 15, 5, 15);
    popup->setObjectName("ListPopup");
    popup->hide();

    title = new TitleBar("Music Storage", popup);

    list = new QTableWidget(popup);
    list->setColumnCount(3);
    list->setColumnWidth(0, 120);
    list->setColumnWidth(1, 360);
    list->setColumnWidth(2, 178);
//    list->setColumnWidth(3, 115);
    list->setHorizontalHeaderLabels(QStringList() << "索引" << "乐曲名" << "作者");
    list->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignBottom);
    list->verticalHeader()->setHidden(true);
    list->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    //整行选中
    list->setSelectionBehavior(QTableWidget::SelectRows);
    //单个选中
    list->setSelectionMode(QTableWidget::SingleSelection);
    //不可修改
    list->setEditTriggers(QTableWidget::NoEditTriggers);
    //去除选中虚线框
    list->setFocusPolicy(Qt::NoFocus);
    //去除网格黑线
    list->setShowGrid(false);
    list->setFixedHeight(700);

    layout = new QVBoxLayout(popup);
    layout->addLayout(title->titleBarLayout);
    layout->addWidget(list);
    layout->setAlignment(Qt::AlignBottom | Qt::AlignCenter);

    connect(this, &QToolButton::clicked, this, &ListButton::listPopup);
}

void ListButton::addItem(const QString &url)
{
    //用哈希表去重
    if(!hasInMem[url])
    {
        auto info = Utils::getMetaInfoFromUrl(url);
        auto count = list->rowCount();
        list->insertRow(count);
        auto player = new QMediaPlayer(this);
        player->setMedia(QUrl(url));
        urls.push_back(url);
        player->play();
//        qDebug() << currTime;
        auto id       = new QTableWidgetItem(QString::number(count + 1));
        auto title    = new QTableWidgetItem(info.title);
        auto artist   = new QTableWidgetItem(info.artist);
//        auto duration = new QTableWidgetItem(Utils::formatTime(currTime));

        player->pause();
        list->setItem(count, 0, id);
        list->setItem(count, 1, title);
        list->setItem(count, 2, artist);
//        list->setItem(count, 3, duration);
//        qDebug() << list->rowCount();
        hasInMem[url] = 1;
    }
}

void ListButton::listPopup()
{
    if(popup->isHidden())
        popup->show();
    else popup->hide();
}

//void ListButton::getDuration(qint64 duration)
//{
////    qDebug() << player->duration();
//    currTime =  duration;
//}

#ifndef QLISTBUTTON_H
#define QLISTBUTTON_H

#include <QToolButton>

//QT_FORWARD_DECLARE_CLASS(QMediaPlayer)
QT_FORWARD_DECLARE_CLASS(QTableWidget)
QT_FORWARD_DECLARE_CLASS(TitleBar)
QT_FORWARD_DECLARE_CLASS(QBoxLayout)

class ListButton : public QToolButton
{
    Q_OBJECT
public:
    explicit ListButton(QWidget *parent = nullptr);
    void addItem(const QString &url);

public:
    QTableWidget *list;
//    QMediaPlayer *player;
    QWidget *popup;
    QHash<QString, bool> hasInMem;
    TitleBar *title;
    QVector<QString> urls;
    QBoxLayout *layout;

public slots:
    void listPopup();
//    void getDuration(qint64 duration);
};

#endif // QLISTMENU_H

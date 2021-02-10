#ifndef PLAYMODE_H
#define PLAYMODE_H

#include <QToolButton>

class PlayMode: public QToolButton
{
    Q_OBJECT

public:
    explicit PlayMode(QWidget *parent = nullptr);
    int playmode() const;

private:
    void setIconByIndex(int i);

public:
    enum
    {
        Sequential,
        Loop,
        CurrentItemInLoop,
        Random
    };

private:
    int mode;

public slots:
    void togglePlayMode();
};

#endif // PLAYMODE_H

#include "playmode.h"

PlayMode::PlayMode(QWidget *parent)
    : QToolButton(parent)
{
    setEnabled(false);
    mode = Sequential;
    setObjectName("modes/mode-0");
    setIconByIndex(mode);
    setToolTip("Loop");
    connect(this, &QToolButton::clicked, this, &PlayMode::togglePlayMode);
}

inline int PlayMode::playmode() const
{
    return mode;
}

void PlayMode::setIconByIndex(int i)
{
    setIcon(QPixmap(":/images/modes/mode-" + QString(i + '0') + ".png"));
}

void PlayMode::togglePlayMode()
{
    switch(playmode())
    {
    case Sequential:
        setObjectName("modes/mode-1");
        setToolTip("Single Circulation");
        ++mode;
        break;
    case Loop:
        setObjectName("modes/mode-2");
        setToolTip("Random");
        ++mode;
        break;
    case CurrentItemInLoop:
        setObjectName("modes/mode-3");
        setToolTip("Sequential");
        ++mode;
        break;
    default:
        setObjectName("modes/mode-0");
        setToolTip("Loop");
        mode = Sequential;
    }
    setIconByIndex(mode);
}

#include "musicplayer.h"
#include "titlebar.h"
#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QIcon>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/style.qss");
    qss.open(QFile::ReadOnly);
    if(qss.isOpen())
    {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
    MusicPlayer w;
    w.show();
    return a.exec();
}

#include "Utils.h"
#include <cwchar>
#include <QFile>
#include <QPixmap>

QString Utils::formatTime(qint64 time)
{
    qint64 seconds = time / 1000;
    const qint64 minutes = seconds / 60;
    seconds -= minutes * 60;
    //QT自带的格式化字符串方法:
    return QStringLiteral("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}

Utils::metaInfo Utils::getMetaInfoFromUrl(const QString &url)
{
    auto i = url.lastIndexOf(".") - url.lastIndexOf("/") - 1;
    return [&url](QStringList sList)->metaInfo
    {
        if(isValidString(url)) return { url, sList[0], sList[1] };
        else return { url, "Unknown Artist", sList[0] };
    } (url.split("/").last().mid(0, i).split(" - "));
}

bool Utils::isValidString(const QString &url)
{
    for(auto i: url)
        if(i == '-') return true;
    return false;
}

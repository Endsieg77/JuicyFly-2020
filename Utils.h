#ifndef UTILS_H
#define UTILS_H

#define MAX_SIZE 5

#include <QStringList>
#include <QImage>

namespace Utils
{
    enum PictureType
    {
        none,
        jpeg,
        png
    };
    static QString welcome[MAX_SIZE] =
    {
        "欢迎使用JuicyFly!",
        "开始你的音乐之旅吧~",
        "今天也是核平的一天",
        "生而为人, 我很抱歉",
        "有些人到了死才出生"
    };
    static QString helpDocument =
            "---------------- User's Manual -----------------\n"
            "\n"
            "您好! 欢迎使用Juicy2021! 本产品是一款轻量级的音乐播放\n"
            "器, 特色是Bug巨多, 布局巨丑. XDDD\n"
            "\n"
            "------------------------------------------------\n"
            "* 每次打开的欢迎语都是随机的噢"
            "\n"
            "* 快捷键:\n"
            "    打开文件: Ctrl + O\n"
            "    打开列表: Ctrl + L\n"
            "    切换模式: Ctrl + M\n"
            "    上一曲/下一曲: Ctrl + Left/Right\n"
            "    切换暂停/开始: Space\n"
            "\n"
            "* 注意:\n"
            "1. 由于QT底层实现的原因, 本产品需要依赖LAV_Filters来支\n"
            "持一部分格式的音乐(安装包位于本产品依赖文件同一目录下);\n"
            "\n"
            "2. 一次打开过多文件时会卡退, 可以分批次读取文件.\n"
            "\n"
            "* 关于专辑封面提取:\n"
            "\n"
            "由于技术力的原因, 目前只有在同时满足:\n"
            "1. 该文件是MP3 ID3V2编码;\n"
            "2. 存在APIC帧;\n"
            "3. APIC帧的大小在int的范围内(这锅是QT的, 我不背);\n"
            "\n"
            "的情况下, 能够提取专辑封面.\n"
            "\n"
            "我试了一下, 大部分都不行lmao, 见谅.\n"
            "------------------------------------------------\n"
            "上面的那句话已经是过去式了, 用了QT的官方接口, 完美解决\n"
            "hahahahahaha!"
            "\n"
            "                           Endsieg77 2021年2月8日";
    struct metaInfo;
    QString formatTime(qint64 time);
    bool isValidString(const QString &url);
    metaInfo getMetaInfoFromUrl(const QString &url);
}

struct Utils::metaInfo
{
    QString url;
    QString artist;
    QString title;
};

#endif // UTILS_H

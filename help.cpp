#include "help.h"
#include "titlebar_v2.h"
#include "Utils.h"
#include <QtWidgets>

Help::Help(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setFixedSize(QSize(600, 690));
    setContentsMargins(5, 8, 5, 12);

    titleBar = new TitleBar_v2("JuicyFly 2021 帮助文档", this);

    auto scrollArea = new QScrollArea(this);
    scrollArea->setFixedSize(QSize(550, 580));

    documents = new QLabel;
    scrollArea->setWidget(documents);
    documents->setObjectName("documents");
//    documents->setFixedSize(QSize(550, 690));
    documents->setContentsMargins(15, 5, 15, 5);
    documents->setText(Utils::helpDocument);
    documents->setFixedSize(documents->sizeHint());

    QBoxLayout *scrollAreaLayout = new QVBoxLayout(scrollArea);
    scrollAreaLayout->addWidget(documents);
    scrollAreaLayout->setAlignment(Qt::AlignTop);

    QBoxLayout *helpLayout = new QVBoxLayout(this);
    helpLayout->addLayout(titleBar->titleBarLayout);
    helpLayout->addWidget(scrollArea);
    helpLayout->setAlignment(Qt::AlignBottom);
}

void Help::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event);

    QStyleOption opt;

    opt.init(this);

    QPainter p(this);

    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}

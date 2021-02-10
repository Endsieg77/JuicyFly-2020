#include "titlebar_v2.h"
#include <QtWidgets>

TitleBar_v2::TitleBar_v2(const QString &title, QWidget *parent)
    : QWidget(parent)
{
    parent
        ? setFixedSize(QSize(parent->width(), 60))
        : setFixedSize(QSize(1000, 60));

    titleIcon = new QLabel(this);
    titleIcon->setObjectName("TitleIcon");
    titleIcon->setFixedSize(QSize(55, 55));
    titleIcon->setScaledContents(true);
    titleIcon->setPixmap(QPixmap(":/images/titlesbar/titleicon.png"));

    windowTitle = new QLabel(this);
    windowTitle->setObjectName("WindowTitle");
    windowTitle->setText(title);
    windowTitle->setAlignment(Qt::AlignCenter);

    close = new QToolButton(this);
    close->setObjectName("titlesbar/close");
    close->installEventFilter(this);
    close->setIcon(QPixmap(":/images/titlesbar/close.png"));
    close->setToolTip("Close");

    minimum = new QToolButton(this);
    minimum->setObjectName("titlesbar/minimum");
    minimum->installEventFilter(this);
    minimum->setIcon(QPixmap(":/images/titlesbar/minimum.png"));
    minimum->setToolTip("Minimum");

    titleBarLayout = new QHBoxLayout(this);
    titleBarLayout->setMargin(2);
    titleBarLayout->addWidget(titleIcon);
    titleBarLayout->addWidget(windowTitle);
    titleBarLayout->addWidget(minimum);
    titleBarLayout->addWidget(close);

    titleConnectionsBuilder(parent);
}

void TitleBar_v2::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        last_mouse_position_ = event->globalPos();
}

void TitleBar_v2::mouseMoveEvent(QMouseEvent *event)
{
    if (!event->buttons().testFlag(Qt::LeftButton))
        return;
    auto ptrParent = static_cast<QWidget *>(parent());
    if(ptrParent)
    {
        const QPoint parent_pos = ptrParent->pos() + event->globalPos() - last_mouse_position_;
        ptrParent->move(parent_pos);
        last_mouse_position_ = event->globalPos();
    }
    else {
        const QPoint position = pos() + event->globalPos() - last_mouse_position_;
        move(position);
        last_mouse_position_ = event->globalPos();
    }
}

void TitleBar_v2::titleConnectionsBuilder(QWidget *widget)
{
    if(!widget)
    {
        connect(minimum, &QToolButton::clicked, this, &QWidget::showMinimized);
        connect(close, &QToolButton::clicked, this, &QWidget::close);
        return;
    }
    connect(minimum, &QToolButton::clicked, widget, &QWidget::showMinimized);
    connect(close, &QToolButton::clicked, widget, &QWidget::close);
}

bool TitleBar_v2::eventFilter(QObject *watched, QEvent *event)
{
    if(close   == watched ||
       minimum == watched)
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

void TitleBar_v2::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event);

    QStyleOption opt;

    opt.init(this);

    QPainter p(this);

    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

}

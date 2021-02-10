#include <QtWidgets>
#include "volumebutton.h"

VolumeButton::VolumeButton(QWidget *parent)
    : QToolButton(parent)
{
    //立刻弹出
    setPopupMode(QToolButton::InstantPopup);
    setIcon(QPixmap(":/images/volume.png"));
    //弹出窗口
    popup = new QWidget(this);
    popup->setObjectName("VolumePopup");

    //滑条
    volumeSlider = new QSlider(Qt::Horizontal, popup);
    //设置范围
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(100);
    //将volumeSlider值的改变与volumeChanged信号函数连接
    connect(volumeSlider, &QAbstractSlider::valueChanged, this, &VolumeButton::volumeChanged);

    //显示音量大小
    num = new QLabel(this);
    num->setObjectName("volume");
    num->setNum(100);
    num->setAlignment(Qt::AlignCenter);
    num->setMinimumWidth(num->sizeHint().width());
    //将volumeSlider的值改变事件与num的setNum连接
    connect(volumeSlider, &QAbstractSlider::valueChanged, num, QOverload<int>::of(&QLabel::setNum));

    //布局
    QBoxLayout *popupLayout = new QHBoxLayout(popup);
    popupLayout->setMargin(2);
    popupLayout->addWidget(volumeSlider);
    popupLayout->addWidget(num);

    //事件
    QWidgetAction *action = new QWidgetAction(this);
    action->setDefaultWidget(popup);

    //弹出菜单
    menu = new QMenu(this);
    menu->addAction(action);
    setMenu(menu);
}

int VolumeButton::volume() const
{
    return volumeSlider->value();
}

void VolumeButton::setVolume(int volume)
{
    volumeSlider->setValue(volume);
}

//volumeSlider的value上升, 则触发该事件
void VolumeButton::increaseVolume()
{
    volumeSlider->triggerAction(QSlider::SliderPageStepAdd);
}

//volumeSlider的value下降, 则触发该事件
void VolumeButton::decreaseVolume()
{
    volumeSlider->triggerAction(QSlider::SliderPageStepSub);
}

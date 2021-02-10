#ifndef HELP_H
#define HELP_H

#include <QWidget>

QT_FORWARD_DECLARE_CLASS(TitleBar_v2)
QT_FORWARD_DECLARE_CLASS(QLabel)

class Help : public QWidget
{
    Q_OBJECT
public:
    explicit Help(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    TitleBar_v2 *titleBar;
    QLabel *documents;
};

#endif // HELP_H

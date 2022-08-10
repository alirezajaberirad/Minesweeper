#ifndef CUSTOMIZEDPUSHBUTTON_H
#define CUSTOMIZEDPUSHBUTTON_H
#include <QPushButton>
#include<qpushbutton.h>
#include <QMouseEvent>


class CustomizedPushButton: public QPushButton
{

    Q_OBJECT

public:
    explicit CustomizedPushButton(QWidget *parent = 0);

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void rightClicked();
    void clicked();

public slots:

};

#endif // CUSTOMIZEDPUSHBUTTON_H

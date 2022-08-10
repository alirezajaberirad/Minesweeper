#include "CustomizedPushButton.h"

CustomizedPushButton::CustomizedPushButton(QWidget *parent) :
    QPushButton(parent)
{
}

void CustomizedPushButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
        emit rightClicked();
    else if(e->button()==Qt::LeftButton)
        emit clicked();
}



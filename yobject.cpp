#include "yobject.h"

yObject::yObject(QWidget * parent) : QLabel(parent)
{
    this->setMouseTracking(true);
    this->scene=(yScene*) parent;
//        QMovie * mov=new QMovie("sa");
//    this->setMovie(mov);
}


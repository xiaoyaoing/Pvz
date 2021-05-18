#ifndef YFLY_H
#define YFLY_H


#include <QLabel>
#include <QMovie>

#include<yobject.h>
#include<yscene.h>


#include"yplant.h"
class yPlant;
class yFly : public yObject
{
    Q_OBJECT;
public:
   double speed;
   virtual void act()=0;
    yFly(QWidget * parent);
};



class pea : public yFly{
    Q_OBJECT;


public:
    QMovie * peafly=new QMovie (":/flys/Pea.gif");
    int diecounter=0;
    int row;
    int timecounter=50;
    int status=0;
    pea(QWidget * parent,int row,int type);
   ~pea();
    void act();
};

class sunFly: public  yFly{
    Q_OBJECT;
public :
    QMovie * movie=new QMovie(":/flys/Sun.gif");
    int counter=0;
    int timemax=200;
    int xpos;
    int ypos;
    bool fromsky;
    sunFly(QWidget * parent,bool fromsky);
    ~sunFly();
    void act();
    void mousePressEvent(QMouseEvent* event);
};

class basketBall : public yFly{
    Q_OBJECT;
public:
    QPoint p;
    QMovie * mov=new QMovie(":/flys/baksetball.png");
    basketBall(QWidget * parent,QPoint  p,QPoint p2);
    basketBall();
    basketBall(QWidget * parent,int xpos);
    ~basketBall();
    void act();
    int height=50;
    int status=0;
    double ay=0;
    float t;
    float  yspeed;
    int timecounter=0;
};

//class icePea : public pea{
//    Q_OBJECT;
//public :
//    QMovie *  peafly=new QMovie (":/flys/Pea.gif");
//    bool ice=true;
//    icePea(QWidget * parent,int row);
//};




#endif // YFLY_H

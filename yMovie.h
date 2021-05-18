#ifndef YMOVIE_H
#define YMOVIE_H

#include "yscene.h"
#include "yobject.h"
#include <QMovie>
#include <QPushButton>
#include"maindialog.h"

class MainDialog;
class yMovie :public yObject
{
    Q_OBJECT;
public:
    bool alive=true;
    yMovie(QWidget * parent);
    virtual void act()=0;
    int status=0;

};


class yZombieDie : public yMovie{
    Q_OBJECT;
public:
    QMovie * die;
    yZombieDie(QWidget * parent,int type,QPoint pos);
    ~yZombieDie();
    void act();




};

class sunNum : public yMovie{
    Q_OBJECT;
public :
    QMovie * sunBack=new QMovie(":/interfaces/SunBack.png");
    QLabel * suntext=new QLabel(this);
    sunNum(QWidget * parent);
    ~sunNum();
    void act();

};

class scoreBoard : public yMovie{
    Q_OBJECT;
public :
    QMovie * back=new QMovie(":/interfaces/SunBack.png");
    QLabel * scoretext=new QLabel(this);
    scoreBoard(QWidget * parent);
    ~scoreBoard();
    void act();
};

class stopBoard : public yMovie{
    Q_OBJECT;
public :
    int status=0;
    void act();
    QMovie * back=new QMovie(":/interfaces/SunBack.png");
    QPushButton * stopText=new QPushButton(this);
    stopBoard(QWidget * parent);
    void stop();
};

class zombieBoomDie : public yMovie{
       Q_OBJECT;
public :
    QMovie * mov=new QMovie(":/Zombies/zombieBoomDie.gif");
    void act();
    zombieBoomDie(QWidget * parent);
    ~zombieBoomDie(); 



};

class boomMovie : public yMovie{
    Q_OBJECT;
public :
    int cnt=0;
    QMovie * mov=new QMovie(":/others/boomMovie.gif");
    void act();
    boomMovie(QWidget * parent,QPoint pos);
    ~boomMovie();

};

class lossMovie :public yMovie{
public :
    int cnt=0;
        QMovie * mov=new QMovie(":/others/loss.png");
        void act();
       lossMovie(QWidget * parent);
      ~lossMovie();

};

class fire : public yMovie{
    Q_OBJECT;
public:
    int t=10;
    QMovie * mov=new QMovie(":/flys/Fire.gif");
     fire(QWidget * parent,QPoint pos);
     void act();
};





#endif // YMOVIE_H

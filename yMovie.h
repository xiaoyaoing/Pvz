#ifndef YMOVIE_H
#define YMOVIE_H

#include "yscene.h"
#include "yobject.h"
#include <QMovie>


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
    yZombieDie(QWidget * parent);
    ~yZombieDie();
    void act();
private:
    QMovie * die=new QMovie(":/Zombies/ZombieDie.gif");


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

class zombieBoomDie : public yMovie{
       Q_OBJECT;
public :
    QMovie * mov=new QMovie(":/Zombies/zombieBoomDie.gif");
    void act();
    zombieBoomDie(QWidget * parent);
    ~zombieBoomDie();

};

#endif // YMOVIE_H

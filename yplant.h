#ifndef YPLANT_H
#define YPLANT_H



#include <QMovie>
#include "yobject.h"
#include "yzombie.h"
#include "yfly.h"
class yZombie ;
class yPlant : public yObject{
    Q_OBJECT;
public:
   yPlant * protectedPlant=nullptr;
    bool canBeEaten=true;
    int row; int column;
    int timecounter=100;
    int plantType=0;
    explicit yPlant(QWidget * parent=0) ;
    virtual void getDamage(int x,yZombie * zombie);
    void getDamage(int damage);
   // void judge();
    void act();
    bool canbeJumpid=true;
};

class peaShooter : public yPlant{
    Q_OBJECT;
public:
    explicit peaShooter(QWidget * parent=0);
    void act();
protected: QMovie * mov=new QMovie(":/plants/Peashooter.gif");
};

class sunFlower : public yPlant{
public :
    sunFlower(QWidget * parent=0);
    void act();
    ~sunFlower();
protected:
    QMovie * mov=new QMovie(":/plants/SunFlower.gif");

};

class icePeaShooter : public yPlant{
    Q_OBJECT;
public:
    explicit icePeaShooter (QWidget * parent=0);
    void act();
    ~icePeaShooter();
protected: QMovie * mov=new QMovie(":/plants/IcePeaShooter.gif");
};

class repeater : public yPlant{
    Q_OBJECT;
public:
    explicit repeater (QWidget * parent=0);
    void act();
    ~repeater();
    protected: QMovie * mov=new QMovie(":/plants/Repeater.gif");
};

class wallNut : public yPlant{
    Q_OBJECT;
public :
    explicit wallNut(QWidget * parent);
    void act();
    ~wallNut();
protected:
    int status=0;
    QMovie * wallNutFirstMov=new QMovie(":/plants/WallNut.gif");
    QMovie * wallNutSecondMov=new QMovie(":/plants/Wallnut_1.gif");
    QMovie * wallNutThirdMov=new QMovie(":/plants/Wallnut_2.gif");

};


class cherryBomb : public yPlant{
    Q_OBJECT;
      public :
    explicit cherryBomb(QWidget * parent);
    void act();
    ~cherryBomb();
    int status=0;
protected: QMovie * mov=new QMovie(":/plants/CherryBomb.gif");
public slots:
   void die();
};

class tallWallNut : public yPlant{
    Q_OBJECT;
public :
    explicit tallWallNut(QWidget * parent);
    void act();
    ~tallWallNut();
protected:
    int status=0;
    QMovie * wallNutFirstMov=new QMovie(":/plants/tallWallNut.gif");
    QMovie * wallNutSecondMov=new QMovie(":/plants/tallWallNut1.gif");
};

class  squash: public yPlant{
      Q_OBJECT;
public :
    int status=0;
    squash(QWidget * parent);
    void act();
    ~squash();
    QMovie * first=new QMovie(":/plants/squash1.gif");
    QMovie * second=new QMovie(":/plants/squash2.gif");

                             };

class garlic : public yPlant{
public :
    QMovie * first=new QMovie(":/plants/garlic1.gif");
    QMovie * second=new QMovie(":/plants/garlic2.gif");
    QMovie * third=new QMovie(":/plants/garlic3.gif");
    int status=0;
    int firstHealth;
    int secondHealth;
    void act();
    garlic(QWidget * parent);
     ~garlic();
    void getDamage(int x,yZombie * zombie);
};

class pumpkinHead : public yPlant{
public:
    QMovie * first=new QMovie(":/cards/pumkin1.gif");
    QMovie * second=new QMovie(":/cards/pumkin2.gif");
    QMovie * third=new QMovie(":/cards/pumkin3.gif");
    int status=0;
   // yPlant * plant;
    void act();
    yPlant * plant;
    pumpkinHead(QWidget * parent,yPlant * p);
    ~pumpkinHead();
};

class fireTree : public yPlant{
public :
    QMovie * mov=new QMovie();
    fireTree(QWidget * parent);
      ~fireTree();

};

class eatFlower : public yPlant{

public :
    int status=0;
    int timecounter=0;
    int timemax=42*50;
    QMovie * m1=new QMovie(":/plants/eatFlower.gif");
      QMovie * m2=new QMovie(":/plants/eatFlower1.gif");
        QMovie * m3=new QMovie(":/plants/eatFlower2.gif");
        eatFlower(QWidget * parent);
    void act();

};




#endif

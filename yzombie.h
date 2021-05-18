#ifndef YZOMBIE_H
#define YZOMBIE_H

#include<QMovie>
#include<stdlib.h>
#include "yscene.h"
#include "yobject.h"
#include "yplant.h"
class yPlant;
enum commonZombieType{
    Common=0,
    Bucket=1,
    Cone=2,
    Flag=3,
    Shield=4
};

class yZombie  : public yObject

{
    Q_OBJECT
public:
    bool withHead=true;
    int type;
    bool canBeiced=true;
    int attackMax=50;
    int attackCounter=0;
    int garlicStatus=0; //吃大蒜以后
    bool iced =false;
    int iceCounter=0;
    int iceTimeMax=150;
    double  speed;
    double originspeed;
    yZombie(QWidget * parent);
    virtual void getDamage(int val);
    int getColmun();
    double ax=0;
    void act();
//public slots :
//    void die();
};

class yCommonZombie : public yZombie
{
    Q_OBJECT;
public :  

    bool isSpecial=false;
    void getDamage(int val);
    void act();
    void set(int x1,int y1,int x2,int y3);
    yCommonZombie(QWidget * parent,int zombieType);
    ~yCommonZombie();
   QMovie   * commonZombieWalk;
   QMovie * commonZombieAttack;
   QMovie * specialZombieWalk=nullptr;;
   QMovie  * specialZombieAttack=nullptr;
   int commonZombieHealth=270;

   //int row;


};

class jumpZombie : public yZombie{
public :
    void act();
    int status=0;

    bool canJump=true;
    QMovie * fastWalk=new QMovie(":/Zombies/PoleZombie.gif");
    QMovie * slowWalk=new QMovie(":/Zombies/PoleZombieWalk.gif");
    QMovie * attack=new QMovie(":/Zombies/PoleZombieAttack.gif");
    QMovie * jump1=new QMovie(":/Zombies/PoleZombieJump.gif");
    QMovie * jump2=new QMovie(":/Zombies/PoleZombieJump2.gif");

    jumpZombie(QWidget * parent);
    ~jumpZombie();


};

class newspaperZombie : public yZombie{
public :
    int  newStatus=0;
    QMovie * attack1=new QMovie(":/Zombies/newAttack1.gif");
    QMovie * walk3=new QMovie(":/Zombies/newWalk1.gif");
    QMovie * attack =new QMovie(":/Zombies/NewsAttack.gif");
    QMovie * newAttack =new QMovie(":/Zombies/NewsAttack_1.gif");
      QMovie * walk1 =new QMovie(":/Zombies/NewsWalk_1.gif");
      QMovie * walk2 =new QMovie(":/Zombies/NewsWalk.gif");
          QMovie * lost =new QMovie(":/Zombies/NewsLost.gif");
     newspaperZombie(QWidget * parent);
     ~newspaperZombie();
     void act();
};

class clownZombie : public yZombie{
    Q_OBJECT;
public :
    int boomCounter;
    int boomTime;
    int status=0;
    void act();
    clownZombie(QWidget * parent);
    ~clownZombie();
    QMovie  * walk1=new QMovie(":/Zombies/clawnWalk.gif");
     QMovie  * walk2=new QMovie(":/Zombies/clownWalk1.gif");
     QMovie * attack1=new QMovie(":/Zombies/clownAttack.gif");
      QMovie  * attack2=new QMovie(":/Zombies/clownAttack1.gif");
      QMovie * open=new QMovie(":/Zombies/clown.gif");

};

class basketBallZombie:  public yZombie{
    Q_OBJECT;
public :
    int basketballNum=10;
    int targetx;
    QMovie * mov1=new QMovie(":/Zombies/baksetballzombie.gif");
    QMovie * mov2=new QMovie(":/Zombies/basketball.Zombie2.gif");
    void act();
    basketBallZombie(QWidget * parent);
    ~basketBallZombie();
};

#endif // YZOMBIE_H

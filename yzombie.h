#ifndef YZOMBIE_H
#define YZOMBIE_H

#include<QMovie>
#include<stdlib.h>
#include "yscene.h"
#include "yobject.h"
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
    bool iced =false;
    int iceCounter=0;
    int iceTimeMax=150;
    yZombie(QWidget * parent);
    void getDamage(int val);
    double ax=0;
//public slots :
//    void die();
};

class yCommonZombie : public yZombie
{
    Q_OBJECT;
public :  
    bool isSpecial=false;
    void act();
    void set(int x1,int y1,int x2,int y3);
    yCommonZombie(QWidget * parent,int zombieType);
    ~yCommonZombie();
   QMovie   * commonZombieWalk;
   QMovie * commonZombieAttack;
   QMovie * specialZombieWalk=nullptr;;
   QMovie  * specialZombieAttack=nullptr;
   int commonZombieHealth=270;
   int attackMax=50;
   QMovie * dieMovie;
   double  speed;
   double originspeed;
   //int row;
   int attackCounter=50;

};

#endif // YZOMBIE_H

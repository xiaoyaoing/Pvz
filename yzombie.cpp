#include "yzombie.h"

yZombie::yZombie(QWidget * parent) : yObject(parent)
{

}


void yZombie:: getDamage(int val){
    this->health-=val;
    if(this->health<=0)
    {
       this->alive=false;
    }
}

//void yZombie:: die(){
//    this->
//    delete  this;
//}



yCommonZombie ::yCommonZombie(QWidget * parent,int zombieType) :yZombie(parent){

    if((rand()%2)==0)
        this->commonZombieWalk=new QMovie(":/Zombies/Zombie_1.gif");
    else this->commonZombieWalk=new QMovie(":/Zombies/Zombie_2.gif");
   // this->commonZombieWalk=new QMovie(":/Zombies/ZombieBucket.gif");
    this->commonZombieAttack=new QMovie(":/Zombies/ZombieAttack.gif");
    qDebug()<<zombieType;
    switch (zombieType) {
    case(Common):
    {
        commonZombieWalk->start();
        commonZombieAttack->start();
        this->health=commonZombieHealth;
        break;
    }
    case (Bucket):{
        this->isSpecial=true;
        this->specialZombieAttack=new QMovie(":/Zombies/ZombieBucketAttack.gif");

        this->specialZombieWalk=new QMovie(":/Zombies/ZombieBucket.gif");
        qDebug()<<specialZombieWalk->isValid()<<"Bucket";
        this->health=1100;
        break;
    }
    case(Cone) : {
    this->isSpecial=true;
    this->specialZombieWalk=new QMovie(":/Zombies/ZombieCone.gif");
        qDebug()<<specialZombieWalk->isValid()<<"Zone";
    this->specialZombieAttack=new QMovie(":/Zombies/ZombieConeAttack.gif");
    this->health=640;
        break;
    }

   case(Flag):{
        this->commonZombieAttack=new QMovie(":/Zombies/ZombieFlagAttack.gif");
        this->commonZombieWalk=new QMovie(":/Zombies/ZombieFlag.gif");
        this->health=270;
        break;
    }

   case(Shield):{
    this->isSpecial=true;
    this->specialZombieAttack=new QMovie(":/Zombies/ZombieShieldAttack.gif");
    this->specialZombieWalk=new QMovie(":/Zombies/ZombieShield.gif");
    this->health=1100;
        qDebug()<<specialZombieWalk->isValid()<<"Shield";
        break;
    }}

     this->speed=0.35;
    originspeed=speed;
      this->strength=100;
     if(specialZombieAttack!=nullptr)     specialZombieAttack->start();
     if(specialZombieWalk!=nullptr) specialZombieWalk->start();
     if(commonZombieWalk!=nullptr) commonZombieWalk->start();
     if(commonZombieAttack!=nullptr) this->commonZombieAttack->start();
     if(isSpecial)
         this->setMovie(specialZombieWalk);
     else this->setMovie(commonZombieWalk);
     if(isSpecial)
     qDebug()<<specialZombieWalk;
    this->raise();
    this->show();

}

yCommonZombie :: ~yCommonZombie() {
    delete this->commonZombieAttack;
    delete this->commonZombieWalk;
   // delete this->dieMovie;
}

void  yCommonZombie:: set(int x1,int y1,int x2,int y3){
    this->setGeometry(x1,y1,x2,y3);
}



void yCommonZombie:: act(){
    if(iced){
        qDebug()<<"iced"<<speed;
        if(speed==originspeed) speed/=2;
        iceCounter++;
        if(iceCounter==iceTimeMax)
        {
            speed*=2;
            iced=false;
        }
    }

    if(this->isSpecial && this->health<=commonZombieHealth){
        this->isSpecial=false;
        this->setMovie(commonZombieWalk);
       // commonZombieWalk->start();
    }
    if(this->health<=0){
        this->setMovie(this->dieMovie);
        this->dieMovie->start();
        return ;
    }
    this->raise();
   yPlant * p;
   for(int i=0;i<this->scene->plants.size();i++){
       p=this->scene->plants.at(i);
       if(abs(p->x()-this->x())<=20 && this->row==p->row && p->canBeEaten)
       {
           if(isSpecial)
           {
           this->setMovie(this->specialZombieAttack);}
           else {
               this->setMovie(this->commonZombieAttack);}
           if(attackCounter==attackMax)
           {p->getDamage(this->strength,this);
               attackCounter=0;
           }
           else attackCounter++;
           return ;
       }
   }
   attackCounter=30;
   if(!isSpecial)
   { this->setMovie(commonZombieWalk);
      }
   else {this->setMovie(specialZombieWalk);}
   ax+=speed;
   if(ax>=1)
   {this->move(this->x()-1,this->y());
   ax-=1;}

}








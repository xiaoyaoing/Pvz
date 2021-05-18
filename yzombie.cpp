#include "yzombie.h"
#include<QDebug>
yZombie::yZombie(QWidget * parent) : yObject(parent)
{

}

void yZombie :: act(){
    if(iced){

       // this->setStyleSheet("background-color: rgba(0, 0, 0, 50%);");
        if(speed==originspeed) speed/=2;
        iceCounter++;
        if(iceCounter==iceTimeMax)
        {
            speed*=2;
            iced=false;
        }
    }
    if(this->garlicStatus!=0){
        if(this->y()!=10+(row-1)*scene->cell_y){
            this->move(this->x(),this->y()+1*garlicStatus);
        }
        else garlicStatus=0;
        return ;
    }
}
void yZombie:: getDamage(int val){
    if(health<=val && this->alive){
        yZombieDie * d=new yZombieDie(scene,type,pos());
        scene->movies.append(d);
        if(withHead ){
            d=new yZombieDie(scene,20+type,pos());
                    scene->movies.append(d);
        }
    }

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

    type=zombieType;
    if((rand()%2)==0)
        this->commonZombieWalk=new QMovie(":/Zombies/Zombie_1.gif");
    else this->commonZombieWalk=new QMovie(":/Zombies/Zombie_2.gif");
   // this->commonZombieWalk=new QMovie(":/Zombies/ZombieBucket.gif");
    this->commonZombieAttack=new QMovie(":/Zombies/ZombieAttack.gif");
    qDebug()<<zombieType;
    switch (zombieType) {
    case(Common):
    {
        this->xoffset=60;
        commonZombieWalk->start();
        commonZombieAttack->start();
        this->health=commonZombieHealth;
        break;
    }
    case (Bucket):{
        xoffset=60;
        this->isSpecial=true;
        this->specialZombieAttack=new QMovie(":/Zombies/ZombieBucketAttack.gif");

        this->specialZombieWalk=new QMovie(":/Zombies/ZombieBucket.gif");
        qDebug()<<specialZombieWalk->isValid()<<"Bucket";
        this->health=1100;
        break;
    }
    case(Cone) : {
        this->xoffset=90;
    this->isSpecial=true;
    this->specialZombieWalk=new QMovie(":/Zombies/ZombieCone.gif");
        qDebug()<<specialZombieWalk->isValid()<<"Zone";
    this->specialZombieAttack=new QMovie(":/Zombies/ZombieConeAttack.gif");
    this->health=640;
        break;
    }

   case(Flag):{
        xoffset=50;
        this->commonZombieAttack=new QMovie(":/Zombies/ZombieFlagAttack.gif");
        this->commonZombieWalk=new QMovie(":/Zombies/ZombieFlag.gif");
        this->health=270;
        break;
    }

   case(Shield):{
        xoffset=80;

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

void yCommonZombie:: getDamage(int val){

    yZombie::getDamage(val);
    if((type==Shield  || type==Bucket) && isSpecial)
        QSound::play(":/sounds/ShieldHit.wav");

}



void yCommonZombie:: act(){
    if(isSpecial==false) xoffset=60;
    yZombie::act();


    if(this->isSpecial && this->health<=commonZombieHealth){
        this->isSpecial=false;
        this->setMovie(commonZombieWalk);
       // commonZombieWalk->start();
    }
    if(this->health<=0){    

    }

   yPlant * p;
   for(int i=0;i<this->scene->plants.size();i++){
       p=this->scene->plants.at(i);
       if(getColmun()==p->column && this->row==p->row && p->canBeEaten)
       {
           if(isSpecial)
           {
           this->setMovie(this->specialZombieAttack);}
           else {
               this->setMovie(this->commonZombieAttack);}
           if(attackCounter==attackMax)
           {

              QSound::play(":/sounds/Eat.wav");
               if(p->protectedPlant!=nullptr)
               p->protectedPlant->getDamage(this->strength,this);
               else
               p->getDamage(this->strength,this);
               if(this->garlicStatus!=0){
                   if(!isSpecial)
                   { this->setMovie(commonZombieWalk);
                      }
                   else {this->setMovie(specialZombieWalk);}
               }
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

jumpZombie :: jumpZombie(QWidget * parent):yZombie(parent){
    type=5;
    this->xoffset=150;
    strength=100;
    this->yoffset=50;
    this->speed=0.70;
    this->originspeed=speed;
    fastWalk->start();
    this->health=500;
    attack->start();
    slowWalk->start();
    this->setMovie(fastWalk);
    this->raise();
    this->show();
}

int yZombie::getColmun(){


       return (this->x()+xoffset-scene->rect.left())/scene->cell_x+1;


}

void jumpZombie:: act(){

    if(health<=200 && withHead ){
        withHead=false;
        slowWalk=new QMovie(":/Zombies/jumpWalk3.gif");
        fastWalk=new QMovie(":/Zombies/jumpWalk2.gif");
         attack=new QMovie(":/Zombies/jumpAttack2.gif");
         slowWalk->start();
         attack->start();
         fastWalk->start();
         yZombieDie * d=new yZombieDie(scene,type+20,pos());
         scene->movies.append(d);
    }
    //if(status==3) xoffset=250;
    yZombie :: act();
    if(garlicStatus!=0) return ;
    yPlant * p;
    if(status==1){
        qDebug()<<jump1->currentFrameNumber();
        if(jump1->currentFrameNumber()==jump1->frameCount()-1){

            if(canJump)
            {status=2;
                jump2->start();
                this->move(this->x()-200,y());
            this->setMovie(jump2);}
            else
            {  status=3;
                this->move(this->x()-50,y());
                this->setMovie(slowWalk);
               // xoffset=80;
                speed/=2;
            }
        }
    }
    else
    if(status==2){
        if(jump2->currentFrameNumber()==jump2->frameCount()-1){
            status=3;
            this->setMovie(slowWalk);
        //    xoffset=80;
            speed/=2;
        }
    }
    if(status==1 || status==2){
//        this->ax+=speed;
//        if(ax>=1){
//            this->move(this->x()-1,y());
//            ax-=1;
//        }

        return;
    }

    for(int i=0;i<this->scene->plants.size();i++){
        p=this->scene->plants.at(i);
        if(getColmun()==p->column && this->row==p->row && p->canBeEaten)
        {

             qDebug()<<getColmun()<<p->column;
            if(status==0){
                canJump=p->canbeJumpid;
                QSound::play(":/sounds/Pole.wav");
                this->setMovie(jump1);
                jump1->start();
                status=1;
                return;
            }
            else {


                this->setMovie(attack);
                if(attackCounter==attackMax)
                {   QSound::play(":/sounds/Eat.wav");
                    if(p->protectedPlant!=nullptr)
                    p->protectedPlant->getDamage(this->strength,this);
                    else
                    p->getDamage(this->strength,this);
                    if(this->garlicStatus!=0){
                       this->setMovie(slowWalk);
                    return ;}

                    attackCounter=0;}

                else attackCounter++;
                return ;

        }}}

        if(status==0)
            this->setMovie(fastWalk);
        else

        this->setMovie(slowWalk);
        this->ax+=speed;

        if(ax>=1){
            this->move(this->x()-1,y());
            ax-=1;
        }

    }

jumpZombie :: ~jumpZombie(){
    delete jump1;
    delete jump2;
    delete slowWalk;
    delete fastWalk;
    delete attack;
}

newspaperZombie:: newspaperZombie(QWidget * parent): yZombie(parent){
    type=6;
    this->xoffset=100;
    this->health=450;
    this->speed=0.35;

    this->originspeed=speed;
    strength=100;
    walk1->start();
    walk2->start();
    attack->start();
    newAttack->start();
    this->setMovie(walk1);
    walk3->start();
    attack1->start();
    this->show();
}
newspaperZombie:: ~newspaperZombie  (){
    delete walk1;
    delete walk2;
    delete  walk3;
    delete attack;
    delete attack1;
    delete newAttack;
}
void newspaperZombie:: act(){
    if(health<100 && withHead){
        withHead=false;
        yZombieDie * d=new yZombieDie(scene,20+type,pos());
        scene->movies.append(d);
    }
    yZombie::act();
    if(this->health<=200 && newStatus==0){
       newStatus =1;
       QSound::play(":/sounds/NewsLost.wav");
        this->setMovie(lost);
       lost->start();
        return ;
    }
    if(newStatus==1){
        if(lost->currentFrameNumber()==lost->frameCount()-1){
            speed*=3;
            originspeed*=3;
            walk2->start();
            this->setMovie(walk2);
            newStatus=2;
        }
        return ;
    }
    yPlant * p;
    for(int i=0;i<this->scene->plants.size();i++){
        p=this->scene->plants.at(i);
        if(getColmun()==p->column && this->row==p->row && p->canBeEaten)
        {
            qDebug()<<this->getColmun()<<pos();
            if(newStatus==0)
            this->setMovie(newAttack);
            else if(health>=100)this->setMovie(attack);
            else this->setMovie(attack1);
                if(attackCounter==attackMax)
                {   QSound::play(":/sounds/Eat.wav");
                    if(p->protectedPlant!=nullptr)
                    p->protectedPlant->getDamage(this->strength,this);
                    else
                    p->getDamage(this->strength,this);
                    if(this->garlicStatus!=0){
                        if(newStatus==0)
                       this->setMovie(walk1);
                        else  if(this->health>=100) this->setMovie(walk2);
                        else this->setMovie(walk3);
                    return ;}
                    attackCounter=0;}
                else attackCounter++;
                return ;}}
    if(newStatus==0)
   this->setMovie(walk1);
    else  if(this->health>=100) this->setMovie(walk2);
    else this->setMovie(walk3);

    this->ax+=speed;
    if(ax>=1){
        this->move(this->x()-1,y());
        ax-=1;
    }

}

void clownZombie:: act(){
    if(status==1 && boomCounter==50){
        QSound::play(":/sounds/Boom.wav");
        yPlant * p;
        for(int i=0;i<this->scene->plants.size();i++){
            p=this->scene->plants.at(i);
            if(abs(getColmun()-p->column)<=1 && abs(this->row-=p->row)<=1 && p->canBeEaten)
            {
                p->alive=false;
            }}
            yMovie  *boom=new boomMovie(this->scene,this->getRealPos());
            this->scene->movies.append(boom);
            this->alive=false;}
   if(status==1 && open->currentFrameNumber()==open->frameCount()-1){
       open->stop();
       boomCounter++;
       return ;
   }


   if(status==1) return ;
   if(boomCounter==boomTime){
       status=1;
       boomCounter=0;
       open->start();
       this->setMovie(open);
       return ;
   }

   yPlant * p;
   for(int i=0;i<this->scene->plants.size();i++){
       p=this->scene->plants.at(i);
       if(getColmun()==p->column && this->row==p->row && p->canBeEaten)
       {
           if(health>=170)
           this->setMovie(attack1);
           else this->setMovie(attack2);

               if(attackCounter==attackMax)
               {
                   QSound::play(":/sounds/Eat.wav");
                   if(p->protectedPlant!=nullptr)
                   p->protectedPlant->getDamage(this->strength,this);
                   else
                   p->getDamage(this->strength,this);
                   if(this->garlicStatus!=0){
                       if(health>=170)
                       this->setMovie(walk1);
                       else this->setMovie(walk2);
                   return ;}
                   attackCounter=0;}
               else attackCounter++;
               return ;}}
   if(health>=170)
   this->setMovie(walk1);
   else this->setMovie(walk2);
   boomCounter++;
   this->ax+=speed;
   if(ax>=1){
       this->move(this->x()-1,y());
       ax-=1;
   }
}
clownZombie:: clownZombie(QWidget * parent):yZombie((parent)){
    type=7;
    yoffset=20;
    strength=100;
   this->health=500;
    this->xoffset=90;
    this->speed=0.66;
    boomTime=rand()%5+10;
    boomTime  *=50;
    walk1->start();
    walk2->start();
    attack2->start();
    attack1->start();
    //open->start();
    this->setMovie(walk1);

}
clownZombie:: ~clownZombie(){
    delete walk1;
    delete  walk2;
    delete attack1;
    delete attack2;
    delete open;
}


void basketBallZombie:: act(){

    if(health<=300) this->setMovie(mov2);
    if(this->x()+xoffset>=targetx){
        this->ax+=speed;
        if(ax>=1){
            this->move(this->x()-1,y());
            ax-=1;
        }
        return ;
    }
    yPlant * p;
    foreach(p,scene->plants){
        if(basketballNum==0) break;
        if(p->row==row && p->canBeEaten){
            if(attackCounter==attackMax){
                basketballNum--;
            basketBall * b=new basketBall(this->scene,p->pos(),QPoint(x()+100,y()+100));
            b->row=this->row;
           // b->move(this->pos());

            scene->flys.append(b);
            attackCounter=0;
        }
        else attackCounter++;
        return ;}
    }
    if(basketballNum==0){
        this->alive=false;
        yZombie * z=new yCommonZombie(this->scene,0);
        this->scene->zombies.append(z);
        qDebug()<<pos();
        qDebug()<<getRealPos();
        z->move(x()+xoffset,y()+yoffset);
        z->row=row;
    }
}
basketBallZombie::  basketBallZombie(QWidget * parent)  :yZombie(parent){
      type=8;
    xoffset=180;
    yoffset=100;
    targetx=1000+rand()%100-50;
    this->health=500;
    this->speed=0.5;
    mov1->start();
    mov2->start();
    this->setMovie(mov1);
    attackMax=100;


}
basketBallZombie::  ~basketBallZombie(){
    delete  mov1;
    delete mov2;
}










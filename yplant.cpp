#include <iostream>
#include <vector>
#include "yplant.h"
yPlant ::yPlant(QWidget *parent) :yObject(parent){

}

void yPlant::  act(){

}

void yPlant:: getDamage(int x,yZombie * zombie){
    this->health-=x;
    //qDebug()<<"豌豆射手受伤了";
    if(this->health<=0)
        this->alive=false;
}




peaShooter::peaShooter(QWidget *parent) : yPlant(parent){
   // qDebug()<<"peashooter";
    this->setMovie(mov);
    this->mov->start();
    this->show();
    this->health=300;
    this->strength=15;
    this->timecounter=70;
}

void peaShooter::act() {
    this->raise();
    yZombie * z;
    foreach(z,this->scene->zombies){
        if(z->row==row)
        {
            if(timecounter==70){
                timecounter=0;
                pea * p=new pea(this->scene,this->row,0);

                p->setGeometry(this->x(),this->y()+10,56,34);
                this->scene->flys.append(p);
                return ;
            }
            timecounter++;
            return ;
        }
    }
    timecounter=70;
}

sunFlower:: sunFlower(QWidget * parent):yPlant(parent)
{
    this->setMovie(mov);
    this->mov->start();
    this->show();
    this->health=300;
    this->timecounter=0;
}

void sunFlower::act(){
    if(timecounter==300){
        sunFly * sunfly=new sunFly(this->scene,false);
        sunfly->setGeometry(this->x()+20,this->y()+20,79,79);
        sunfly->show();
        this->scene->flys.append(sunfly);
        timecounter=0;
        return ;
    }
    timecounter++;
}

sunFlower ::  ~sunFlower(){
    delete  mov;
}

void icePeaShooter:: act(){
    this->raise();
    yZombie * z;
    foreach(z,this->scene->zombies){
        if(z->row==row)
        {
            if(timecounter==50){
                timecounter=0;
                pea * p=new pea(this->scene,this->row,1);
                p->setGeometry(this->x(),this->y()+10,56,34);
                this->scene->flys.append(p);
                return ;
            }
            timecounter++;
            return ;
        }
    }
    timecounter=50;
}

icePeaShooter :: icePeaShooter(QWidget * parent) :yPlant(parent){
    this->setMovie(mov);
    this->mov->start();
    this->show();
    this->health=100;
    this->strength=15;
    this->timecounter=50;
}

icePeaShooter :: ~icePeaShooter(){
        delete mov;
}

repeater :: ~repeater(){
    delete mov;
}

repeater  :: repeater(QWidget * parent) : yPlant(parent){
    this->setMovie(mov);
    this->mov->start();
    this->show();
    this->health=100;
    this->strength=15;
    this->timecounter=45;

}

void repeater::act() {
    this->raise();
    yZombie * z;
    foreach(z,this->scene->zombies){
        if(z->row==row)
        {
            if(timecounter==45 || timecounter==50){
                if(timecounter==50)
                    timecounter=0;
              //  else timecounter++;
                pea * p=new pea(this->scene,this->row,0);

                p->setGeometry(this->x(),this->y()+10,56,34);
                this->scene->flys.append(p);
                return ;
            }
            timecounter++;
            return ;
        }
    }
    timecounter=50;
}

wallNut ::wallNut(QWidget * parent) : yPlant(parent){
    this->setMovie(wallNutFirstMov);
    this->wallNutFirstMov->start();
    this->show();
    this->health=400;
}

void wallNut :: act(){
    if(this->health<=200 && health>=100 && status==0){
        wallNutSecondMov->start();
        this->setMovie(wallNutSecondMov);
        delete this->wallNutFirstMov;
        status=1;
    }
    if(this->health<=100 && status==1){
        this->wallNutThirdMov->start();
        this->setMovie(wallNutThirdMov);
        delete wallNutSecondMov;
        status=2;
    };

}

wallNut :: ~wallNut(){
    delete wallNutThirdMov;
}

tallWallNut:: tallWallNut(QWidget * parent) : yPlant(parent){
    canbeJumpid=false;
    this->setMovie(wallNutFirstMov);
    this->wallNutFirstMov->start();
    this->show();
    this->health=800;
}
void  tallWallNut:: act(){
    if(status==0 && health<=400){
        status=1;
          wallNutSecondMov->start();
        this->setMovie(wallNutSecondMov);
          delete wallNutFirstMov;
    }
}
tallWallNut::~tallWallNut(){
       delete wallNutSecondMov;
}

void cherryBomb::die(){

    this->alive=false;
    yZombie * z;
    QRect r((column-2)*scene->cell_x,(row-2)*scene->cell_y,scene->cell_x*3,scene->cell_y*3);
    foreach(z,this->scene->zombies){
        QPair<int,int> p=this->scene->getPos(z->pos());
        int x=p.first;int y=p.second;
        if(x>=column-1 && x<=column+1 && y<=row+1 && y>=row-1)
        {
            z->alive=false;
           zombieBoomDie * die=new zombieBoomDie(scene);
            die->move(z->pos());
            die->show();
            die->raise();
           // qDebug()<<die->pos();
           scene->movies.append(die);
        }
    }
}

cherryBomb :: cherryBomb(QWidget * parent) : yPlant(parent){
    this->health=100;
    this->setMovie(mov);
    mov->start();
    this->show();
    //connect(mov,SIGNAL(finished()),this,SLOT(die()));
}

cherryBomb :: ~cherryBomb()
{
    delete mov;
}

void cherryBomb:: act(){
    qDebug()<<mov->currentFrameNumber();
    if(mov->currentFrameNumber()==6)
        status++;
    if(status!=0 && mov->currentFrameNumber()==0)
        die();

}

squash:: squash(QWidget * parent) : yPlant(parent){
    this->health=100;
    this->setMovie(first);
    first->start();
    this->show();
}
void  squash:: act(){
    yZombie * z;
    foreach(z,scene->zombies){
        QPair<int,int> p=scene->getPos(z->pos());
        qDebug()<<p<<row<<"  "<<column;
        if(p.second==row-1 && p.first<=column && p.first>=column-2){
            if(status==0){
                status=1;
                this->setMovie(second);
                this->setGeometry(z->x()+30,this->y()-150,100,226);
                second->start();

                return ;
            }
            else {
                if(this->second->currentFrameNumber()!=3){
                    return ;
                }
                if(this->second->currentFrameNumber()==3){
                    z->alive=false;
                    this->alive=false;
                }
            }
        }
    }
    if(status==1)
        qDebug()<<second->currentFrameNumber();
}
squash :: ~squash(){
    delete second;
}

garlic ::garlic(QWidget * parent):yPlant(parent){

}

garlic:: ~garlic(){

}

void garlic:: act(){

}
void garlic::getDamage(int x, yZombie *zombie){

}








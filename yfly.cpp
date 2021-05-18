#include "yfly.h"
#include<QDebug>
yFly::yFly(QWidget * parent)  :yObject(parent)
{
   this->scene=(yScene*) parent;
}

pea::pea(QWidget * parent,int row,int type)  :yFly(parent){
    QSound::play(":/sounds/Pea.wav");
    this->row=row;
    this->strength=20;
    this->speed=10;
    if(type==1) {
        this->peafly=new QMovie(":/flys/PeaIce.gif");
        status=1;
        //qDebug()<<"icepea";
    }
    this->setMovie(this->peafly);
   // qDebug()<<peafly->isValid();
    peafly->start();
    this->show();
    this->raise();
}

pea:: ~pea(){
    delete this->peafly;
}

void pea::act(){
    yPlant * p;
    foreach(p,scene->plants){
        if(p->plantType==10 && row==p->row && p->x()-x()>0 && p->x()-this->x()<=8){
            if(status==0){
                status=2;
                peafly=new QMovie(":/flys/PeaFire.gif");
                peafly->start();
                this->setMovie(peafly);
            }
            else if(status==1){
                status=0;
                peafly=new QMovie(":/flys/Pea.gif");
                peafly->start();
                this->setMovie(peafly);
            }
        }
    }
    yZombie * zombie;

    foreach(zombie,this->scene->zombies){
        if(abs(this->x()-zombie->x()-zombie->xoffset)<=5 && this->row==zombie->row && zombie->health>=0){
           if(status==2){
             yZombie * z;
             foreach(z,scene->zombies)
             {if(z->row==zombie->row && z->getColmun()==zombie->getColmun())

            z->getDamage(this->strength*2);}
            QSound::play(":/sounds/Fire.wav");
            fire *  f=new fire(this->scene,pos());
            scene->movies.append(f);
            if(zombie->iced){
                zombie->iced=false;
                zombie->iceCounter=zombie->iceTimeMax;
            }
           }
           else{
            QSound::play(":/sounds/PeaHit.wav");
            if(status==1 && zombie->canBeiced) {zombie->iced=true;
                zombie->iceCounter=0;
            }           
        }   this->alive=false;
           return ;
        }
    }

    this->move(this->x()+speed,this->y());
}

sunFly :: sunFly(QWidget * parent,bool fromsky) : yFly(parent){
    raise();
    this->setMovie(movie);
     xpos=this->scene->rect.left()+81*(rand()%9);
   ypos=this->scene->rect.top()+100*(rand()%5);
   this->movie->start();
   this->fromsky=fromsky;
   if(fromsky)
   {this->setGeometry(xpos,0,79,79);
   this->show();}
   this->raise();
   //qDebug()<<"created sun";
}

void sunFly:: act(){
    if(this->y()<ypos && fromsky)
    {this->move(this->x(),this->y()+1);
        return ;}
    if(counter==timemax)
        this->alive=false;
    counter++;
}

void  sunFly:: mousePressEvent(QMouseEvent* event){
    QSound::play(":/sounds/Sun.wav");
    this->alive=false;
    this->scene->sun+=25;
}

sunFly :: ~sunFly(){
    delete  this->movie;
}

//icePea :: icePea(QWidget * parent,int row): pea(parent,row){
//    this->setMovie(peafly);

//}


basketBall::   basketBall(QWidget * parent,QPoint p,QPoint p2) :yFly(parent){
    this->setMovie(mov);
    this->move(p2.x(),p.y());
    mov->start();
    this->show();
   this->p=p;
    speed=10;
    t=(p2.x()-p.x())/speed;
     yspeed=100 /((p2.x()-p.x())/speed);
     qDebug()<<t<<x()<<p<<yspeed;
}
basketBall:: ~basketBall(){
    delete mov;
}
 void  basketBall::  act(){
    // qDebug()<<y();
    if(this->x()-p.x()<=3){
        yPlant * plant;
        foreach(plant,scene->plants){
            if(this->x()-plant->x()<=10 && row==plant->row){

                {   if(plant->protectedPlant!=nullptr) plant->protectedPlant->getDamage(50);
                    else plant->getDamage(50);
                }
                this->alive=false;
                return ;
            }
        }
              this->alive=false;

    }
    timecounter++;
    if(timecounter>=t/2-1)
        this->move(x()-speed,y()+yspeed);
    else  this->move(x()-speed,y()-yspeed);
}



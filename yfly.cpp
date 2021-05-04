#include "yfly.h"

yFly::yFly(QWidget * parent)  :yObject(parent)
{
   this->scene=(yScene*) parent;
}

pea::pea(QWidget * parent,int row,int type)  :yFly(parent){

    this->row=row;
    this->strength=20;
    this->speed=10;
    if(type==1) {
        this->peafly=new QMovie(":/flys/PeaIce.gif");
        ice=true;
        qDebug()<<"icepea";
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
    yZombie * zombie;
    foreach(zombie,this->scene->zombies){
        if(abs(this->x()-zombie->x())<=5 && this->row==zombie->row){
            zombie->getDamage(this->strength);
            this->alive=false;
            if(ice) {zombie->iced=true;
                zombie->iceCounter=0;
            }
        }
    }

    this->move(this->x()+speed,this->y());
}

sunFly :: sunFly(QWidget * parent,bool fromsky) : yFly(parent){
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
    this->alive=false;
    this->scene->sun+=25;
}

sunFly :: ~sunFly(){
    delete  this->movie;
}

//icePea :: icePea(QWidget * parent,int row): pea(parent,row){
//    this->setMovie(peafly);

//}

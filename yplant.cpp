#include <iostream>
#include <vector>
#include "yplant.h"
#include<QDebug>
yPlant ::yPlant(QWidget *parent) :yObject(parent){

}

void yPlant::  act(){

}

void yPlant:: getDamage(int x,yZombie * zombie){
    this->health-=x;
    if(this->health<=0)
        this->alive=false;
}


void yPlant:: getDamage(int x){
    this->health-=x;
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
        if(z->row==row && z->getColmun()>column-2)
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
        if(z->row==row &&  z->getColmun()>column-2)
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
    this->health=300;
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
    this->health=300;
    this->strength=15;
    this->timecounter=45;

}

void repeater::act() {
    this->raise();
    yZombie * z;
    foreach(z,this->scene->zombies){
        if(z->row==row && z->getColmun()>column-2)
        {
            if(timecounter==45 || timecounter==50){
                if(timecounter==50)
                    timecounter=0;
                else timecounter++;
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
    this->health=4000;
}

void wallNut :: act(){
    if(this->health<=2000 && health>=100 && status==0){
        wallNutSecondMov->start();
        this->setMovie(wallNutSecondMov);
        delete this->wallNutFirstMov;
        status=1;
    }
    if(this->health<=1000 && status==1){
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
    this->health=6000;
}
void  tallWallNut:: act(){
    if(status==0 && health<=3000){
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


        int x=z->getColmun();int y=z->row;
        qDebug()<<x<<" "<<y<<column<<"  "<<row;
        if(x>=column-1 && x<=column+1 && y<=row+1 && y>=row-1 )
        {
            z->alive=false;
           zombieBoomDie * die=new zombieBoomDie(scene);
           boomMovie * boom=new boomMovie(scene,pos());
           this->scene->movies.append(boom);
            //die->move(z->getRealPos());
           die->move(z->pos());
            die->show();
            die->raise();
           // qDebug()<<die->pos();
           scene->movies.append(die);
        }
         QSound::play(":/sounds/Boom.wav");
    }
}

cherryBomb :: cherryBomb(QWidget * parent) : yPlant(parent){
    this->health=300;
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
    this->health=500;
    this->setMovie(first);
    first->start();
    this->show();
}
void  squash:: act(){
    yZombie * z;
    foreach(z,scene->zombies){
        QPair<int,int> p=scene->getPos(QPoint(z->x()+z->xoffset,z->y()+z->yoffset));
        qDebug()<<p<<row<<"  "<<column<<"  "<<z->pos();
        if(z->row==row && p.first<=column+1 && p.first>=column-1 ){
            if(status==0){
                QMediaPlayer * s=new QMediaPlayer();
                s->setMedia(QUrl("qrc:/sounds/squash.mp3"));
                s->setVolume(50);
                s->play();
                status=1;
                this->setMovie(second);
                this->setGeometry(z->x()+30+z->xoffset/2,this->y()-150,100,226);
                second->start();

                return ;
            }
            else {
                if(this->second->currentFrameNumber()!=3){
                    return ;
                }
                if(this->second->currentFrameNumber()==3){
                    z->getDamage(z->health);
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
    this->health=600;
    this->firstHealth=400;
    this->secondHealth=200;
    first->start();
    this->setMovie(first);
    this->show();
}

garlic:: ~garlic(){
    delete first;
    delete second;
    delete third;
}

void garlic:: act(){

}
void garlic::getDamage(int x, yZombie *zombie){
    this->health-=x;
    if(health<=firstHealth && status==0){
        second->start();
        this->setMovie(second);
        status=1;
    }
    if(health<=secondHealth && status==1){
        third->start();
        this->setMovie(third);
        status=2;
    }
    qDebug()<<"garlic";
    if(zombie->row==1){
        zombie->row=2;
        zombie->garlicStatus=1;
    }
    else if(zombie->row==5){
        zombie->row=4;
        zombie->garlicStatus=-1;
    }
    else {
        int x=rand()%3;
        x=x==1?1:-1;
        zombie->row+=x;
        zombie->garlicStatus=x;
    }
}

pumpkinHead::pumpkinHead(QWidget * parent,yPlant * p) : yPlant(parent){
    plant=p;
    if(plant!=nullptr)
    plant->protectedPlant=this;
    this->health=4000;
    this->status=0;
    this->first=new QMovie(":/plants/pumkin1.gif");
    this->second=new QMovie(":/plants/pumkin2.gif");
    third=new QMovie(":/plants/pumkin3.gif");
    this->setMovie(first);
    first->start();
    this->show();

}
pumpkinHead::~pumpkinHead(){
    if(plant!=nullptr)
    plant->protectedPlant=nullptr;
    if(first!=nullptr) delete first;
    if(second!=nullptr) delete second;
    if(third!=nullptr) delete third;
}

void pumpkinHead::act(){
    if(status==0 && health<=2677){
        this->status=1;
        second->start();
        this->setMovie(second);
      //  delete first;

    }
    else if(status==1 && health<=1333){
        this->status=2;
        third->start();
        this->setMovie(third);
        //delete second;
    }
}

fireTree::fireTree(QWidget * parent) :yPlant(parent) {
    health=500;
    plantType=10;
    mov=new QMovie(":/plants/FireTree.gif");
    mov->start();
    setMovie(mov);
    show();
}

fireTree:: ~fireTree(){
    delete mov;
}

eatFlower :: eatFlower(QWidget * parent):yPlant(parent){
    yoffset=-30;
    health=500;
    m1->start();
   // m2->start();
    m3->start();
    setMovie(m1);
    show();
}

void eatFlower::act(){
    if(status==2){
        timecounter++;
        if(timecounter==timemax){
            timecounter=0;
            status=0;
            setMovie(m1);
        }
        return ;
    }
    if(status==1){
        timecounter++;
        if(m2->currentFrameNumber()==m2->frameCount()-1)
        {setMovie(m3);
        status=2;}
        return;
    }
    yZombie * z;
    foreach(z,scene->zombies){
        if(z->row==row && ( z->x()+z->xoffset-x()<50 || z->getColmun()==this->column+1)){
            z->alive=false;
            this->setMovie(m2);
            m2->start();
            QSound::play(":/sounds/Eat.wav");
            status=1;
            return;
        }
    }

}







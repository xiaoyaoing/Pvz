#include "yscene.h"

yScene::yScene(QWidget *parent) :QLabel(parent){

}

void yScene :: createPlant(){

}

void yScene:: createZombie(){
    if(timecounter==500)
    {
        yCommonZombie * z=new yCommonZombie(this,rand()%5);

        int a=(rand()%5);
        z->row=a+1;
        qDebug()<<z->row;
        z->move(1200,10+a*100);
        z->show();
        this->zombies.append(z);
       // qDebug()<<z->y()<<"  ";
        timecounter=0;
    }
    else timecounter++;

}

bool yScene:: hasEnemy(int row){
    return this->rowHasEmeny[row];
}

void yScene::dealDealth(){
    for(int i=0;i<this->plants.size();i++)
        if(!this->plants.at(i)->alive){
            yPlant * p=plants.at(i);
            qDebug()<<"the plant has died";
            plants.remove(i);
            delete  p;
        }
    //qDebug()<<plants.size();
    for(int i=0;i<this->zombies.size();i++)
        if(   !this->zombies.at(i)->alive){
             qDebug()<<"the zombie has died";
            delete zombies.at(i);
             score+=50;
             zombies.remove(i);
        }
    for(int i=0;i<this->flys.size();i++)
        if(!this->flys.at(i)->alive){
             qDebug()<<"the fly has died";
            delete  flys.at(i);
            flys.remove(i);
        }
    for(int i=0;i<this->movies.size();i++)
        if(!this->movies.at(i)->alive){
            delete movies.at(i);
            movies.remove(i);
        }

}

void   yScene::  mouseMoveEvent (QMouseEvent* event){
    if(curCard!=nullptr)
    {       //qDebug()<<event->pos();
        curCard->move(event->pos());
    }
}
void   yScene::  mousePressEvent(QMouseEvent* event){
    qDebug()<<event->pos();
    qDebug()<<(curCard==nullptr);
    if(curCard!=nullptr)
    {   curCard->setPos();
        curCard=nullptr;

    }

}

void yScene:: createSun(){
    if(suncounter==500)
    {
        suncounter=0;

        this->flys.append( new sunFly(this,true));
        return ;
    }
    suncounter++;


}




void yScene:: help(QPoint p,int buttontype){
   //qDebug()<<curCard->pos()<<p;
    if(curCard->rect().contains(p)){
            curCard->setPos();
            curCard=nullptr;
            qDebug()<<"not in";
            return ;}
    if(buttontype==0){
        if(this->curCard!=nullptr){
            curCard->setPos();
            curCard=nullptr;
        }
        qDebug()<<"right";
          return ;
    }

    if(!rect.contains(p))
    {
        qDebug()<<"not in too";
        curCard->setPos();
        curCard=nullptr;
        return ;
    }
    qDebug()<<"hello";
    QPair<int,int> pair=getPos(p);
    int x=pair.first;
    int y=pair.second;
    qDebug()<<x<<y;
    yPlant * plant;
    foreach(plant,plants)
    {
        if(plant->row ==x && plant->column==y && curCard->type>=0)
        {
            curCard->setPos();
            curCard=nullptr;
            return ;
        }
    }
    putCurPlant(x,y);
}

void yScene :: putCurPlant(int x,int y){
    if(curCard->type==-1){

    }
    qDebug()<<"put plant"<<curCard->type;
    yPlant  * p=nullptr;;
    if(curCard->type==1){
        p=new peaShooter(this);

    }
    else if(curCard->type==0){
        p=new sunFlower(this);
    }
    else if(curCard->type==2)
        p=new icePeaShooter(this);
    else if(curCard->type==3)
        p=new repeater(this);
    else if(curCard->type==4)
        p=new cherryBomb(this);
    else if(curCard->type==5)
        p=new wallNut(this);
    else if(curCard->type==6)
        p=new tallWallNut(this);
    else if(curCard->type==7)
        p=new squash(this);
    if(p->canbeJumpid)
    p->move(rect.left()+cell_x*(x-1),rect.top()+cell_y*(y-1));
    else p->move(rect.left()+cell_x*(x-1),rect.top()+cell_y*(y-1)-30);
   //p->setGeometry(rect.left()+cell_x*(x-1),rect.top()+cell_y*(y-1),81,100);
    p->column=x;
    p->row=y;
    plants.append(p);
    sun-=curCard->sunCost;
    curCard->counter=curCard->time;
    curCard->setPos();
    this->curCard=nullptr;
}


QPair <int,int>  yScene::getPos(QPoint p){
    return QPair<int,int>((p.x()-rect.left())/cell_x+1,(p.y()-rect.top())/cell_y+1);
}

void dayScene::initCards(){
   //  qDebug()<<"s";
     this->movies.append(new sunNum(this));
    this->movies.append(new scoreBoard(this));


    for(int i=0;i<=7;i++)
            this->cards.append(new yPlantCard(this,i));
}



dayScene::dayScene(QWidget *parent) : yScene(parent) {
    this->setGeometry(0,0,1400,600);
    this->mov=new QMovie(":/background/background1.jpg");
   // qDebug()<<this->mov->isValid();
   this->setMovie(mov);
   this->mov->start();
    this->timer=new QTimer(this);
    this->timer->start(20);

    //qDebug()<<"创建了一个dayscene"<<"  ";
    initCards();
    connect(timer,SIGNAL(timeout()),this,SLOT(timeOut()));
    this->show();




    rect=QRect(250,80,729,500);
    this->cell_x=81;
    cell_y=100;
    sun=300;
}


void dayScene:: timeOut(){

    this->act();
//    if(this->curCard!=nullptr)
//        curCard->move(200,47);
    createSun();
   this->createZombie();
    this->dealDealth();
}




void dayScene::act() {

    yPlant * p;
    yZombie * z;
    yFly * f;
    yPlantCard * c;
    yMovie * m;
    foreach(p ,this->plants)
        p->act();
    foreach(z,this->zombies)
        z->act();
    foreach(f,this->flys)
        f->act();
    foreach (c,cards) {
        c->act();
    }
    foreach(m,movies)
        m->act();
//    if(this->plants.size()<5)
//   { peaShooter * a=new peaShooter(this);
//    a->row=this->plants.size()+1;
//    a->setGeometry(300,a->row*100,71,71);
//    plants.append(a);
//    }
 //   qDebug()<<a->x()<<"  ";
}

startScene ::startScene(QWidget * parent) : yScene(parent) {


    this->setGeometry(0,0,800,600);
    this->mov=new QMovie(":/interfaces/start.jpg");
    this->setMovie(mov);
    this->mov->start();

//    QMovie * logo =new QMovie(":/interfaces/mainlogo.png");
//    this->startbtn->setMovie(logo);
//    qDebug()<<logo->isValid();
//    this->startbtn->setGeometry(400,200,200,100);
//    logo->start();
}

void startScene::act() {
    //  开始界面不做任何事情
}

void startScene:: mousePressEvent(QMouseEvent *ev){
    if(QRect(0,0,900,600).contains(ev->pos()))
        emit toLight();

}



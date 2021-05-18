#include "yplantcard.h"
#include<QDebug>
yPlantCard::yPlantCard(QWidget * parent ,int type) : QLabel(parent)
{
    this->scene=(yScene*)parent;
    this->setMouseTracking(true);
    this->setFixedSize(100,60);
   // front=new QLabel(this);  
    costText=new QLabel(this);
    costText->setGeometry(0,50,100,10);
    costText->setAlignment(Qt::AlignCenter);
    this->raise();
    counter=0;
    this->type=type;


    switch (type) {
    case -1:{
        movie=new QMovie(":/cards/Shovel.png");
        time=1;
        sunCost=0;
        break;
    }
    case 0 :{
        time=50*7.5;
        sunCost=50;
        movie=new QMovie(":/cards/card_Sunflower.png");
          backMovie=new QMovie(":/cards/sunFlower.png");

        break;
    }
    case 1:{
        time=50*7.5;
        sunCost=100;
         movie=new QMovie(":/cards/card_PeaShooter.png");
         backMovie=new QMovie(":/cards/RepeateBlack.png");

         break;
    }
    case 2:{
        time=50*7.5;
        sunCost=175;
            movie=new QMovie(":/cards/card_IcePeaShooter.png");
             backMovie=new QMovie(":/cards/IcePeashooterBlack.png");
         break;
    }
    case 3:{
        time=50*7.5;
        sunCost=200;
         movie=new QMovie(":/cards/card_Repeater.png");
          backMovie=new QMovie(":/cards/repeaterBlack.png");
         break;
    }
    case 4:{
        time=50*15;
        sunCost=150;
         movie=new QMovie(":/cards/card_CherryBomb.png");
          backMovie=new QMovie(":/cards/cheeryBombBlack.png");
         break;
    }
    case 5:{
        time=50*7.5;
        sunCost=50;
         movie=new QMovie(":/cards/wallnut.png");
          backMovie=new QMovie(":/cards/wallNutBlack.png");
         break;
    }
    case 6:{
        time=50*22.5;
        sunCost=125;
        movie=new QMovie(":/cards/tallWallNutCard.png");
         backMovie=new QMovie(":/cards/tallWallutBlack.png");
        break;
    }
    case 7:{
    time=50*7.5;
    sunCost=50;
    movie=new QMovie(":/cards/card_squash.png");
     backMovie=new QMovie(":/cards/squash.png");
    break;
    }
    case 8:{
        time=400;
        sunCost=50;
        movie=new QMovie(":/cards/garlcCard.png");
         backMovie=new QMovie(":/cards/garlicBlack.png");
        break;
    }
    case 9:{
        time=1500;
        sunCost=125;
        movie=new  QMovie(":/cards/card_PumpkinHead.png");
         backMovie=new QMovie(":/cards/pumkinHeadBlack.png");
        break;
    }
    case 10:{
        time=7.5*50;
        sunCost=175;
        movie=new  QMovie(":/cards/card_FireTree.png");
         backMovie=new QMovie(":/cards/FireTreeBlack.png");
        break;
    }

   case 11:{
        time=7.5*50;
        sunCost=150;
        movie=new  QMovie(":/cards/Card_eatFlower.png");
         backMovie=new QMovie(":/cards/eatFlowerBlack.png");
        break;

    }}
    if(backMovie!=nullptr)
    backMovie->start();
   // back->setMovie(backMovie);
    movie->setBackgroundColor(Qt::black);
    movie->start();
    //this->setMovie(movie);
    //back->setMovie(movie);
  //  back->show();
    setPos();
    setMovie(backMovie);
    costText->setText(QString::number(sunCost));
    this->show();

}

yPlantCard::yPlantCard(QWidget * parent,int type,int index){
    this->index=index;
    yPlantCard(parent,type);
}
void yPlantCard:: act(){
    raise();
    /*f(type==7){
        //back->move(0,-60);
        return ;
    }*/
   // qDebug()<<backMovie;
    //back->raise();
    if(scene->sun<sunCost){
         if(backMovie!=nullptr)
             this->setMovie(backMovie);
            return ;
        }
    if(counter==0) {
        this->setMovie(movie);
        return ;
    }
    if(counter>0)
       {counter--;
        if(backMovie!=nullptr)
        this->setMovie(backMovie);
    }
  //  front->setGeometry(0,0,100,50*counter/time);
}

void yPlantCard:: setPos(){
    if(scene->sceneType==1){
           this->setGeometry(10+100*(type%4),186+60*(type/4),100,60);
        return ;
    }
    if(type<0){
        this->setGeometry(0,92+(-type)*1,100,60);
        return ;
    }
    qDebug()<<index;
    this->setGeometry(50+100*(index+1),10,100,60);
}

void yPlantCard::mousePressEvent(QMouseEvent* event){
    if(scene->sceneType==1){

        if(status==0 && ((chooseScene *)(scene))->getNum()==8){
            QSound::play(":/sounds/NotEnoughSun.wav");
            return ;
        }
        QSound::play(":/sounds/Sun.wav");
        status=1-status;
        setMovie(status==0?backMovie:movie);
        return ;
    }
   if(this->scene->curCard!=nullptr){
       qDebug()<<"a";

       this->scene->help(event->pos()+QPoint(this->x(),this->y()),event->button()==Qt::LeftButton?1:0);
       return ;
   }
   if(counter>0 || sunCost>scene->sun)
   {    QSound::play(":/sounds/NotEnoughSun.wav");
       return ;}
  // qDebug()<<"reached the card";
   scene->curCard=this;
   
}





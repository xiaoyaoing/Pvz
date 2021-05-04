#include "yplantcard.h"

yPlantCard::yPlantCard(QWidget * parent ,int type) : QLabel(parent)
{
    this->scene=(yScene*)parent;
    this->setMouseTracking(true);
    front=new QLabel(this);
    back=new QLabel(this);
    costText=new QLabel(this);
    costText->setGeometry(0,50,100,10);
    costText->setAlignment(Qt::AlignCenter);
    this->raise();
    counter=0;
    this->type=type;
    switch (type) {
    case 0 :{
        time=100;
        sunCost=50;
        movie=new QMovie(":/cards/card_Sunflower.png");
        break;
    }
    case 1:{
        time=100;
        sunCost=100;
         movie=new QMovie(":/cards/card_PeaShooter.png");
         break;
    }
    case 2:{
        time=300;
        sunCost=175;
         movie=new QMovie(":/cards/card_IcePeaShooter.png");
         break;
    }
    case 3:{
        time=300;
        sunCost=200;
         movie=new QMovie(":/cards/card_Repeater.png");
         break;
    }
    case 4:{
        time=300;
        sunCost=150;
         movie=new QMovie(":/cards/card_CherryBomb.png");
         break;
    }
    case 5:{
        time=200;
        sunCost=50;
         movie=new QMovie(":/cards/card_WallNut.png");
         break;
    }
    case 6:{
        time=400;
        sunCost=125;
        movie=new QMovie(":/cards/tallWallNutCard.png");
        break;
    }
    case 7:{
    time=300;
    sunCost=50;
    movie=new QMovie(":/cards/card_squash.png");
    }
//    case 6:{
//        time=300;
//        sunCost=175;
//         movie=new QMovie(":/cards/card_IcePeaShooter.png");
//         break;
//    }

    }
    movie->setBackgroundColor(Qt::black);
    movie->start();
    this->setMovie(movie);
    setPos();
    costText->setText(QString::number(sunCost));
    this->show();
}


void yPlantCard:: act(){
    if(counter>0)
       counter--;
    if(scene->sun<sunCost){
        front->setGeometry(0,0,100,50);
        return ;
    }
    front->setGeometry(0,0,100,50*counter/time);
}

void yPlantCard:: setPos(){
    this->setGeometry(50+100*(type+1),10,100,60);
}

void yPlantCard::mousePressEvent(QMouseEvent* event){
   if(this->scene->curCard!=nullptr){
       qDebug()<<"a";

       this->scene->help(event->pos()+QPoint(this->x(),this->y()),event->button()==Qt::LeftButton?1:0);
       return ;
   }
   if(counter>0 || sunCost>scene->sun)
       return ;
  // qDebug()<<"reached the card";
   scene->curCard=this;
   
}



//peaShooterCard::peaShooterCard(QWidget * parent)  :yPlantCard(parent)
//{
//    time=100;
//    counter=0;
//    type=1;
//    sunCost=100;
//    movie=new QMovie(":/cards/card_PeaShooter.png");
////    front->setMovie(movie);
////    back->setMovie(movie);
//    movie->start();
//    this->setMovie(movie);
//    costText->setText("100");

//    setPos();
//    this->show();
//   // qDebug()<<"created";

//}

//sunFlowerCard :: sunFlowerCard(QWidget * parent) : yPlantCard(parent){
//    time=100;
//    counter=0;
//    type=0;
//    sunCost=50;
//    movie=new QMovie(":/cards/card_Sunflower.png");
////    front->setMovie(movie);
////    back->setMovie(movie);
//    movie->start();
//    this->setMovie(movie);
//    costText->setText("50");
//    setPos();
//    this->show();
//   // qDebug()<<"created";
//}

//icePeaShooterCard :: icePeaShooterCard(QWidget * parent): yPlantCard(parent){
//    time=300;
//}

//repeaterCard :: repeaterCard(QWidget * parent) : yPlantCard(parent){
//    time=200;
//    counter=0;
//    type=3;
//    suncost=200;
//    movie=new Qmo
//}

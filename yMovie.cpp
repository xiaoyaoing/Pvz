#include "yMovie.h"



yMovie :: yMovie(QWidget * parent) : yObject(parent)

{
    //do nothing
}


//void yZombieDie:: goDie(){
//    this->alive=false;
//}
void yZombieDie :: act(){

}

yZombieDie :: yZombieDie(QWidget * parent) : yMovie(parent){
    this->setMovie(die);
    this->alive=true;
    die->start();
    this->show();
    connect(this->die,SIGNAL(frameChanged(1)),this,SLOT(goDie()));
}


yZombieDie :: ~yZombieDie(){
    delete this->die;
}


sunNum::  sunNum(QWidget * parent) :yMovie(parent){
       this->setGeometry(0,0,123,34);
       this->suntext->setGeometry(50,10,30,20);
    sunBack->start();
    this->raise();
    this->setMovie(sunBack);
    this->show();

    qDebug()<<sunBack->isValid();
    }

    sunNum:: ~sunNum(){
        delete suntext;
        delete sunBack;
    }
   void  sunNum:: act(){
        this->suntext->setText(QString::number(this->scene->sun));
    }

   scoreBoard:: scoreBoard(QWidget * parent) :yMovie(parent){
       this->setGeometry(0,34,123,34);
       this->scoretext->setGeometry(50,10,30,20);
    back->start();
    this->raise();
    this->setMovie(back);
    this->show();

   }
 scoreBoard :: ~scoreBoard(){
       delete back;
       delete scoretext;
   }

  void scoreBoard::act(){
       this->scoretext->setText(QString::number(this->scene->score));
   }

  void zombieBoomDie::   act(){
     // qDebug()<<mov->currentFrameNumber()<<mov->state();
      if(this->mov->currentFrameNumber()==19)
         alive=false;
//      if(status!=0 && mov->currentFrameNumber()==0)
//          alive=false;
  }
  zombieBoomDie:: zombieBoomDie(QWidget * parent) :yMovie(parent){
    this->setMovie(mov);
      qDebug()<<mov->isValid();
      this->mov->start();
      this->raise();
      this->show();
  }
  zombieBoomDie:: ~zombieBoomDie(){
    delete mov;
  }

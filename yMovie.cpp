#include "yMovie.h"
#include<QDebug>
#include<QMessageBox>

yMovie :: yMovie(QWidget * parent) : yObject(parent)

{
    //do nothing
}


//void yZombieDie:: goDie(){
//    this->alive=false;
//}
void yZombieDie :: act(){
    if(die->currentFrameNumber()==die->frameCount()-1)
        alive=false;
}

yZombieDie :: yZombieDie(QWidget * parent,int type,QPoint pos) : yMovie(parent){
    if(type<5 || type==8){
        die=new QMovie(":/Zombies/ZombieDie.gif");
    }
    else if(type==5){
         die=new QMovie(":/Zombies/PoleZombieDie.gif");
    }
    else if(type==6){
        die=new QMovie(":/Zombies/NewsDie.gif");
    }
    else if(type==7)
        die=new QMovie(":/Zombies/clownDie.gif");
    else if(type==25)
        die=new QMovie(":/Zombies/PoleZombieHead.gif");
    else if(type==26)

        die=new QMovie(":/Zombies/NewsHead.gif");

    else if((20<=type && type<=25) || type==27 || type==28)
{   die=new QMovie(":/Zombies/ZombieHead.gif");
    }
    this->alive=true;
    this->setMovie(die);
    die->start();
    this->move(pos);
    this->show();
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


  stopBoard ::stopBoard(QWidget * parent):yMovie(parent){
      this->setGeometry(0,68,123,24);
      this->setMovie(back);
      back->start();
      stopText->setGeometry(50,0,50,20);
      stopText->setText("暂停");
      this->show();
    connect(stopText,&QPushButton::clicked,this,&stopBoard::stop);
  }
  void stopBoard :: stop(){
      this->scene->isStop=(1-status);
      stopText->setText(status==0?"继续":"暂停");
       status=1-status;
  }


  void stopBoard::act(){

  }
 void
 boomMovie:: act(){
     if(++cnt==50)
         alive=false;
 }


 boomMovie :: boomMovie (QWidget * parent,QPoint pos):yMovie(parent){
     this->setMovie(mov);
     mov->start();
     move(QPoint(pos.x()-10,pos.y()+80));
     show();
 }

 boomMovie:: ~boomMovie(){
     delete mov;
 }

 lossMovie :: lossMovie(QWidget * parent) : yMovie(parent){
    // this->move()
     mov->start();
     this->setMovie(mov);
     this->move(200,50);
    show();
 }

 void lossMovie:: act(){
    cnt++;
    if(cnt==50){
        QMessageBox::StandardButton rb = QMessageBox::question(NULL, "Loss", "Do you want to try again?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb==QMessageBox::Yes){
            MainDialog::get()->toChoose();
        }
        else MainDialog::get()->close();

    }

 }

lossMovie :: ~lossMovie(){
delete mov;
 }

fire::fire(QWidget * parent,QPoint pos):yMovie(parent){
    mov->start();
    setMovie(mov);
    move(pos);
    show();
}

void fire::act(){
    t--;
    if(t==0)
        alive=false;
}







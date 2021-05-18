#include "maindialog.h"
#include<QDebug>
#include<vector>
MainDialog * MainDialog :: instance=nullptr;
MainDialog * MainDialog :: get(){
    if(instance==nullptr)
        instance=new MainDialog();
    return instance;
}
MainDialog::MainDialog(QWidget * parent) :QDialog(parent)
{
    setWindowIcon(QIcon(QStringLiteral(":/interfaces/mainlogo.png")));
    this->resize(800,600);
    this->curScene=new startScene(this);
    this->show();
    connect(this->curScene,SIGNAL(toLight()),this,SLOT(toChoose()));
}

void MainDialog:: toLight(){
    QList<yPlantCard *> p =curScene->cards;
  std::  vector<int> a(1);
    a[0]=((chooseScene *)(curScene))->dayOrDark;
    for(int i=0;i<p.size();i++){
        if(p.at(i)->status==1)
            a.push_back(p.at(i)->type);
    }
    this->resize(1200,600);
    curScene->timer->stop();
    for(int i=0;i<400;i++)
        int j=1;
     delete curScene;

    qDebug()<<"delete CurScene";
    this->curScene=new dayScene(this,a);
}

void MainDialog :: toChoose(){
    if(curScene->sceneType==2){
        curScene->timer->stop();

    }
    for(int i=0;i<400;i++)
        int j=1;
    if(curScene->player!=nullptr)
        curScene->player->stop();
  // delete  curScene;
   // delete curScene;
    qDebug()<<"delete CurScene";
    this->curScene=new chooseScene(this);
    qDebug()<<"chooseScene create";
   connect(this->curScene,SIGNAL(toLight()),this,SLOT(toLight()));
    qDebug()<<"connent";
}

void MainDialog:: toStart(){

}
void MainDialog:: toDark(){

}

#include "maindialog.h"

MainDialog::MainDialog(QWidget * parent) :QDialog(parent)
{
    setWindowIcon(QIcon(QStringLiteral(":/interfaces/mainlogo.png")));
    this->setFixedSize(800,600);
    this->curScene=new startScene(this);
    this->show();
    connect(this->curScene,SIGNAL(toLight()),this,SLOT(toLight()));
}

void MainDialog:: toLight(){
    this->setFixedSize(1400,600);
    delete this->curScene;
    qDebug()<<"sasa";
    this->curScene=new dayScene(this);
}

void MainDialog:: toStart(){

}
void MainDialog:: toDark(){

}

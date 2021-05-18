#include "yscene.h"
#include <unistd.h>
#include<QDebug>
#include<QMessageBox>

yZombie * getZombie(yScene * scene,int type){
    if(type<5){
        return new yCommonZombie(scene,type);
    }
    if(type==5) return new jumpZombie(scene);
    if(type==6) return new newspaperZombie(scene);
    if(type==7) return new clownZombie(scene);
    if(type==8) return new basketBallZombie(scene);
}
yScene::yScene(QWidget *parent) :QLabel(parent){

}

yScene:: ~yScene(){
    qDebug()<<"yscene delete";
    if(player!=nullptr){
        player->stop();
     delete  player;}
    if(playerList!=nullptr) {

        delete playerList;}
}

void yScene :: createPlant(){

}



void yScene:: createZombie(){
    if(timecounter==ZombieTimeMax){
        QMediaPlayer *  comingplayer=new QMediaPlayer();
                   comingplayer->setMedia(QUrl("qrc:/sounds/ZombieComing.MP3"));
                   comingplayer->setVolume(100);
                   qDebug()<<comingplayer->state();
                   comingplayer->play();
                    qDebug()<<comingplayer->state();

    }

    if(timecounter%ZombieTimeMax==0 && timecounter>0)
    {
        //yZombie  * z=new yCommonZombie(this,rand()%5);
        qDebug()<<"zombie";
        int a=(rand()%5);
          yZombie * z;
        if(ZombieNum<=4)
             z=getZombie(this,0);

    else      z=getZombie(this,rand()%9);
       // yZombie * z=getZombie(this,rand()%7);
        z->row=a+1;
        qDebug()<<z->row;
        qDebug()<<z->yoffset;
        z->move(1000,10+a*100-z->yoffset);
        z->show();
        this->zombies.append(z);
        ZombieNum++;
        if(ZombieNum%5==0 && ZombieTimeMax>5){
            ZombieTimeMax-=15;
        }
       // qDebug()<<z->y()<<"  ";

    }
    timecounter++;

}

bool yScene:: hasEnemy(int row){
    return this->rowHasEmeny[row];
}

void yScene::dealDealth(){
    qDebug()<<"remove death";
    for(int i=0;i<this->plants.size();i++)
        if(!this->plants.at(i)->alive){
            yPlant * p=plants.at(i);
            qDebug()<<"the plant has died";
            plants.removeAt(i);
            delete  p;
        }
    //qDebug()<<plants.size();
    for(int i=0;i<this->zombies.size();i++)
        if(   !this->zombies.at(i)->alive){
             qDebug()<<"the zombie has died";
            delete zombies.at(i);
             score+=50;
             zombies.removeAt(i);
        }
    for(int i=0;i<this->flys.size();i++)
        if(!this->flys.at(i)->alive){
             qDebug()<<"the fly has died";
            delete  flys.at(i);
            flys.removeAt(i);
        }
    for(int i=0;i<this->movies.size();i++)
        if(!this->movies.at(i)->alive){
            delete movies.at(i);
            movies.removeAt(i);
        }

}
void yScene:: stopOrCountintue(){

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
    {   help(event->pos(),event->button());
//        curCard->setPos();
//        curCard=nullptr;

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
            //qDebug()<<"not in";
            return ;}
    if(buttontype==0){
        if(this->curCard!=nullptr){
            curCard->setPos();
            curCard=nullptr;
        }
       // qDebug()<<"right";
          return ;
    }

    if(!rect.contains(p))
    {
        //qDebug()<<"not in too";
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
    if(curCard->type>=0)
    foreach(plant,plants)
    {
        if(plant->column ==x && plant->row==y && curCard->type>=0 && curCard->type!=9)
        {
            curCard->setPos();
            curCard=nullptr;
            qDebug()<<"已经有植物了"<<p<<x<<y;;
            return ;
        }
    }
    putCurPlant(x,y);
}

void yScene :: putCurPlant(int x,int y){
    if(curCard->type==-1){
        yPlant * p;
        foreach(p,plants){
            if(p->column==x && y==p->row )
                p->alive=false;
        }
        QSound::play(":/sounds/Place.wav");
        curCard->setPos();
        this->curCard=nullptr;
        return ;
    }
    bool hasSetPos=false;

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
    else if(curCard->type==8)
        p=new garlic(this);
    else if(curCard->type==9){
        p=nullptr;
        yPlant * plant;
        foreach(plant,plants){
            if(plant->row==y && plant->column==x){
                p=new pumpkinHead(this,plant);
                p->move(plant->x()-10,plant->y());
             //   plant->raise();
                hasSetPos=true;
                break;
            }
        }
        if(p==nullptr)
            p=new pumpkinHead(this,nullptr);
    }
    else if(curCard->type==10){
        p=new fireTree(this);
    }
    else if(curCard->type==11)
        p=new eatFlower(this);
    if(hasSetPos==false)
    {if(p->canbeJumpid)
    p->move(rect.left()+cell_x*(x-1)+16,rect.top()+cell_y*(y-1)+p->yoffset);
    else p->move(rect.left()+cell_x*(x-1)+16,rect.top()+cell_y*(y-1)-30);}
   //p->setGeometry(rect.left()+cell_x*(x-1),rect.top()+cell_y*(y-1),81,100);
    p->column=x;
    p->row=y;
    plants.append(p);
    sun-=curCard->sunCost;
    curCard->counter=curCard->time;
    QSound::play(":/sounds/Place.wav");
    curCard->setPos();
    this->curCard=nullptr;
}


QPair <int,int>  yScene::getPos(QPoint p){

    return QPair<int,int>((p.x()-rect.left())/cell_x+1,(p.y()-rect.top())/cell_y+1);
}

void dayScene::initCards(std::vector<int> & card){
   //  qDebug()<<"s";
     this->movies.append(new sunNum(this));
    this->movies.append(new scoreBoard(this));
    this->movies.append(new stopBoard(this));
    cards.append(new yPlantCard(this,-1));
    for(int i=1;i<card.size();i++)
    {       yPlantCard * c=new yPlantCard(this,card[i]);
            c->index=i-1;
            c->setPos();
            //qDebug()<<c->index;
            this->cards.append(c);}
}

void dayScene::initMedia(){
    playerList=new QMediaPlaylist;
    playerList->addMedia(QUrl("qrc:/sounds/backMusic.MP3"));
    playerList->addMedia(QUrl("qrc:/sounds/ZombieComing.MP3"));
    playerList->setCurrentIndex(0);
    playerList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
 player = new QMediaPlayer();
player->setPlaylist(playerList);
//    player->setMedia(QUrl("qrc:/sounds/backMusic.MP3"));
     player->setVolume(80);
       player->play();


}



dayScene::dayScene(QWidget *parent,std::vector<int> & card) : yScene(parent) {
    sceneType=2;
    this->setGeometry(0,0,1200,600);
    this->mov=new QMovie(card[0]==0?":/background/background1.jpg":":/background/darkBackground.jpg");
   // qDebug()<<this->mov->isValid();
   this->setMovie(mov);
   this->mov->start();

  initMedia();
    //qDebug()<<"创建了一个dayscene"<<"  ";
    initCards(card);
    this->timer=new QTimer(this);
    this->timer->start(20);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeOut()));
    this->show();


    rect=QRect(234,80,729,500);
    this->cell_x=81;
    cell_y=100;
    sun=150;
}

dayScene:: ~dayScene(){
    delete mov;
    disconnect(timer,SIGNAL(timeout()),this,SLOT(timeOut()));
    delete timer;
    qDebug()<<"dayScene"<<"delete";
    yObject * y;
    for(int i=0;i<movies.size();i++){
        delete movies.at(i);
    }
    for(int i=0;i<plants.size();i++){
        delete plants.at(i);
     }
        for(int i=0;i<zombies.size();i++){
            delete zombies.at(i);
         }
        for(int i=0;i<flys.size();i++){
                delete flys.at(i);
            }
}



void dayScene:: timeOut(){
    //qDebug()<<"timeout";
    if(MainDialog::get()->curScene!=this)
        return;
    if(isStop==1)
        return ;
     //qDebug()<<"act";
    isLoss();
//    if(this->curCard!=nullptr)
//        curCard->move(200,47);


    createSun();

   this->createZombie();
    this->dealDealth();
     this->act();
   //  qDebug()<<"complete";
}

void dayScene::isLoss(){
    if(isloss) return ;
    yZombie * z;
    foreach(z,zombies){
        if(z->x()+z->xoffset<=50){
            isloss=true;
            movies.append(new lossMovie(this));
        }
    }
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
    playerList=new QMediaPlaylist;
    playerList->addMedia(QUrl("qrc:/sounds/backMusic2.MP3"));
    playerList->setCurrentIndex(0);
    playerList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    player = new QMediaPlayer();
    player->setPlaylist(playerList);
    player->play();
    this->setGeometry(0,0,800,600);
    this->mov=new QMovie(":/interfaces/startBackground.png");
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
    //qDebug()<<ev->pos();
    if(QRect(360,550,80,20).contains(ev->pos()))
        emit toLight();

}

void chooseScene::initCards(){
    for(int i=0;i<=11;i++)
        cards.append(new yPlantCard(this,i));
}



chooseScene :: chooseScene(QWidget * parent) : yScene(parent){
    qDebug()<<"chooseScene";
    start=new QLabel(this);
    QMovie * m=new QMovie(":/interfaces/startButton.png");
    start->setMovie(m);
   start->move(206,440);
    m->start();
    start->show();
    Text=new QLabel(this);
   Text->setGeometry(143,102,300,100);
   Text->show();
   qDebug()<<"chooseScene";

   Text1=new QLabel(this);
   Text1->setGeometry(443,102,300,100);
   Text1->show();

   smallDark=new QLabel(this);
   QMovie * m1=new QMovie(":/background/Smalldark.png");
   m1->start();
   smallDark->setMovie(m1);
   smallDark->show();
   smallDark->setFixedSize(300,100);
   smallDark->move(450,202);

   smallDay=new QLabel(this);
   QMovie * m2=new QMovie(":/background/smallDay.png");
   m2->start();
   smallDay->setMovie(m2);
   smallDay->show();
   smallDay->setFixedSize(300,100);
   smallDay->move(450,302);
  // smallDark->move();



    sceneType=1;
    movie=new QMovie(":/interfaces/Title.jpg");
    movie->start();
    setMovie(movie);
        initCards();
    show();
    yPlantCard * c;
    foreach(c,cards)
        c->raise();
    this->timer=new QTimer(this);
    this->timer->start(20);
    qDebug()<<"chooseScene";
    connect(timer,SIGNAL(timeout()),this,SLOT(act()));
    qDebug()<<"chooseScene";
    playerList=new QMediaPlaylist;
    playerList->addMedia(QUrl("qrc:/sounds/music3.mp3"));
    playerList->setCurrentIndex(0);
    playerList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
 player = new QMediaPlayer();
player->setPlaylist(playerList);
     player->setVolume(40);
       player->play();

}

 void chooseScene:: act(){
    Text->setText("你还有"+QString::number(8-getNum())+"种植物可以选择");
    if(dayOrDark==-1)
    Text1->setText("请选择白天或者黑夜");
    else if(dayOrDark==0)
        Text1->setText("当前背景：白天");
    else Text1->setText("当前背景：黑夜");
}
 int chooseScene:: getNum(){
     int ans=0;
     for(int i=0;i<cards.size();i++)
        if(cards.at(i)->status==1)
            ans++;
     return ans;
 }

 void chooseScene::mousePressEvent(QMouseEvent* event){
     qDebug()<<event->pos();
     QPoint p=event->pos();
     int x=p.x();int y=p.y();
     qDebug()<<smallDark->rect()<<smallDark->rect().contains(p);
     if(x-smallDark->x()<smallDark->width() && y-smallDark->y()<smallDark->height()){
          QSound::play(":/sounds/Sun.wav");
         qDebug()<<smallDark;
         if(dayOrDark==1)
             dayOrDark=-1;
         else dayOrDark =1;
         return ;
     }
     if(x-smallDay->x()<smallDay->width() && y-smallDay->y()<smallDay->height()){
          QSound::play(":/sounds/Sun.wav");
         if(dayOrDark==0)
             dayOrDark=-1;
         else dayOrDark=0;
         return ;
     }
     if(x-start->x()<start->width() && y-start->y()<start->height()){
         if(getNum()!=8){
            QMessageBox::information(NULL, "hint", "Not enough plants!");
            return ;
         }
         if(dayOrDark==-1){
             QMessageBox::information(NULL, "hint", "Please choose a background");
             return ;
         }
         emit toLight();
     }

 }

 chooseScene:: ~chooseScene(){
     delete   Text;
     delete   Text1;
     delete   start;
     delete   smallDay;
     delete   smallDark;
     qDebug("chooseScene ～");
 }



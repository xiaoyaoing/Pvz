#ifndef YSCENE_H
#define YSCENE_H

#include<QMouseEvent>
#include <QLabel>
#include <QMovie>
#include <QTimer>
#include<QPair>
#include <QSound>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<vector>
#include "yobject.h"
#include "yplant.h"
#include "yzombie.h"
#include "yMovie.h"
#include "yfly.h"
#include "yplantcard.h"

class yPlant;
class yZombie;
class yFly;
class yMovie;
class yPlantCard;




class yScene: public QLabel{

        Q_OBJECT
    public:
        QMediaPlayer * player;
        int sceneType=0;
    int timecounter=0;
    QMovie * mov=nullptr;
    int ZombieNum=0;
    int ZombieTimeMax=500+15*4;
   QMediaPlaylist  * playerList=nullptr;
    QMediaPlayer * comingplayer=nullptr;
    QList<yPlant *> plants;
    QList<yZombie *> zombies;
    QList<yMovie *> movies;
    QList<yFly *> flys;
    QList<yPlantCard *> cards;
    int isStop=0;
    QTimer * timer;
    yPlantCard * curCard=nullptr;
    QRect  rect=QRect(0,0,0,0);
    QPair<int,int> getPos(QPoint p);
    int sun;
    int cell_x=1;
    int cell_y=1;
    int score=0;
    void stopOrCountintue();
    bool rowHasEmeny[6];
    bool hasEnemy(int row);
    ~yScene();
    explicit yScene(QWidget * parent=0);
    void createZombie();
    void dealDealth();
    void createPlant();
    void putCurPlant(int x,int y);
    void help(QPoint p,int buttontype);
    void  createSun();
    int suncounter=0;
protected:
   void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

signals :
   void  toLight();
};

class dayScene : public yScene{
        Q_OBJECT;
public:
    ~dayScene();
    bool isloss=false;
      void isLoss();
     dayScene(QWidget * parent,std::vector<int> & card);
    void act();
    void initCards(std::vector<int> & card);
    void initMedia();

public slots:
        void timeOut();
};

class startScene : public yScene{
    Q_OBJECT
private :
    QLabel * startbtn=new QLabel(this);
public :

    explicit startScene(QWidget * parent=0);
    void act();


protected:
    void mousePressEvent(QMouseEvent* event);

};

class chooseScene : public yScene{
    Q_OBJECT;
public:
    QLabel * Text;
    QLabel * Text1;
      void  initCards();
    QLabel * start;
    QLabel * smallDay;
    QLabel * smallDark;
    chooseScene (QWidget * parent);
    int getNum();
    QMovie * movie=nullptr;
    int dayOrDark=-1;
     void mousePressEvent(QMouseEvent* event);
     ~chooseScene();
public slots:
    void act();

};


#endif // YSCENE_H

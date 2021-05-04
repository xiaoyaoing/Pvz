#ifndef YSCENE_H
#define YSCENE_H

#include<QMouseEvent>
#include <QLabel>
#include <QMovie>
#include <QTimer>
#include<QPair>


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
    int timecounter=500;
    QMovie * mov;
    QList<yPlant *> plants;
    QList<yZombie *> zombies;
    QList<yMovie *> movies;
    QList<yFly *> flys;
    QList<yPlantCard *> cards;

    QTimer * timer;
    yPlantCard * curCard=nullptr;
    QRect  rect=QRect(0,0,0,0);
    QPair<int,int> getPos(QPoint p);
    int sun;
    int cell_x=1;
    int cell_y=1;
    int score=0;

    bool rowHasEmeny[6];
    bool hasEnemy(int row);
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

    explicit  dayScene(QWidget * parent=0);
    void act();
    void initCards();
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


#endif // YSCENE_H

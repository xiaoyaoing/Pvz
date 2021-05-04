#ifndef YPLANTCARD_H
#define YPLANTCARD_H


#include <yobject.h>
#include <yscene.h>
#include<QLabel>
#include<QMovie>

//enum plantType{
//    shovel=-1,
//    sunflower=0,
//     peashooter=1,
//};
        

class yPlantCard : public QLabel
{
public:
    yPlantCard(QWidget * parent,int type);
    int  type;
    yScene * scene;
    QLabel * front;
    QLabel * back;
    QMovie * movie;
    QLabel * costText;
    int time;
    int counter;
    int sunCost;
    void setPos();
    void mousePressEvent(QMouseEvent* event);
    void act();
};


class peaShooterCard : public yPlantCard{
public:
    peaShooterCard(QWidget * parent);
};

class sunFlowerCard : public yPlantCard{
public :
    sunFlowerCard(QWidget * parent);
};

//class icePeaShooterCard : public yPlantCard{
//public :
//       icePeaShooterCard(QWidget * parent);
//};

//class repeaterCard  : public yPlantCard{
//public :
//       repeaterCard(QWidget * parent);
//};

//class cherryBombcard : public yPlantCard{
//public :
//    cherryBombcard(QWidget * parent);
//};


//class wallNutCard : public yPlantCard{
//public :
//       wallNutCard(QWidget * parent);
//};

//class tallWallNutCard : public yPlantCard{
//public :
//    tallWallNutCard(QWidget * parent);
//};



//class squashCard: public yPlantCard{
//public :
//       squashCard(QWidget * parent);
//};

//class garicCard : public  yPlantCard{
//public :
//    garicCard(QWidget * parent);
//};

//yPlantCard  * getCard();









#endif // YPLANTCARD_H

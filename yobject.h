#ifndef YOBJECT_H
#define YOBJECT_H

#include<QLabel>
#include<QPoint>
class yScene;

class yObject : public QLabel{

    Q_OBJECT
public :
   // QMovie * mov;
    virtual  void act()=0;
      int yoffset=0;
      int xoffset=0;
    bool alive=true;
    int health;
    int strength;
    yScene * scene;
    int row;
    QPoint getRealPos();

    explicit yObject(QWidget * parent);
};

#endif // YOBJECT_H

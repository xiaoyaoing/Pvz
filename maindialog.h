#ifndef MAINDIALOG_H
#define MAINDIALOG_H
#include<QDialog>
#include<yscene.h>
#include<QPushButton>
class MainDialog  : public QDialog
{
    Q_OBJECT
public:
    MainDialog(QWidget * parent=0);
    QPushButton * button;
    yScene * curScene;
 public slots :
    void toLight();
    void toDark();
    void toStart();

};

#endif // MAINDIALOG_H

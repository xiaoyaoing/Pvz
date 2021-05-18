#ifndef MAINDIALOG_H
#define MAINDIALOG_H
#include<QDialog>
#include<yscene.h>
#include<QPushButton>
class MainDialog  : public QDialog
{
    Q_OBJECT
    static MainDialog * instance;
    MainDialog(QWidget * parent=0);
public:
    static MainDialog  * get();

    QPushButton * button;
    yScene * curScene;
 public slots :
    void toLight();
    void toDark();
    void toStart();
    void toChoose();

};

#endif // MAINDIALOG_H

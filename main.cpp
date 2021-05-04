#include "maindialog.h"
#include "yscene.h">
#include <QApplication>
#include "yplant.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     MainDialog d;
     d.show();
    return a.exec();
}

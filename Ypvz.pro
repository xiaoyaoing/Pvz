QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    maindialog.cpp \
    yMovie.cpp \
    yfly.cpp \
    yobject.cpp \
    yplant.cpp \
    yplantcard.cpp \
    yscene.cpp \
    yzombie.cpp

HEADERS += \
    maindialog.h \
    yMovie.h \
    yfly.h \
    yobject.h \
    yplant.h \
    yplantcard.h \
    yscene.h \
    yzombie.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    rc/background1.jpg

RESOURCES += \
    rc/pvz.qrc

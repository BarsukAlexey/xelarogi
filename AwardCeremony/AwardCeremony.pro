#-------------------------------------------------
#
# Project created by QtCreator 2016-11-23T22:18:45
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AwardCeremony
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    SoundPlayer.cpp \
    dialogawardpanel.cpp \
    utils.cpp \
    qitemdelegateformusiclist.cpp

HEADERS  += mainwindow.h \
    SoundPlayer.h \
    dialogawardpanel.h \
    utils.h \
    qitemdelegateformusiclist.h

FORMS    += mainwindow.ui \
    soundplayer.ui \
    dialogawardpanel.ui

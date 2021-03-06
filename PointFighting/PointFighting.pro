#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T15:20:26
#
#-------------------------------------------------

QT       += core gui sql axcontainer #webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PointFighting
TEMPLATE = app
QT += multimedia
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    qrightclickbutton.cpp \
    formscore.cpp \
    form_advertisement.cpp \
    form_advertisement_setting.cpp \
    dialogdisq.cpp \
    logindialog.cpp \
    aspect_ratio_pixmap_label.cpp \
    aspectratiotextlabel.cpp \
    myqlcdnumber.cpp \
    fighting.cpp \
    fightingtable2.cpp

HEADERS  += mainwindow.h \
    qrightclickbutton.h \
    formscore.h \
    forma_dvertisement.h \
    form_advertisement_setting.h \
    dialogdisq.h \
    logindialog.h \
    aspect_ratio_pixmap_label.h \
    aspectratiotextlabel.h \
    myqlcdnumber.h \
    fighting.h \
    fightingtable2.h

FORMS    += mainwindow.ui \
    form.ui \
    form_advertisement.ui \
    form_advertisement_setting.ui \
    dialogdisq.ui \
    logindialog.ui \
    fightingtable2.ui

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
    fighting_table.cpp \
    qrightclickbutton.cpp \
    formscore.cpp \
    form_advertisement.cpp \
    form_advertisement_setting.cpp

HEADERS  += mainwindow.h \
    fighting_table.h \
    qrightclickbutton.h \
    formscore.h \
    forma_dvertisement.h \
    form_advertisement_setting.h

FORMS    += mainwindow.ui \
    fighting_table.ui \
    form.ui \
    form_advertisement.ui \
    form_advertisement_setting.ui

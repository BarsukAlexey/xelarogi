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
    fighting_table.cpp

HEADERS  += mainwindow.h \
    fighting_table.h

FORMS    += mainwindow.ui \
    fighting_table.ui

#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T22:13:52
#
#-------------------------------------------------

QT       += core gui sql axcontainer #webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = TournamentManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    handbookdialog.cpp \
    databaseexpert.cpp \
    webreportdialog.cpp \
    tournamentmanager.cpp

HEADERS  += mainwindow.h \
    handbookdialog.h \
    databaseexpert.h \
    webreportdialog.h \
    tournamentmanager.h

FORMS    += mainwindow.ui \
    handbookdialog.ui \
    webreportdialog.ui

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
    tournamentmanager.cpp \
    tournamentgridwidget.cpp \
    tournamentgriddialog.cpp \
    choosetournamentdialog.cpp \
    tournamentadmindialog.cpp \
    createtournamentdialog.cpp \
    onefieldsetupdialog.cpp \
    createtournamentordersdialog.cpp \
    renderareawidget.cpp \
    tournamentgriddialog2.cpp

HEADERS  += mainwindow.h \
    handbookdialog.h \
    databaseexpert.h \
    webreportdialog.h \
    tournamentmanager.h \
    tournamentgridwidget.h \
    tournamentgriddialog.h \
    choosetournamentdialog.h \
    tournamentadmindialog.h \
    createtournamentdialog.h \
    onefieldsetupdialog.h \
    createtournamentordersdialog.h \
    renderareawidget.h \
    tournamentgriddialog2.h

FORMS    += mainwindow.ui \
    handbookdialog.ui \
    webreportdialog.ui \
    tournamentgridwidget.ui \
    tournamentgriddialog.ui \
    choosetournamentdialog.ui \
    tournamentadmindialog.ui \
    createtournamentdialog.ui \
    onefieldsetupdialog.ui \
    createtournamentordersdialog.ui

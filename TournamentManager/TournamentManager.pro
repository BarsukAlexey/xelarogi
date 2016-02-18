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
    createtournamentdialog.cpp \
    onefieldsetupdialog.cpp \
    createtournamentordersdialog.cpp \
    addorderdialog.cpp \
    renderareawidget.cpp \
    tournamentgriddialog2.cpp \
    fiting_distribution.cpp \
    bd_utils.cpp \
    excel_utils.cpp \
    fighting_pairs.cpp

HEADERS  += mainwindow.h \
    handbookdialog.h \
    databaseexpert.h \
    webreportdialog.h \
    tournamentmanager.h \
    tournamentgridwidget.h \
    tournamentgriddialog.h \
    createtournamentdialog.h \
    onefieldsetupdialog.h \
    createtournamentordersdialog.h \
    addorderdialog.h \
    renderareawidget.h \
    tournamentgriddialog2.h \
    fiting_distribution.h \
    bd_utils.h \
    excel_utils.h \
    fighting_pairs.h

FORMS    += mainwindow.ui \
    handbookdialog.ui \
    webreportdialog.ui \
    tournamentgridwidget.ui \
    tournamentgriddialog.ui \
    createtournamentdialog.ui \
    onefieldsetupdialog.ui \
    createtournamentordersdialog.ui \
    addorderdialog.ui

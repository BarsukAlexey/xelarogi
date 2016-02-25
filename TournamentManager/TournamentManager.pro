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
    createtournamentordersdialog.cpp \
    renderareawidget.cpp \
    tournamentgriddialog2.cpp \
    createtournamentcategoriesdialog.cpp \
    fiting_distribution.cpp \
    excel_utils.cpp \
    fighting_pairs.cpp \
    db_utils.cpp \
    weighing_protocol.cpp \
    winner_report.cpp \
    ebnutvbazu.cpp

HEADERS  += mainwindow.h \
    handbookdialog.h \
    databaseexpert.h \
    webreportdialog.h \
    tournamentmanager.h \
    tournamentgridwidget.h \
    tournamentgriddialog.h \
    createtournamentdialog.h \
    createtournamentordersdialog.h \
    renderareawidget.h \
    tournamentgriddialog2.h \
    createtournamentcategoriesdialog.h \
    fiting_distribution.h \
    excel_utils.h \
    fighting_pairs.h \
    db_utils.h \
    weighing_protocol.h \
    winner_report.h \
    ebnutvbazu.h

FORMS    += mainwindow.ui \
    handbookdialog.ui \
    webreportdialog.ui \
    tournamentgridwidget.ui \
    tournamentgriddialog.ui \
    createtournamentdialog.ui \
    createtournamentordersdialog.ui \
    createtournamentcategoriesdialog.ui

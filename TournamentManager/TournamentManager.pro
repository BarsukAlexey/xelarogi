#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T22:13:52
#
#-------------------------------------------------

QT       += core gui sql axcontainer printsupport #webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = TournamentManager
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    handbookdialog.cpp \
    createtournamentdialog.cpp \
    createtournamentordersdialog.cpp \
    renderareawidget.cpp \
    createtournamentcategoriesdialog.cpp \
    fiting_distribution.cpp \
    excel_utils.cpp \
    fighting_pairs.cpp \
    db_utils.cpp \
    weighing_protocol.cpp \
    winner_report.cpp \
    ebnutvbazu.cpp \
    renderarearesultdialog.cpp \
    createtypedialog.cpp \
    generatetournamentcategoriesdialog.cpp \
    errormessagesdialog.cpp \
    logindialog.cpp \
    trophygenerator.cpp \
    trophygeneratorsettingsdialog.cpp \
    report_manda.cpp \
    report_ministr.cpp \
    dialog_insert_data_in_database.cpp \
    dialog_change_category.cpp \
    dialog_create_age_category.cpp \
    mythread.cpp \
    countryiconsdialog.cpp \
    formdipl.cpp \
    dialogselectfieldsfordimloma.cpp \
    dialogchosedata.cpp \
    dialogschedule.cpp \
    dialogschedulesettinglists.cpp \
    dialogschedule2.cpp \
    dialogschedule2treewidget.cpp \
    dialogschedule2tablewidget.cpp \
    utils.cpp \
    dialogschedule2inputtype.cpp \
    dialogtournamentgrid.cpp \
    sqltablemanager.cpp \
    dialogsqltablemanager.cpp

HEADERS  += mainwindow.h \
    handbookdialog.h \
    createtournamentdialog.h \
    createtournamentordersdialog.h \
    renderareawidget.h \
    createtournamentcategoriesdialog.h \
    fiting_distribution.h \
    excel_utils.h \
    fighting_pairs.h \
    db_utils.h \
    weighing_protocol.h \
    winner_report.h \
    ebnutvbazu.h \
    renderarearesultdialog.h \
    createtypedialog.h \
    generatetournamentcategoriesdialog.h \
    errormessagesdialog.h \
    logindialog.h \
    trophygeneratorsettingsdialog.h \
    report_manda.h \
    report_ministr.h \
    dialog_insert_data_in_database.h \
    dialog_change_category.h \
    dialog_create_age_category.h \
    mythread.h \
    countryiconsdialog.h \
    formdipl.h \
    dialogselectfieldsfordimloma.h \
    dialogchosedata.h \
    dialogschedule.h \
    dialogschedulesettinglists.h \
    dialogschedule2.h \
    dialogschedule2treewidget.h \
    dialogschedule2tablewidget.h \
    utils.h \
    dialogschedule2inputtype.h \
    dialogtournamentgrid.h \
    trophygenerator.h \
    sqltablemanager.h \
    dialogsqltablemanager.h

FORMS    += mainwindow.ui \
    handbookdialog.ui \
    webreportdialog.ui \
    createtournamentdialog.ui \
    createtournamentordersdialog.ui \
    createtournamentcategoriesdialog.ui \
    renderarearesultdialog.ui \
    createtypedialog.ui \
    generatetournamentcategoriesdialog.ui \
    errormessagesdialog.ui \
    logindialog.ui \
    trophygeneratorsettingsdialog.ui \
    dialog_insert_data_in_database.ui \
    dialogchangecategory.ui \
    dialog_create_age_category.ui \
    countryiconsdialog.ui \
    formdipl.ui \
    dialogselectfieldsfordimloma.ui \
    dialogchosedata.ui \
    fighting_pairs.ui \
    dialogschedule.ui \
    dialogschedulesettinglists.ui \
    dialogschedule2.ui \
    dialogschedule2inputtype.ui \
    dialogtournamentgrid.ui \
    sqltablemanager.ui \
    dialogsqltablemanager.ui

DISTFILES +=

RESOURCES +=

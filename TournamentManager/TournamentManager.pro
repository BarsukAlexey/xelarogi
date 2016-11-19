#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T22:13:52
#
#-------------------------------------------------

QT       += core gui sql axcontainer printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = TournamentManager
TEMPLATE = app

LIBS     += libgdi32


SOURCES += main.cpp \
    logindialog.cpp \
    db_utils.cpp \
    utils.cpp \
    ebnutvbazu.cpp \
    excel_utils.cpp \
    dialog_change_category.cpp \
    dialogtournamentgrid.cpp \
    dialogselectfieldsfordimloma.cpp \
    dialogchosedata.cpp \
    renderareawidget.cpp \
    renderarearesultdialog.cpp \
    createtournamentordersdialog.cpp \
    sqltablemanager.cpp \
    dialogsqltablemanager.cpp \
    imageloaderwidget.cpp \
    errormessagesdialog.cpp \
    createtournamentcategoriesdialog.cpp \
    generatetournamentcategoriesdialog.cpp \
    mainwindow.cpp \
    weighing_protocol.cpp \
    dialogschedule.cpp \
    dialogschedulesettinglists.cpp \
    fiting_distribution.cpp \
    fighting_pairs.cpp \
    mythread.cpp \
    dialogorderoftc.cpp \
    dialogschedule2.cpp \
    dialogschedule2treewidget.cpp \
    dialogschedule2tablewidget.cpp \
    dialogschedule2inputtype.cpp \

#    winner_report.cpp \
#    report_manda.cpp \
#    report_ministr.cpp \
#    formdipl.cpp \




HEADERS  += logindialog.h \
    db_utils.h \
    utils.h \
    ebnutvbazu.h \
    excel_utils.h \
    dialog_change_category.h \
    dialogtournamentgrid.h \
    dialogchosedata.h \
    dialogselectfieldsfordimloma.h \
    renderareawidget.h \
    renderarearesultdialog.h \
    createtournamentordersdialog.h \
    sqltablemanager.h \
    dialogsqltablemanager.h \
    imageloaderwidget.h \
    errormessagesdialog.h \
    createtournamentcategoriesdialog.h \
    generatetournamentcategoriesdialog.h \
    mainwindow.h \
    weighing_protocol.h \
    dialogschedule.h \
    dialogschedulesettinglists.h \
    fiting_distribution.h \
    fighting_pairs.h \
    mythread.h \
    dialogorderoftc.h \
    dialogschedule2.h \
    dialogschedule2treewidget.h \
    dialogschedule2tablewidget.h \
    dialogschedule2inputtype.h \
#    winner_report.h \
#    report_manda.h \
#    report_ministr.h \
#    formdipl.h \




FORMS +=  logindialog.ui \
    dialogchangecategory.ui \
    dialogtournamentgrid.ui \
    dialogselectfieldsfordimloma.ui \
    dialogchosedata.ui \
    renderarearesultdialog.ui \
    createtournamentordersdialog.ui \
    sqltablemanager.ui \
    dialogsqltablemanager.ui \
    imageloaderwidget.ui \
    errormessagesdialog.ui \
    createtournamentcategoriesdialog.ui \
    generatetournamentcategoriesdialog.ui \
    mainwindow.ui \
    dialogschedule.ui \
    dialogschedulesettinglists.ui \
    fighting_pairs.ui \
    dialogorderoftc.ui \
    dialogschedule2.ui \
    dialogschedule2inputtype.ui \

#    formdipl.ui \




DISTFILES +=

RESOURCES +=

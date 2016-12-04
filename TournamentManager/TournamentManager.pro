#-------------------------------------------------
#
# Project created by QtCreator 2015-10-22T22:13:52
#
#-------------------------------------------------

QT       += core gui sql axcontainer printsupport multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = TournamentManager
TEMPLATE = app

LIBS     += libgdi32


SOURCES += db_utils.cpp \
    utils.cpp \
    superstruct.cpp \
    main.cpp \
    dialogtournamentgrid.cpp \
    logindialog.cpp \
    dialogchosedata.cpp \
    renderareawidget.cpp \
    renderarearesultdialog.cpp \
    excel_utils.cpp \
    dialogselectfieldsfordimloma.cpp \
    createtournamentordersdialog.cpp \
    sqltablemanager.cpp \
    ebnutvbazu.cpp \
    dialog_change_category.cpp \
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
    winner_report.cpp \
    report_manda.cpp \
    report_ministr.cpp \
    formdipl.cpp \
    dialogaward.cpp \
    SoundPlayer.cpp \
    dialogawardselecttournamentcategories.cpp





HEADERS  += db_utils.h \
    utils.h \
    superstruct.h \
    dialogtournamentgrid.h \
    logindialog.h \
    dialogchosedata.h \
    renderareawidget.h \
    renderarearesultdialog.h \
    excel_utils.h \
    dialogselectfieldsfordimloma.h \
    createtournamentordersdialog.h \
    sqltablemanager.h \
    ebnutvbazu.h \
    dialog_change_category.h \
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
    winner_report.h \
    report_manda.h \
    report_ministr.h \
    formdipl.h \
    dialogaward.h \
    SoundPlayer.h \
    dialogawardselecttournamentcategories.h





FORMS +=  logindialog.ui \
    dialogchangecategory.ui \
    dialogtournamentgrid.ui \
    dialogchosedata.ui \
    renderarearesultdialog.ui \
    dialogselectfieldsfordimloma.ui \
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
    formdipl.ui \
    dialogaward.ui \
    soundplayer.ui \
    dialogawardselecttournamentcategories.ui




DISTFILES +=

RESOURCES += \
    imgs.qrc

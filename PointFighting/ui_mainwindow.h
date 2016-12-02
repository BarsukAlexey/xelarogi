/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_data;
    QAction *actionExport_results;
    QAction *actionAdv;
    QAction *actionSwitch_winner;
    QAction *actionSwapWinner;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QPushButton *pushButtonGo;
    QMenuBar *menuBar;
    QMenu *menuData;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(859, 548);
        actionLoad_data = new QAction(MainWindow);
        actionLoad_data->setObjectName(QStringLiteral("actionLoad_data"));
        actionExport_results = new QAction(MainWindow);
        actionExport_results->setObjectName(QStringLiteral("actionExport_results"));
        actionAdv = new QAction(MainWindow);
        actionAdv->setObjectName(QStringLiteral("actionAdv"));
        actionSwitch_winner = new QAction(MainWindow);
        actionSwitch_winner->setObjectName(QStringLiteral("actionSwitch_winner"));
        actionSwapWinner = new QAction(MainWindow);
        actionSwapWinner->setObjectName(QStringLiteral("actionSwapWinner"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        QFont font;
        font.setPointSize(11);
        tableWidget->setFont(font);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setColumnCount(0);
        tableWidget->verticalHeader()->setVisible(false);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        pushButtonGo = new QPushButton(centralWidget);
        pushButtonGo->setObjectName(QStringLiteral("pushButtonGo"));

        gridLayout->addWidget(pushButtonGo, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 859, 21));
        menuData = new QMenu(menuBar);
        menuData->setObjectName(QStringLiteral("menuData"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuData->menuAction());
        menuData->addAction(actionLoad_data);
        menuData->addAction(actionExport_results);
        menuData->addAction(actionAdv);
        menuData->addAction(actionSwapWinner);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionLoad_data->setText(QApplication::translate("MainWindow", "Load data...", 0));
        actionExport_results->setText(QApplication::translate("MainWindow", "Export results...", 0));
        actionAdv->setText(QApplication::translate("MainWindow", "Setting...", 0));
        actionSwitch_winner->setText(QApplication::translate("MainWindow", "Switch winner...", 0));
        actionSwapWinner->setText(QApplication::translate("MainWindow", "\320\241\320\262\320\260\320\277\320\275\321\203\321\202\321\214 \320\277\320\276\320\261\320\265\320\264\320\270\321\202\320\265\320\273\321\217...", 0));
        pushButtonGo->setText(QApplication::translate("MainWindow", "Go...", 0));
        menuData->setTitle(QApplication::translate("MainWindow", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

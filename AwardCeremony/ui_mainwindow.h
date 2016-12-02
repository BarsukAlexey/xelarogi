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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "soundplayer.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoadData;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QTableWidget *tableWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *pushButtonIV;
    QPushButton *pushButtonII;
    QPushButton *pushButtonI;
    QPushButton *pushButtonIII;
    QPushButton *pushButtonAll;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QRadioButton *radioButtonFrom1To3;
    QRadioButton *radioButtonFrom3To1;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QTreeView *treeViewMusic;
    SoundPlayer *soundPlayer;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_4;
    SoundPlayer *soundPlayerHymn;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(861, 624);
        actionLoadData = new QAction(MainWindow);
        actionLoadData->setObjectName(QStringLiteral("actionLoadData"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tableWidget = new QTableWidget(splitter);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        splitter->addWidget(tableWidget);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setWordWrap(true);

        verticalLayout->addWidget(label_2);

        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButtonIV = new QPushButton(groupBox);
        pushButtonIV->setObjectName(QStringLiteral("pushButtonIV"));

        gridLayout_2->addWidget(pushButtonIV, 4, 0, 1, 1);

        pushButtonII = new QPushButton(groupBox);
        pushButtonII->setObjectName(QStringLiteral("pushButtonII"));

        gridLayout_2->addWidget(pushButtonII, 2, 0, 1, 1);

        pushButtonI = new QPushButton(groupBox);
        pushButtonI->setObjectName(QStringLiteral("pushButtonI"));

        gridLayout_2->addWidget(pushButtonI, 1, 0, 1, 1);

        pushButtonIII = new QPushButton(groupBox);
        pushButtonIII->setObjectName(QStringLiteral("pushButtonIII"));

        gridLayout_2->addWidget(pushButtonIII, 3, 0, 1, 1);

        pushButtonAll = new QPushButton(groupBox);
        pushButtonAll->setObjectName(QStringLiteral("pushButtonAll"));

        gridLayout_2->addWidget(pushButtonAll, 5, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        radioButtonFrom1To3 = new QRadioButton(groupBox_2);
        radioButtonFrom1To3->setObjectName(QStringLiteral("radioButtonFrom1To3"));
        radioButtonFrom1To3->setChecked(true);

        gridLayout_3->addWidget(radioButtonFrom1To3, 0, 0, 1, 1);

        radioButtonFrom3To1 = new QRadioButton(groupBox_2);
        radioButtonFrom3To1->setObjectName(QStringLiteral("radioButtonFrom3To1"));

        gridLayout_3->addWidget(radioButtonFrom3To1, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox_4 = new QGroupBox(layoutWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_2 = new QVBoxLayout(groupBox_4);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);


        verticalLayout_2->addLayout(horizontalLayout);

        treeViewMusic = new QTreeView(groupBox_4);
        treeViewMusic->setObjectName(QStringLiteral("treeViewMusic"));
        treeViewMusic->setSortingEnabled(false);

        verticalLayout_2->addWidget(treeViewMusic);

        soundPlayer = new SoundPlayer(groupBox_4);
        soundPlayer->setObjectName(QStringLiteral("soundPlayer"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(soundPlayer->sizePolicy().hasHeightForWidth());
        soundPlayer->setSizePolicy(sizePolicy);
        soundPlayer->setMinimumSize(QSize(0, 0));

        verticalLayout_2->addWidget(soundPlayer);


        verticalLayout->addWidget(groupBox_4);

        groupBox_3 = new QGroupBox(layoutWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_4 = new QGridLayout(groupBox_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        soundPlayerHymn = new SoundPlayer(groupBox_3);
        soundPlayerHymn->setObjectName(QStringLiteral("soundPlayerHymn"));
        sizePolicy.setHeightForWidth(soundPlayerHymn->sizePolicy().hasHeightForWidth());
        soundPlayerHymn->setSizePolicy(sizePolicy);
        soundPlayerHymn->setMinimumSize(QSize(0, 0));

        gridLayout_4->addWidget(soundPlayerHymn, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        splitter->addWidget(layoutWidget);

        gridLayout->addWidget(splitter, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 861, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(tableWidget, pushButtonI);
        QWidget::setTabOrder(pushButtonI, pushButtonII);
        QWidget::setTabOrder(pushButtonII, pushButtonIII);
        QWidget::setTabOrder(pushButtonIII, pushButtonIV);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionLoadData);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionLoadData->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\320\222\320\265\321\201\320\276\320\262\320\260\321\217 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "I", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "II", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "III", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "III (2)", 0));
        label_2->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\265\321\202\320\265 \320\262\320\265\321\201\320\276\320\262\321\203\321\216 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\216 \320\270 \320\275\320\260\320\266\320\270\320\274\320\260\320\271\321\202\320\265 \320\237\320\240\320\236\320\221\320\225\320\233, \321\207\321\202\320\276\320\261\321\213 \320\277\320\276\320\272\320\260\320\267\321\213\320\262\320\260\321\202\321\214 \320\277\320\276\320\261\320\265\320\264\320\270\321\202\320\265\320\273\320\265\320\271 \320\270\320\273\320\270 \320\272\320\273\320\270\320\272\320\260\320\271\321\202\320\265 \320\275\320\260 \320\272\320\275\320\276\320\277\320\272\320\270, \321\207\321\202\320\276 \321\201\320\275\320\270\320\267\321\203", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", 0));
        pushButtonIV->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 III \320\274\320\265\321\201\321\202\320\276 (2)", 0));
        pushButtonII->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 II \320\274\320\265\321\201\321\202\320\276", 0));
        pushButtonI->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 I \320\274\320\265\321\201\321\202\320\276", 0));
        pushButtonIII->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 III \320\274\320\265\321\201\321\202\320\276", 0));
        pushButtonAll->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\201\321\200\320\260\320\267\321\203 \320\262\321\201\320\265 \320\274\320\265\321\201\321\202\320\260", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\320\237\320\276\321\200\321\217\320\264\320\276\320\272 \320\277\320\276\320\272\320\260\320\267\320\260 \320\277\320\276\320\261\320\265\320\264\320\270\321\202\320\265\320\273\320\265\320\271", 0));
        radioButtonFrom1To3->setText(QApplication::translate("MainWindow", "\320\236\321\202 1\320\263\320\276 \320\272 3\320\265\320\274\321\203 \320\274\320\265\321\201\321\202\321\203", 0));
        radioButtonFrom3To1->setText(QApplication::translate("MainWindow", "\320\236\321\202 3\320\263\320\276 \320\272 1\320\276\320\274\321\203 \320\274\320\265\321\201\321\202\321\203", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "\320\244\320\276\320\275\320\276\320\262\320\260\321\217 \320\274\321\203\320\267\321\213\320\272\320\260", 0));
        label->setText(QApplication::translate("MainWindow", "\320\234\321\203\320\267\321\213\320\272\320\260 \321\201 \320\272\320\260\321\202\320\260\320\273\320\276\320\263\320\260 .\\music", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "\320\223\320\270\320\274\320\275", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

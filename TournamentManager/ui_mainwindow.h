/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *countryAction;
    QAction *regionAction;
    QAction *ateAction;
    QAction *sexAction;
    QAction *typeAction;
    QAction *sportCategoryAction;
    QAction *tournamentAction;
    QAction *tournamentCategoryAction;
    QAction *clubAction;
    QAction *coachAction;
    QAction *orderAction;
    QAction *actionAgeCategory;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter;
    QTreeWidget *tournamentTreeWidget;
    QStackedWidget *stackedWidget;
    QWidget *generalPage;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *testClearBtn;
    QWidget *ordersPage;
    QGridLayout *gridLayout;
    QLabel *tournamentLabel;
    QLabel *tournamentUidLabel;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *createTournamentCategoriesBtn;
    QPushButton *createOrdersBtn;
    QPushButton *pushButtonGrid;
    QPushButton *pushButtonProtokolVzveshinanya;
    QPushButton *pushButtonFightinDistribution;
    QPushButton *pushButtonPair;
    QPushButton *pushButtonLoadWinner;
    QPushButton *pushButtonWinnerReport;
    QPushButton *trophyBtn;
    QPushButton *manda;
    QPushButton *btn_report_ministr;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *handbookMenu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(798, 504);
        countryAction = new QAction(MainWindow);
        countryAction->setObjectName(QStringLiteral("countryAction"));
        regionAction = new QAction(MainWindow);
        regionAction->setObjectName(QStringLiteral("regionAction"));
        ateAction = new QAction(MainWindow);
        ateAction->setObjectName(QStringLiteral("ateAction"));
        sexAction = new QAction(MainWindow);
        sexAction->setObjectName(QStringLiteral("sexAction"));
        typeAction = new QAction(MainWindow);
        typeAction->setObjectName(QStringLiteral("typeAction"));
        sportCategoryAction = new QAction(MainWindow);
        sportCategoryAction->setObjectName(QStringLiteral("sportCategoryAction"));
        tournamentAction = new QAction(MainWindow);
        tournamentAction->setObjectName(QStringLiteral("tournamentAction"));
        tournamentCategoryAction = new QAction(MainWindow);
        tournamentCategoryAction->setObjectName(QStringLiteral("tournamentCategoryAction"));
        clubAction = new QAction(MainWindow);
        clubAction->setObjectName(QStringLiteral("clubAction"));
        coachAction = new QAction(MainWindow);
        coachAction->setObjectName(QStringLiteral("coachAction"));
        orderAction = new QAction(MainWindow);
        orderAction->setObjectName(QStringLiteral("orderAction"));
        actionAgeCategory = new QAction(MainWindow);
        actionAgeCategory->setObjectName(QStringLiteral("actionAgeCategory"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setLineWidth(1);
        splitter->setMidLineWidth(1);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(true);
        splitter->setHandleWidth(10);
        tournamentTreeWidget = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        tournamentTreeWidget->setHeaderItem(__qtreewidgetitem);
        tournamentTreeWidget->setObjectName(QStringLiteral("tournamentTreeWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tournamentTreeWidget->sizePolicy().hasHeightForWidth());
        tournamentTreeWidget->setSizePolicy(sizePolicy1);
        tournamentTreeWidget->setMaximumSize(QSize(400, 16777215));
        tournamentTreeWidget->setAlternatingRowColors(false);
        tournamentTreeWidget->setIndentation(10);
        tournamentTreeWidget->setAnimated(true);
        splitter->addWidget(tournamentTreeWidget);
        tournamentTreeWidget->header()->setCascadingSectionResizes(true);
        tournamentTreeWidget->header()->setStretchLastSection(true);
        stackedWidget = new QStackedWidget(splitter);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(0, 0));
        generalPage = new QWidget();
        generalPage->setObjectName(QStringLiteral("generalPage"));
        generalPage->setMinimumSize(QSize(200, 0));
        gridLayout_2 = new QGridLayout(generalPage);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(generalPage);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(13);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);

        verticalLayout_3->addWidget(label);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        pushButton_3 = new QPushButton(generalPage);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout_3->addWidget(pushButton_3);

        pushButton = new QPushButton(generalPage);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setEnabled(true);

        verticalLayout_3->addWidget(pushButton);

        pushButton_2 = new QPushButton(generalPage);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setEnabled(true);

        verticalLayout_3->addWidget(pushButton_2);

        testClearBtn = new QPushButton(generalPage);
        testClearBtn->setObjectName(QStringLiteral("testClearBtn"));
        testClearBtn->setEnabled(false);

        verticalLayout_3->addWidget(testClearBtn);


        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 1);

        stackedWidget->addWidget(generalPage);
        ordersPage = new QWidget();
        ordersPage->setObjectName(QStringLiteral("ordersPage"));
        ordersPage->setMinimumSize(QSize(200, 0));
        gridLayout = new QGridLayout(ordersPage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tournamentLabel = new QLabel(ordersPage);
        tournamentLabel->setObjectName(QStringLiteral("tournamentLabel"));
        QFont font1;
        font1.setFamily(QStringLiteral("Times New Roman"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        tournamentLabel->setFont(font1);
        tournamentLabel->setWordWrap(true);

        gridLayout->addWidget(tournamentLabel, 0, 0, 1, 1);

        tournamentUidLabel = new QLabel(ordersPage);
        tournamentUidLabel->setObjectName(QStringLiteral("tournamentUidLabel"));
        tournamentUidLabel->setEnabled(true);

        gridLayout->addWidget(tournamentUidLabel, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        createTournamentCategoriesBtn = new QPushButton(ordersPage);
        createTournamentCategoriesBtn->setObjectName(QStringLiteral("createTournamentCategoriesBtn"));

        verticalLayout->addWidget(createTournamentCategoriesBtn);

        createOrdersBtn = new QPushButton(ordersPage);
        createOrdersBtn->setObjectName(QStringLiteral("createOrdersBtn"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(createOrdersBtn->sizePolicy().hasHeightForWidth());
        createOrdersBtn->setSizePolicy(sizePolicy2);
        createOrdersBtn->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(createOrdersBtn);

        pushButtonGrid = new QPushButton(ordersPage);
        pushButtonGrid->setObjectName(QStringLiteral("pushButtonGrid"));

        verticalLayout->addWidget(pushButtonGrid);

        pushButtonProtokolVzveshinanya = new QPushButton(ordersPage);
        pushButtonProtokolVzveshinanya->setObjectName(QStringLiteral("pushButtonProtokolVzveshinanya"));

        verticalLayout->addWidget(pushButtonProtokolVzveshinanya);

        pushButtonFightinDistribution = new QPushButton(ordersPage);
        pushButtonFightinDistribution->setObjectName(QStringLiteral("pushButtonFightinDistribution"));

        verticalLayout->addWidget(pushButtonFightinDistribution);

        pushButtonPair = new QPushButton(ordersPage);
        pushButtonPair->setObjectName(QStringLiteral("pushButtonPair"));

        verticalLayout->addWidget(pushButtonPair);

        pushButtonLoadWinner = new QPushButton(ordersPage);
        pushButtonLoadWinner->setObjectName(QStringLiteral("pushButtonLoadWinner"));

        verticalLayout->addWidget(pushButtonLoadWinner);

        pushButtonWinnerReport = new QPushButton(ordersPage);
        pushButtonWinnerReport->setObjectName(QStringLiteral("pushButtonWinnerReport"));

        verticalLayout->addWidget(pushButtonWinnerReport);

        trophyBtn = new QPushButton(ordersPage);
        trophyBtn->setObjectName(QStringLiteral("trophyBtn"));

        verticalLayout->addWidget(trophyBtn);

        manda = new QPushButton(ordersPage);
        manda->setObjectName(QStringLiteral("manda"));

        verticalLayout->addWidget(manda);

        btn_report_ministr = new QPushButton(ordersPage);
        btn_report_ministr->setObjectName(QStringLiteral("btn_report_ministr"));

        verticalLayout->addWidget(btn_report_ministr);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 2, 0, 1, 1);

        stackedWidget->addWidget(ordersPage);
        splitter->addWidget(stackedWidget);

        verticalLayout_2->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 798, 21));
        handbookMenu = new QMenu(menuBar);
        handbookMenu->setObjectName(QStringLiteral("handbookMenu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(handbookMenu->menuAction());
        handbookMenu->addAction(countryAction);
        handbookMenu->addAction(regionAction);
        handbookMenu->addAction(ateAction);
        handbookMenu->addAction(sexAction);
        handbookMenu->addAction(actionAgeCategory);
        handbookMenu->addAction(typeAction);
        handbookMenu->addAction(sportCategoryAction);
        handbookMenu->addSeparator();
        handbookMenu->addAction(tournamentAction);
        handbookMenu->addAction(tournamentCategoryAction);
        handbookMenu->addSeparator();
        handbookMenu->addAction(clubAction);
        handbookMenu->addAction(coachAction);
        handbookMenu->addSeparator();
        handbookMenu->addSeparator();
        handbookMenu->addAction(orderAction);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        countryAction->setText(QApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\320\275\321\213", 0));
        regionAction->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\263\320\270\320\276\320\275\321\213", 0));
        ateAction->setText(QApplication::translate("MainWindow", "\320\220\320\242\320\225", 0));
        sexAction->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\273", 0));
        typeAction->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\267\320\264\320\265\320\273\321\213", 0));
        sportCategoryAction->setText(QApplication::translate("MainWindow", "\320\241\320\277\320\276\321\200\321\202\320\270\320\262\320\275\321\213\320\265 \321\200\320\260\320\267\321\200\321\217\320\264\321\213", 0));
        tournamentAction->setText(QApplication::translate("MainWindow", "\320\242\321\203\321\200\320\275\320\270\321\200\321\213", 0));
        tournamentCategoryAction->setText(QApplication::translate("MainWindow", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270 \321\202\321\203\321\200\320\275\320\270\321\200\320\276\320\262", 0));
        clubAction->setText(QApplication::translate("MainWindow", "\320\232\320\273\321\203\320\261\321\213", 0));
        coachAction->setText(QApplication::translate("MainWindow", "\320\242\321\200\320\265\320\275\320\265\321\200\321\201\320\272\320\270\320\271 \321\201\320\276\321\201\321\202\320\260\320\262", 0));
        orderAction->setText(QApplication::translate("MainWindow", "\320\227\320\260\321\217\320\262\320\272\320\270", 0));
        actionAgeCategory->setText(QApplication::translate("MainWindow", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202\320\275\321\213\320\265 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270", 0));
        label->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\265\321\202\320\265 \321\202\321\203\321\200\320\275\320\270\321\200", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\260 \321\204\320\273\320\260\320\263\320\260", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\321\202\321\214 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\275\320\264\320\276\320\274\320\275\321\213\320\265 \320\277\320\276\320\261\320\265\320\264\320\270\321\202\320\265\320\273\320\270", 0));
        testClearBtn->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\276\321\210\320\270\320\261\320\276\321\207\320\275\321\213\320\265 \320\267\320\260\320\277\320\270\321\201\320\270 \320\270\320\267 \320\261\320\260\320\267\321\213 (\321\202\320\265\321\201\321\202\320\276\320\262\320\276\320\265)", 0));
        tournamentLabel->setText(QApplication::translate("MainWindow", "\320\242\321\203\321\200\320\275\320\270\321\200. \320\232\320\260\320\272 \321\203\320\261\321\200\320\260\321\202\321\214 \321\215\321\202\320\276 \320\277\321\200\320\270 \320\267\320\260\320\277\321\203\321\201\320\272\320\265?", 0));
        tournamentUidLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        createTournamentCategoriesBtn->setText(QApplication::translate("MainWindow", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        createOrdersBtn->setText(QApplication::translate("MainWindow", "\320\227\320\260\321\217\320\262\320\272\320\270", 0));
        pushButtonGrid->setText(QApplication::translate("MainWindow", "\320\242\321\203\321\200\320\275\320\270\321\200\320\275\321\213\320\265 \321\201\320\265\321\202\320\272\320\270", 0));
        pushButtonProtokolVzveshinanya->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273\321\213 \320\262\320\267\320\262\320\265\321\210\320\270\320\262\320\260\320\275\320\270\321\217", 0));
        pushButtonFightinDistribution->setText(QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272 \321\200\320\260\321\201\320\277\320\265\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\321\217 \320\261\320\276\321\221\320\262", 0));
        pushButtonPair->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\260\320\262\321\213 \320\277\320\260\321\200", 0));
        pushButtonLoadWinner->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\261\320\276\321\221\320\262", 0));
        pushButtonWinnerReport->setText(QApplication::translate("MainWindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\277\320\276\320\261\320\265\320\264\320\270\321\202\320\265\320\273\320\265\320\271", 0));
        trophyBtn->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\263\321\200\320\260\320\274\320\276\321\202\321\213", 0));
        manda->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273 \320\274\320\260\320\275\320\264\320\260\321\202\320\275\320\276\320\271 \320\272\320\276\320\274\320\270\321\201\321\201\320\270\320\270", 0));
        btn_report_ministr->setText(QApplication::translate("MainWindow", "\320\236\321\202\321\207\321\221\321\202 \320\274\320\270\320\275\320\270\321\201\321\202\320\265\321\200\321\201\321\202\320\262\320\260", 0));
        handbookMenu->setTitle(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\276\321\207\320\275\320\270\320\272\320\270", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

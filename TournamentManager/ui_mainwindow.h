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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
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
    QAction *iconsAction;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QTableView *tableViewTournament;
    QStackedWidget *stackedWidget;
    QWidget *generalPage;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;
    QWidget *ordersPage;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButtonProtokolVzveshinanya;
    QPushButton *pushButtonWinnerReport;
    QPushButton *manda;
    QPushButton *btn_report_ministr;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButtonCountries;
    QPushButton *pushButtonRegions;
    QPushButton *pushButtonCities;
    QPushButton *pushButtonClubs;
    QLabel *labelTournament;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButtonTournamentCategories;
    QPushButton *pushButtonOrders;
    QPushButton *pushButtonGrids;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonFightDist;
    QPushButton *pushButtonTimeScheduling;
    QPushButton *pushButtonPair;
    QPushButton *pushButtonLoadWinner;
    QPushButton *trophyBtnImage;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_4;
    QMenuBar *menuBar;
    QMenu *handbookMenu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(997, 416);
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
        iconsAction = new QAction(MainWindow);
        iconsAction->setObjectName(QStringLiteral("iconsAction"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tableViewTournament = new QTableView(splitter);
        tableViewTournament->setObjectName(QStringLiteral("tableViewTournament"));
        tableViewTournament->setMinimumSize(QSize(300, 0));
        tableViewTournament->setFocusPolicy(Qt::WheelFocus);
        tableViewTournament->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableViewTournament->setSelectionMode(QAbstractItemView::SingleSelection);
        tableViewTournament->setSelectionBehavior(QAbstractItemView::SelectRows);
        splitter->addWidget(tableViewTournament);
        tableViewTournament->horizontalHeader()->setStretchLastSection(true);
        stackedWidget = new QStackedWidget(splitter);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(530, 0));
        generalPage = new QWidget();
        generalPage->setObjectName(QStringLiteral("generalPage"));
        generalPage->setMinimumSize(QSize(200, 0));
        layoutWidget = new QWidget(generalPage);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 136, 69));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(13);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);

        verticalLayout_3->addWidget(label);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        stackedWidget->addWidget(generalPage);
        ordersPage = new QWidget();
        ordersPage->setObjectName(QStringLiteral("ordersPage"));
        gridLayout = new QGridLayout(ordersPage);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_2 = new QGroupBox(ordersPage);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        pushButtonProtokolVzveshinanya = new QPushButton(groupBox_2);
        pushButtonProtokolVzveshinanya->setObjectName(QStringLiteral("pushButtonProtokolVzveshinanya"));

        verticalLayout_4->addWidget(pushButtonProtokolVzveshinanya);

        pushButtonWinnerReport = new QPushButton(groupBox_2);
        pushButtonWinnerReport->setObjectName(QStringLiteral("pushButtonWinnerReport"));

        verticalLayout_4->addWidget(pushButtonWinnerReport);

        manda = new QPushButton(groupBox_2);
        manda->setObjectName(QStringLiteral("manda"));

        verticalLayout_4->addWidget(manda);

        btn_report_ministr = new QPushButton(groupBox_2);
        btn_report_ministr->setObjectName(QStringLiteral("btn_report_ministr"));

        verticalLayout_4->addWidget(btn_report_ministr);


        gridLayout->addWidget(groupBox_2, 3, 1, 1, 1);

        groupBox = new QGroupBox(ordersPage);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        pushButtonCountries = new QPushButton(groupBox);
        pushButtonCountries->setObjectName(QStringLiteral("pushButtonCountries"));

        verticalLayout_2->addWidget(pushButtonCountries);

        pushButtonRegions = new QPushButton(groupBox);
        pushButtonRegions->setObjectName(QStringLiteral("pushButtonRegions"));

        verticalLayout_2->addWidget(pushButtonRegions);

        pushButtonCities = new QPushButton(groupBox);
        pushButtonCities->setObjectName(QStringLiteral("pushButtonCities"));

        verticalLayout_2->addWidget(pushButtonCities);

        pushButtonClubs = new QPushButton(groupBox);
        pushButtonClubs->setObjectName(QStringLiteral("pushButtonClubs"));

        verticalLayout_2->addWidget(pushButtonClubs);


        gridLayout->addWidget(groupBox, 1, 1, 1, 1);

        labelTournament = new QLabel(ordersPage);
        labelTournament->setObjectName(QStringLiteral("labelTournament"));
        QFont font1;
        font1.setFamily(QStringLiteral("Times New Roman"));
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        labelTournament->setFont(font1);
        labelTournament->setWordWrap(true);

        gridLayout->addWidget(labelTournament, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(17, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        pushButtonTournamentCategories = new QPushButton(ordersPage);
        pushButtonTournamentCategories->setObjectName(QStringLiteral("pushButtonTournamentCategories"));
        pushButtonTournamentCategories->setFlat(false);

        verticalLayout->addWidget(pushButtonTournamentCategories);

        pushButtonOrders = new QPushButton(ordersPage);
        pushButtonOrders->setObjectName(QStringLiteral("pushButtonOrders"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonOrders->sizePolicy().hasHeightForWidth());
        pushButtonOrders->setSizePolicy(sizePolicy);
        pushButtonOrders->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(pushButtonOrders);

        pushButtonGrids = new QPushButton(ordersPage);
        pushButtonGrids->setObjectName(QStringLiteral("pushButtonGrids"));

        verticalLayout->addWidget(pushButtonGrids);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButtonFightDist = new QPushButton(ordersPage);
        pushButtonFightDist->setObjectName(QStringLiteral("pushButtonFightDist"));

        horizontalLayout_3->addWidget(pushButtonFightDist);

        pushButtonTimeScheduling = new QPushButton(ordersPage);
        pushButtonTimeScheduling->setObjectName(QStringLiteral("pushButtonTimeScheduling"));

        horizontalLayout_3->addWidget(pushButtonTimeScheduling);

        pushButtonPair = new QPushButton(ordersPage);
        pushButtonPair->setObjectName(QStringLiteral("pushButtonPair"));

        horizontalLayout_3->addWidget(pushButtonPair);


        verticalLayout->addLayout(horizontalLayout_3);

        pushButtonLoadWinner = new QPushButton(ordersPage);
        pushButtonLoadWinner->setObjectName(QStringLiteral("pushButtonLoadWinner"));

        verticalLayout->addWidget(pushButtonLoadWinner);

        trophyBtnImage = new QPushButton(ordersPage);
        trophyBtnImage->setObjectName(QStringLiteral("trophyBtnImage"));

        verticalLayout->addWidget(trophyBtnImage);

        verticalSpacer = new QSpacerItem(17, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 1, 0, 3, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 2, 1, 1, 1);

        stackedWidget->addWidget(ordersPage);
        splitter->addWidget(stackedWidget);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 997, 21));
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
        handbookMenu->addAction(tournamentAction);
        handbookMenu->addSeparator();
        handbookMenu->addAction(actionAgeCategory);
        handbookMenu->addAction(typeAction);
        handbookMenu->addAction(sportCategoryAction);
        handbookMenu->addSeparator();
        handbookMenu->addAction(countryAction);
        handbookMenu->addAction(regionAction);
        handbookMenu->addAction(ateAction);
        handbookMenu->addSeparator();
        handbookMenu->addAction(clubAction);
        handbookMenu->addAction(coachAction);
        handbookMenu->addSeparator();

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        countryAction->setText(QApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\320\275\321\213", 0));
        regionAction->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\263\320\270\320\276\320\275\321\213", 0));
        ateAction->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\320\265\320\273\320\265\320\275\320\275\321\213\320\265 \320\277\321\203\320\275\320\272\321\202\321\213", 0));
        sexAction->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\273", 0));
        typeAction->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\270\320\273\320\270", 0));
        sportCategoryAction->setText(QApplication::translate("MainWindow", "\320\241\320\277\320\276\321\200\321\202\320\270\320\262\320\275\321\213\320\265 \321\200\320\260\320\267\321\200\321\217\320\264\321\213", 0));
        tournamentAction->setText(QApplication::translate("MainWindow", "\320\242\321\203\321\200\320\275\320\270\321\200\321\213", 0));
        tournamentCategoryAction->setText(QApplication::translate("MainWindow", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270 \321\202\321\203\321\200\320\275\320\270\321\200\320\276\320\262", 0));
        clubAction->setText(QApplication::translate("MainWindow", "\320\232\320\273\321\203\320\261\321\213", 0));
        coachAction->setText(QApplication::translate("MainWindow", "\320\242\321\200\320\265\320\275\320\265\321\200\321\201\320\272\320\270\320\271 \321\201\320\276\321\201\321\202\320\260\320\262", 0));
        orderAction->setText(QApplication::translate("MainWindow", "\320\227\320\260\321\217\320\262\320\272\320\270", 0));
        actionAgeCategory->setText(QApplication::translate("MainWindow", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202\320\275\321\213\320\265 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270", 0));
        iconsAction->setText(QApplication::translate("MainWindow", "\320\244\320\273\320\260\320\263\320\270 \321\201\321\202\321\200\320\260\320\275", 0));
        label->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\265\321\202\320\265 \321\202\321\203\321\200\320\275\320\270\321\200", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\320\236\321\202\321\207\321\221\321\202\321\213", 0));
        pushButtonProtokolVzveshinanya->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273 \320\262\320\267\320\262\320\265\321\210\320\270\320\262\320\260\320\275\320\270\321\217", 0));
        pushButtonWinnerReport->setText(QApplication::translate("MainWindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\277\320\276\320\261\320\265\320\264\320\270\321\202\320\265\320\273\320\265\320\271", 0));
        manda->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273 \320\274\320\260\320\275\320\264\320\260\321\202\320\275\320\276\320\271 \320\272\320\276\320\274\320\270\321\201\321\201\320\270\320\270", 0));
        btn_report_ministr->setText(QApplication::translate("MainWindow", "\320\236\321\202\321\207\321\221\321\202 \320\274\320\270\320\275\320\270\321\201\321\202\320\265\321\200\321\201\321\202\320\262\320\260", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\276\321\207\320\275\320\270\320\272\320\270", 0));
        pushButtonCountries->setText(QApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\320\275\321\213", 0));
        pushButtonRegions->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\263\320\270\320\276\320\275\321\213", 0));
        pushButtonCities->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\320\265\320\273\320\265\320\275\320\275\321\213\320\265 \320\277\321\203\320\275\320\272\321\202\321\213", 0));
        pushButtonClubs->setText(QApplication::translate("MainWindow", "\320\232\320\273\321\203\320\261\321\213", 0));
        labelTournament->setText(QApplication::translate("MainWindow", "\320\242\321\203\321\200\320\275\320\270\321\200 \320\275\320\265 \320\262\321\213\320\261\321\200\320\260\320\275", 0));
        pushButtonTournamentCategories->setText(QApplication::translate("MainWindow", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        pushButtonOrders->setText(QApplication::translate("MainWindow", "\320\227\320\260\321\217\320\262\320\272\320\270", 0));
        pushButtonGrids->setText(QApplication::translate("MainWindow", "\320\242\321\203\321\200\320\275\320\270\321\200\320\275\321\213\320\265 \321\201\320\265\321\202\320\272\320\270", 0));
        pushButtonFightDist->setText(QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272 \321\200\320\260\321\201\320\277\320\265\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\321\217 \320\261\320\276\321\221\320\262", 0));
        pushButtonTimeScheduling->setText(QApplication::translate("MainWindow", "\320\240\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\320\265", 0));
        pushButtonPair->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\260\320\262 \320\277\320\260\321\200", 0));
        pushButtonLoadWinner->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\261\320\276\321\221\320\262", 0));
        trophyBtnImage->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\261\320\265\320\271\320\264\320\266\320\270 / \320\263\321\200\320\260\320\274\320\276\321\202\321\213 (PDF)", 0));
        handbookMenu->setTitle(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\276\321\207\320\275\320\270\320\272\320\270", 0));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

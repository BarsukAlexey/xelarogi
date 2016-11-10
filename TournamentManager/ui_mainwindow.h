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
    QLabel *labelTournament;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *createTournamentCategoriesBtn;
    QPushButton *createOrdersBtn;
    QPushButton *pushButtonGrid;
    QPushButton *pushButtonProtokolVzveshinanya;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton;
    QPushButton *pushButtonTimeScheduling;
    QPushButton *pushButtonPair;
    QPushButton *pushButtonLoadWinner;
    QPushButton *pushButtonWinnerReport;
    QHBoxLayout *horizontalLayout;
    QPushButton *trophyBtn;
    QPushButton *trophyBtnImage;
    QPushButton *manda;
    QPushButton *btn_report_ministr;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *handbookMenu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(853, 442);
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

        createTournamentCategoriesBtn = new QPushButton(ordersPage);
        createTournamentCategoriesBtn->setObjectName(QStringLiteral("createTournamentCategoriesBtn"));
        createTournamentCategoriesBtn->setFlat(false);

        verticalLayout->addWidget(createTournamentCategoriesBtn);

        createOrdersBtn = new QPushButton(ordersPage);
        createOrdersBtn->setObjectName(QStringLiteral("createOrdersBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(createOrdersBtn->sizePolicy().hasHeightForWidth());
        createOrdersBtn->setSizePolicy(sizePolicy);
        createOrdersBtn->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(createOrdersBtn);

        pushButtonGrid = new QPushButton(ordersPage);
        pushButtonGrid->setObjectName(QStringLiteral("pushButtonGrid"));

        verticalLayout->addWidget(pushButtonGrid);

        pushButtonProtokolVzveshinanya = new QPushButton(ordersPage);
        pushButtonProtokolVzveshinanya->setObjectName(QStringLiteral("pushButtonProtokolVzveshinanya"));

        verticalLayout->addWidget(pushButtonProtokolVzveshinanya);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButton = new QPushButton(ordersPage);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_3->addWidget(pushButton);

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

        pushButtonWinnerReport = new QPushButton(ordersPage);
        pushButtonWinnerReport->setObjectName(QStringLiteral("pushButtonWinnerReport"));

        verticalLayout->addWidget(pushButtonWinnerReport);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        trophyBtn = new QPushButton(ordersPage);
        trophyBtn->setObjectName(QStringLiteral("trophyBtn"));

        horizontalLayout->addWidget(trophyBtn);

        trophyBtnImage = new QPushButton(ordersPage);
        trophyBtnImage->setObjectName(QStringLiteral("trophyBtnImage"));

        horizontalLayout->addWidget(trophyBtnImage);


        verticalLayout->addLayout(horizontalLayout);

        manda = new QPushButton(ordersPage);
        manda->setObjectName(QStringLiteral("manda"));

        verticalLayout->addWidget(manda);

        btn_report_ministr = new QPushButton(ordersPage);
        btn_report_ministr->setObjectName(QStringLiteral("btn_report_ministr"));

        verticalLayout->addWidget(btn_report_ministr);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        verticalSpacer = new QSpacerItem(17, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        stackedWidget->addWidget(ordersPage);
        splitter->addWidget(stackedWidget);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 853, 21));
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
        handbookMenu->addAction(countryAction);
        handbookMenu->addAction(regionAction);
        handbookMenu->addAction(ateAction);
        handbookMenu->addSeparator();
        handbookMenu->addAction(actionAgeCategory);
        handbookMenu->addAction(typeAction);
        handbookMenu->addAction(sportCategoryAction);
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
        ateAction->setText(QApplication::translate("MainWindow", "\320\223\320\276\321\200\320\276\320\264\320\260", 0));
        sexAction->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\273", 0));
        typeAction->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\267\320\264\320\265\320\273\321\213", 0));
        sportCategoryAction->setText(QApplication::translate("MainWindow", "\320\241\320\277\320\276\321\200\321\202\320\270\320\262\320\275\321\213\320\265 \321\200\320\260\320\267\321\200\321\217\320\264\321\213", 0));
        tournamentAction->setText(QApplication::translate("MainWindow", "\320\242\321\203\321\200\320\275\320\270\321\200\321\213", 0));
        tournamentCategoryAction->setText(QApplication::translate("MainWindow", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270 \321\202\321\203\321\200\320\275\320\270\321\200\320\276\320\262", 0));
        clubAction->setText(QApplication::translate("MainWindow", "\320\232\320\273\321\203\320\261\321\213", 0));
        coachAction->setText(QApplication::translate("MainWindow", "\320\242\321\200\320\265\320\275\320\265\321\200\321\201\320\272\320\270\320\271 \321\201\320\276\321\201\321\202\320\260\320\262", 0));
        orderAction->setText(QApplication::translate("MainWindow", "\320\227\320\260\321\217\320\262\320\272\320\270", 0));
        actionAgeCategory->setText(QApplication::translate("MainWindow", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202\320\275\321\213\320\265 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270", 0));
        iconsAction->setText(QApplication::translate("MainWindow", "\320\244\320\273\320\260\320\263\320\270 \321\201\321\202\321\200\320\260\320\275", 0));
        label->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\265\321\202\320\265 \321\202\321\203\321\200\320\275\320\270\321\200", 0));
        labelTournament->setText(QApplication::translate("MainWindow", "\320\242\321\203\321\200\320\275\320\270\321\200 \320\275\320\265 \320\262\321\213\320\261\321\200\320\260\320\275", 0));
        createTournamentCategoriesBtn->setText(QApplication::translate("MainWindow", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        createOrdersBtn->setText(QApplication::translate("MainWindow", "\320\227\320\260\321\217\320\262\320\272\320\270", 0));
        pushButtonGrid->setText(QApplication::translate("MainWindow", "\320\242\321\203\321\200\320\275\320\270\321\200\320\275\321\213\320\265 \321\201\320\265\321\202\320\272\320\270", 0));
        pushButtonProtokolVzveshinanya->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273 \320\262\320\267\320\262\320\265\321\210\320\270\320\262\320\260\320\275\320\270\321\217", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272 \321\200\320\260\321\201\320\277\320\265\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\321\217 \320\261\320\276\321\221\320\262", 0));
        pushButtonTimeScheduling->setText(QApplication::translate("MainWindow", "\320\240\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\320\265", 0));
        pushButtonPair->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\260\320\262 \320\277\320\260\321\200", 0));
        pushButtonLoadWinner->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\261\320\276\321\221\320\262", 0));
        pushButtonWinnerReport->setText(QApplication::translate("MainWindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\277\320\276\320\261\320\265\320\264\320\270\321\202\320\265\320\273\320\265\320\271", 0));
        trophyBtn->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\263\321\200\320\260\320\274\320\276\321\202\321\213 (Excel)", 0));
        trophyBtnImage->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\261\320\265\320\271\320\264\320\266\320\270 / \320\263\321\200\320\260\320\274\320\276\321\202\321\213 (PDF)", 0));
        manda->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273 \320\274\320\260\320\275\320\264\320\260\321\202\320\275\320\276\320\271 \320\272\320\276\320\274\320\270\321\201\321\201\320\270\320\270", 0));
        btn_report_ministr->setText(QApplication::translate("MainWindow", "\320\236\321\202\321\207\321\221\321\202 \320\274\320\270\320\275\320\270\321\201\321\202\320\265\321\200\321\201\321\202\320\262\320\260", 0));
        handbookMenu->setTitle(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\276\321\207\320\275\320\270\320\272\320\270", 0));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

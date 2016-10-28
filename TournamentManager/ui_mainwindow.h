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
    QAction *iconsAction;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QTreeWidget *tournamentTreeWidget;
    QPushButton *pushButtonAddContest;
    QStackedWidget *stackedWidget;
    QWidget *generalPage;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QSpacerItem *verticalSpacer_3;
    QWidget *ordersPage;
    QGridLayout *gridLayout;
    QLabel *tournamentLabel;
    QLabel *tournamentUidLabel;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *createTournamentCategoriesBtn;
    QPushButton *createOrdersBtn;
    QPushButton *pushButton_Flag;
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
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *handbookMenu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(629, 490);
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
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tournamentTreeWidget = new QTreeWidget(widget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        tournamentTreeWidget->setHeaderItem(__qtreewidgetitem);
        tournamentTreeWidget->setObjectName(QStringLiteral("tournamentTreeWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tournamentTreeWidget->sizePolicy().hasHeightForWidth());
        tournamentTreeWidget->setSizePolicy(sizePolicy);
        tournamentTreeWidget->setMaximumSize(QSize(400, 16777215));
        tournamentTreeWidget->setAlternatingRowColors(false);
        tournamentTreeWidget->setIndentation(10);
        tournamentTreeWidget->setAnimated(true);
        tournamentTreeWidget->header()->setCascadingSectionResizes(true);
        tournamentTreeWidget->header()->setStretchLastSection(true);

        gridLayout_3->addWidget(tournamentTreeWidget, 0, 0, 1, 1);

        pushButtonAddContest = new QPushButton(widget);
        pushButtonAddContest->setObjectName(QStringLiteral("pushButtonAddContest"));

        gridLayout_3->addWidget(pushButtonAddContest, 1, 0, 1, 1);


        horizontalLayout_2->addWidget(widget);

        stackedWidget = new QStackedWidget(centralWidget);
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
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(createOrdersBtn->sizePolicy().hasHeightForWidth());
        createOrdersBtn->setSizePolicy(sizePolicy1);
        createOrdersBtn->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(createOrdersBtn);

        pushButton_Flag = new QPushButton(ordersPage);
        pushButton_Flag->setObjectName(QStringLiteral("pushButton_Flag"));

        verticalLayout->addWidget(pushButton_Flag);

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


        verticalLayout->addLayout(horizontalLayout_3);

        pushButtonPair = new QPushButton(ordersPage);
        pushButtonPair->setObjectName(QStringLiteral("pushButtonPair"));

        verticalLayout->addWidget(pushButtonPair);

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

        verticalSpacer = new QSpacerItem(17, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 2, 0, 1, 1);

        stackedWidget->addWidget(ordersPage);

        horizontalLayout_2->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 629, 21));
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
        iconsAction->setText(QApplication::translate("MainWindow", "\320\244\320\273\320\260\320\263\320\270 \321\201\321\202\321\200\320\260\320\275", 0));
        pushButtonAddContest->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\201\320\276\321\200\320\265\320\262\320\275\320\276\320\262\320\260\320\275\320\270\320\265", 0));
        label->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\320\265\321\200\320\265\321\202\320\265 \321\202\321\203\321\200\320\275\320\270\321\200", 0));
        tournamentLabel->setText(QApplication::translate("MainWindow", "\320\242\321\203\321\200\320\275\320\270\321\200 \320\275\320\265 \320\262\321\213\320\261\321\200\320\260\320\275", 0));
        tournamentUidLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        createTournamentCategoriesBtn->setText(QApplication::translate("MainWindow", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        createOrdersBtn->setText(QApplication::translate("MainWindow", "\320\227\320\260\321\217\320\262\320\272\320\270", 0));
        pushButton_Flag->setText(QApplication::translate("MainWindow", "\320\244\320\273\320\260\320\263\320\270", 0));
        pushButtonGrid->setText(QApplication::translate("MainWindow", "\320\242\321\203\321\200\320\275\320\270\321\200\320\275\321\213\320\265 \321\201\320\265\321\202\320\272\320\270", 0));
        pushButtonProtokolVzveshinanya->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\321\202\320\276\320\272\320\276\320\273\321\213 \320\262\320\267\320\262\320\265\321\210\320\270\320\262\320\260\320\275\320\270\321\217", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272 \321\200\320\260\321\201\320\277\320\265\321\200\320\265\320\264\320\265\320\273\320\265\320\275\320\270\321\217 \320\261\320\276\321\221\320\262", 0));
        pushButtonTimeScheduling->setText(QApplication::translate("MainWindow", "\320\240\320\260\321\201\320\277\320\270\321\201\320\260\320\275\320\270\320\265", 0));
        pushButtonPair->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\201\321\202\320\260\320\262\321\213 \320\277\320\260\321\200", 0));
        pushButtonLoadWinner->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \320\261\320\276\321\221\320\262", 0));
        pushButtonWinnerReport->setText(QApplication::translate("MainWindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\277\320\276\320\261\320\265\320\264\320\270\321\202\320\265\320\273\320\265\320\271", 0));
        trophyBtn->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\263\321\200\320\260\320\274\320\276\321\202\321\213 (Excel)", 0));
        trophyBtnImage->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\261\320\265\320\271\320\264\320\266\320\270/\320\263\321\200\320\260\320\274\320\276\321\202\321\213 (PDF)", 0));
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

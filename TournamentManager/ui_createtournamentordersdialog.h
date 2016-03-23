/********************************************************************************
** Form generated from reading UI file 'createtournamentordersdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATETOURNAMENTORDERSDIALOG_H
#define UI_CREATETOURNAMENTORDERSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateTournamentOrdersDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *filterSecondNameLE;
    QLineEdit *filterCountryLE;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *filterFirstNameLE;
    QLineEdit *filterRegionLE;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *filterSexLE;
    QLineEdit *filterRegionUintLE;
    QHBoxLayout *horizontalLayout_9;
    QLineEdit *filterTournamentCategoriesLE;
    QLineEdit *filterCoachLE;
    QSplitter *splitter;
    QTableView *tableView;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QVBoxLayout *verticalLayout_9;
    QLineEdit *secondNameLE;
    QLineEdit *firstNameLE;
    QLineEdit *patronymicLE;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_11;
    QDateEdit *birthdayDE;
    QDoubleSpinBox *weightDSB;
    QComboBox *countriesCB;
    QComboBox *regionsCB;
    QComboBox *regionUnitsCB;
    QComboBox *gendersCB;
    QComboBox *sportCategoriesCB;
    QComboBox *typesCB;
    QComboBox *clubsCB;
    QComboBox *coachsCB;
    QComboBox *tournamentCategoriesCB;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *changeOrderBtn;
    QPushButton *addOrderBtn;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *loadBtn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnExit;

    void setupUi(QDialog *CreateTournamentOrdersDialog)
    {
        if (CreateTournamentOrdersDialog->objectName().isEmpty())
            CreateTournamentOrdersDialog->setObjectName(QStringLiteral("CreateTournamentOrdersDialog"));
        CreateTournamentOrdersDialog->resize(845, 601);
        gridLayout = new QGridLayout(CreateTournamentOrdersDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(CreateTournamentOrdersDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(CreateTournamentOrdersDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        filterSecondNameLE = new QLineEdit(CreateTournamentOrdersDialog);
        filterSecondNameLE->setObjectName(QStringLiteral("filterSecondNameLE"));

        verticalLayout_3->addWidget(filterSecondNameLE);

        filterCountryLE = new QLineEdit(CreateTournamentOrdersDialog);
        filterCountryLE->setObjectName(QStringLiteral("filterCountryLE"));

        verticalLayout_3->addWidget(filterCountryLE);


        horizontalLayout_8->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        filterFirstNameLE = new QLineEdit(CreateTournamentOrdersDialog);
        filterFirstNameLE->setObjectName(QStringLiteral("filterFirstNameLE"));

        verticalLayout_4->addWidget(filterFirstNameLE);

        filterRegionLE = new QLineEdit(CreateTournamentOrdersDialog);
        filterRegionLE->setObjectName(QStringLiteral("filterRegionLE"));

        verticalLayout_4->addWidget(filterRegionLE);


        horizontalLayout_8->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        filterSexLE = new QLineEdit(CreateTournamentOrdersDialog);
        filterSexLE->setObjectName(QStringLiteral("filterSexLE"));

        verticalLayout_5->addWidget(filterSexLE);

        filterRegionUintLE = new QLineEdit(CreateTournamentOrdersDialog);
        filterRegionUintLE->setObjectName(QStringLiteral("filterRegionUintLE"));

        verticalLayout_5->addWidget(filterRegionUintLE);


        horizontalLayout_8->addLayout(verticalLayout_5);


        verticalLayout_6->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        filterTournamentCategoriesLE = new QLineEdit(CreateTournamentOrdersDialog);
        filterTournamentCategoriesLE->setObjectName(QStringLiteral("filterTournamentCategoriesLE"));

        horizontalLayout_9->addWidget(filterTournamentCategoriesLE);

        filterCoachLE = new QLineEdit(CreateTournamentOrdersDialog);
        filterCoachLE->setObjectName(QStringLiteral("filterCoachLE"));

        horizontalLayout_9->addWidget(filterCoachLE);


        verticalLayout_6->addLayout(horizontalLayout_9);


        verticalLayout->addLayout(verticalLayout_6);

        splitter = new QSplitter(CreateTournamentOrdersDialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Horizontal);
        tableView = new QTableView(splitter);
        tableView->setObjectName(QStringLiteral("tableView"));
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);
        tableView->setFocusPolicy(Qt::NoFocus);
        tableView->setContextMenuPolicy(Qt::CustomContextMenu);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        splitter->addWidget(tableView);
        tableView->horizontalHeader()->setCascadingSectionResizes(true);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 0));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_16 = new QLabel(widget);
        label_16->setObjectName(QStringLiteral("label_16"));
        QFont font1;
        font1.setPointSize(8);
        label_16->setFont(font1);

        verticalLayout_8->addWidget(label_16);

        label_17 = new QLabel(widget);
        label_17->setObjectName(QStringLiteral("label_17"));

        verticalLayout_8->addWidget(label_17);

        label_18 = new QLabel(widget);
        label_18->setObjectName(QStringLiteral("label_18"));

        verticalLayout_8->addWidget(label_18);


        horizontalLayout_6->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        secondNameLE = new QLineEdit(widget);
        secondNameLE->setObjectName(QStringLiteral("secondNameLE"));

        verticalLayout_9->addWidget(secondNameLE);

        firstNameLE = new QLineEdit(widget);
        firstNameLE->setObjectName(QStringLiteral("firstNameLE"));

        verticalLayout_9->addWidget(firstNameLE);

        patronymicLE = new QLineEdit(widget);
        patronymicLE->setObjectName(QStringLiteral("patronymicLE"));

        verticalLayout_9->addWidget(patronymicLE);


        horizontalLayout_6->addLayout(verticalLayout_9);


        gridLayout_2->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        label_19 = new QLabel(widget);
        label_19->setObjectName(QStringLiteral("label_19"));

        verticalLayout_10->addWidget(label_19);

        label_20 = new QLabel(widget);
        label_20->setObjectName(QStringLiteral("label_20"));

        verticalLayout_10->addWidget(label_20);

        label_21 = new QLabel(widget);
        label_21->setObjectName(QStringLiteral("label_21"));

        verticalLayout_10->addWidget(label_21);

        label_22 = new QLabel(widget);
        label_22->setObjectName(QStringLiteral("label_22"));

        verticalLayout_10->addWidget(label_22);

        label_23 = new QLabel(widget);
        label_23->setObjectName(QStringLiteral("label_23"));

        verticalLayout_10->addWidget(label_23);

        label_24 = new QLabel(widget);
        label_24->setObjectName(QStringLiteral("label_24"));

        verticalLayout_10->addWidget(label_24);

        label_25 = new QLabel(widget);
        label_25->setObjectName(QStringLiteral("label_25"));

        verticalLayout_10->addWidget(label_25);

        label_26 = new QLabel(widget);
        label_26->setObjectName(QStringLiteral("label_26"));

        verticalLayout_10->addWidget(label_26);

        label_28 = new QLabel(widget);
        label_28->setObjectName(QStringLiteral("label_28"));

        verticalLayout_10->addWidget(label_28);

        label_29 = new QLabel(widget);
        label_29->setObjectName(QStringLiteral("label_29"));

        verticalLayout_10->addWidget(label_29);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_10->addWidget(label_3);


        horizontalLayout_7->addLayout(verticalLayout_10);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        birthdayDE = new QDateEdit(widget);
        birthdayDE->setObjectName(QStringLiteral("birthdayDE"));

        verticalLayout_11->addWidget(birthdayDE);

        weightDSB = new QDoubleSpinBox(widget);
        weightDSB->setObjectName(QStringLiteral("weightDSB"));
        weightDSB->setMaximum(1000);
        weightDSB->setValue(50);

        verticalLayout_11->addWidget(weightDSB);

        countriesCB = new QComboBox(widget);
        countriesCB->setObjectName(QStringLiteral("countriesCB"));

        verticalLayout_11->addWidget(countriesCB);

        regionsCB = new QComboBox(widget);
        regionsCB->setObjectName(QStringLiteral("regionsCB"));

        verticalLayout_11->addWidget(regionsCB);

        regionUnitsCB = new QComboBox(widget);
        regionUnitsCB->setObjectName(QStringLiteral("regionUnitsCB"));

        verticalLayout_11->addWidget(regionUnitsCB);

        gendersCB = new QComboBox(widget);
        gendersCB->setObjectName(QStringLiteral("gendersCB"));

        verticalLayout_11->addWidget(gendersCB);

        sportCategoriesCB = new QComboBox(widget);
        sportCategoriesCB->setObjectName(QStringLiteral("sportCategoriesCB"));

        verticalLayout_11->addWidget(sportCategoriesCB);

        typesCB = new QComboBox(widget);
        typesCB->setObjectName(QStringLiteral("typesCB"));

        verticalLayout_11->addWidget(typesCB);

        clubsCB = new QComboBox(widget);
        clubsCB->setObjectName(QStringLiteral("clubsCB"));

        verticalLayout_11->addWidget(clubsCB);

        coachsCB = new QComboBox(widget);
        coachsCB->setObjectName(QStringLiteral("coachsCB"));

        verticalLayout_11->addWidget(coachsCB);

        tournamentCategoriesCB = new QComboBox(widget);
        tournamentCategoriesCB->setObjectName(QStringLiteral("tournamentCategoriesCB"));

        verticalLayout_11->addWidget(tournamentCategoriesCB);


        horizontalLayout_7->addLayout(verticalLayout_11);


        gridLayout_2->addLayout(horizontalLayout_7, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        changeOrderBtn = new QPushButton(widget);
        changeOrderBtn->setObjectName(QStringLiteral("changeOrderBtn"));
        changeOrderBtn->setEnabled(false);

        horizontalLayout_4->addWidget(changeOrderBtn);

        addOrderBtn = new QPushButton(widget);
        addOrderBtn->setObjectName(QStringLiteral("addOrderBtn"));

        horizontalLayout_4->addWidget(addOrderBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        gridLayout_2->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        splitter->addWidget(widget);

        verticalLayout->addWidget(splitter);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        loadBtn = new QPushButton(CreateTournamentOrdersDialog);
        loadBtn->setObjectName(QStringLiteral("loadBtn"));

        horizontalLayout_2->addWidget(loadBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        btnExit = new QPushButton(CreateTournamentOrdersDialog);
        btnExit->setObjectName(QStringLiteral("btnExit"));

        horizontalLayout_2->addWidget(btnExit);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(CreateTournamentOrdersDialog);

        QMetaObject::connectSlotsByName(CreateTournamentOrdersDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateTournamentOrdersDialog)
    {
        CreateTournamentOrdersDialog->setWindowTitle(QApplication::translate("CreateTournamentOrdersDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\267\320\260\321\217\320\262\320\276\320\272 \320\272 \321\202\321\203\321\200\320\275\320\270\321\200\321\203", 0));
        label->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\241\320\277\321\200\320\260\320\262\320\276\321\207\320\275\320\270\320\272", 0));
        label_2->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\244\320\270\320\273\321\214\321\202\321\200", 0));
        filterSecondNameLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterCountryLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\241\321\202\321\200\320\260\320\275\320\260 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterFirstNameLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\230\320\274\321\217  (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterRegionLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\240\320\265\320\263\320\270\320\276\320\275 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterSexLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\237\320\276\320\273 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterRegionUintLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\235\320\260\321\201\320\265\320\273\320\265\320\275\320\275\321\213\320\271 \320\277\321\203\320\275\320\272\321\202 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterTournamentCategoriesLE->setInputMask(QString());
        filterTournamentCategoriesLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217 \321\202\321\203\321\200\320\275\320\270\321\200\320\260 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterCoachLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\242\321\200\320\265\320\275\320\265\321\200 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        label_16->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217", 0));
        label_17->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\230\320\274\321\217", 0));
        label_18->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\236\321\202\321\207\320\265\321\201\321\202\320\262\320\276", 0));
        label_19->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\224\320\260\321\202\320\260 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", 0));
        label_20->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\222\320\265\321\201", 0));
        label_21->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\241\321\202\321\200\320\260\320\275\320\260", 0));
        label_22->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\240\320\265\320\263\320\270\320\276\320\275", 0));
        label_23->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\235\320\260\321\201\320\265\320\273\320\265\320\275\320\275\321\213\320\271 \320\277\321\203\320\275\320\272\321\202", 0));
        label_24->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\237\320\276\320\273", 0));
        label_25->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\241\320\277\320\276\321\200\321\202\320\270\320\262\320\275\321\213\320\271 \321\200\320\260\320\267\321\200\321\217\320\264", 0));
        label_26->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\240\320\260\320\267\320\264\320\265\320\273 \321\201\320\276\321\200\320\265\320\262\320\275\320\276\320\262\320\260\320\275\320\270\321\217", 0));
        label_28->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\232\320\273\321\203\320\261", 0));
        label_29->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\242\321\200\320\265\320\275\320\265\321\200", 0));
        label_3->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        changeOrderBtn->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0));
        addOrderBtn->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0));
        loadBtn->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267 excel", 0));
        btnExit->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateTournamentOrdersDialog: public Ui_CreateTournamentOrdersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETOURNAMENTORDERSDIALOG_H

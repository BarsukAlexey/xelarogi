/********************************************************************************
** Form generated from reading UI file 'createtournamentordersdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
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
#include <QtWidgets/QFormLayout>
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
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
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
    QHBoxLayout *horizontalLayout_2;
    QPushButton *loadBtn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *toExcelBtn;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QSplitter *splitter;
    QTableView *tableView;
    QWidget *widget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButtonChangeCategory;
    QSpacerItem *verticalSpacer;
    QFormLayout *formLayout;
    QLabel *label_16;
    QLineEdit *secondNameLE;
    QLabel *label_17;
    QLineEdit *firstNameLE;
    QLabel *label_18;
    QLineEdit *patronymicLE;
    QLabel *label_19;
    QDateEdit *birthdayDE;
    QLabel *label_20;
    QDoubleSpinBox *weightDSB;
    QLabel *label_21;
    QComboBox *countriesCB;
    QLabel *label_22;
    QComboBox *regionsCB;
    QLabel *label_23;
    QComboBox *regionUnitsCB;
    QLabel *label_24;
    QComboBox *gendersCB;
    QLabel *label_25;
    QComboBox *sportCategoriesCB;
    QLabel *label_26;
    QComboBox *typesCB;
    QLabel *label_28;
    QComboBox *clubsCB;
    QLabel *label_29;
    QComboBox *coachsCB;
    QLabel *label_3;
    QLabel *labelTournamentCategories;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *changeOrderBtn;
    QPushButton *addOrderBtn;
    QPushButton *pushButtonShowGrid;

    void setupUi(QDialog *CreateTournamentOrdersDialog)
    {
        if (CreateTournamentOrdersDialog->objectName().isEmpty())
            CreateTournamentOrdersDialog->setObjectName(QStringLiteral("CreateTournamentOrdersDialog"));
        CreateTournamentOrdersDialog->resize(1022, 804);
        gridLayout_2 = new QGridLayout(CreateTournamentOrdersDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
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


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

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


        gridLayout_2->addLayout(verticalLayout_6, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        loadBtn = new QPushButton(CreateTournamentOrdersDialog);
        loadBtn->setObjectName(QStringLiteral("loadBtn"));

        horizontalLayout_2->addWidget(loadBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        toExcelBtn = new QPushButton(CreateTournamentOrdersDialog);
        toExcelBtn->setObjectName(QStringLiteral("toExcelBtn"));

        horizontalLayout_2->addWidget(toExcelBtn);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        gridLayout_2->addLayout(horizontalLayout_2, 4, 0, 1, 1);

        label_4 = new QLabel(CreateTournamentOrdersDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 5, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(CreateTournamentOrdersDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 0, 1, 1);

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
        tableView->setFocusPolicy(Qt::ClickFocus);
        tableView->setContextMenuPolicy(Qt::CustomContextMenu);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(true);
        splitter->addWidget(tableView);
        tableView->horizontalHeader()->setCascadingSectionResizes(false);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(true);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 0));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        pushButtonChangeCategory = new QPushButton(widget);
        pushButtonChangeCategory->setObjectName(QStringLiteral("pushButtonChangeCategory"));

        horizontalLayout_6->addWidget(pushButtonChangeCategory);


        gridLayout->addLayout(horizontalLayout_6, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_16 = new QLabel(widget);
        label_16->setObjectName(QStringLiteral("label_16"));
        QFont font1;
        font1.setPointSize(8);
        label_16->setFont(font1);
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_16);

        secondNameLE = new QLineEdit(widget);
        secondNameLE->setObjectName(QStringLiteral("secondNameLE"));

        formLayout->setWidget(0, QFormLayout::FieldRole, secondNameLE);

        label_17 = new QLabel(widget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_17);

        firstNameLE = new QLineEdit(widget);
        firstNameLE->setObjectName(QStringLiteral("firstNameLE"));

        formLayout->setWidget(1, QFormLayout::FieldRole, firstNameLE);

        label_18 = new QLabel(widget);
        label_18->setObjectName(QStringLiteral("label_18"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_18);

        patronymicLE = new QLineEdit(widget);
        patronymicLE->setObjectName(QStringLiteral("patronymicLE"));

        formLayout->setWidget(2, QFormLayout::FieldRole, patronymicLE);

        label_19 = new QLabel(widget);
        label_19->setObjectName(QStringLiteral("label_19"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_19);

        birthdayDE = new QDateEdit(widget);
        birthdayDE->setObjectName(QStringLiteral("birthdayDE"));

        formLayout->setWidget(3, QFormLayout::FieldRole, birthdayDE);

        label_20 = new QLabel(widget);
        label_20->setObjectName(QStringLiteral("label_20"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_20);

        weightDSB = new QDoubleSpinBox(widget);
        weightDSB->setObjectName(QStringLiteral("weightDSB"));
        weightDSB->setMaximum(1000);
        weightDSB->setValue(50);

        formLayout->setWidget(4, QFormLayout::FieldRole, weightDSB);

        label_21 = new QLabel(widget);
        label_21->setObjectName(QStringLiteral("label_21"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_21);

        countriesCB = new QComboBox(widget);
        countriesCB->setObjectName(QStringLiteral("countriesCB"));
        countriesCB->setMaxVisibleItems(69);

        formLayout->setWidget(5, QFormLayout::FieldRole, countriesCB);

        label_22 = new QLabel(widget);
        label_22->setObjectName(QStringLiteral("label_22"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_22);

        regionsCB = new QComboBox(widget);
        regionsCB->setObjectName(QStringLiteral("regionsCB"));
        regionsCB->setMaxVisibleItems(69);

        formLayout->setWidget(6, QFormLayout::FieldRole, regionsCB);

        label_23 = new QLabel(widget);
        label_23->setObjectName(QStringLiteral("label_23"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_23);

        regionUnitsCB = new QComboBox(widget);
        regionUnitsCB->setObjectName(QStringLiteral("regionUnitsCB"));
        regionUnitsCB->setMaxVisibleItems(69);

        formLayout->setWidget(7, QFormLayout::FieldRole, regionUnitsCB);

        label_24 = new QLabel(widget);
        label_24->setObjectName(QStringLiteral("label_24"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_24);

        gendersCB = new QComboBox(widget);
        gendersCB->setObjectName(QStringLiteral("gendersCB"));
        gendersCB->setMaxVisibleItems(69);

        formLayout->setWidget(8, QFormLayout::FieldRole, gendersCB);

        label_25 = new QLabel(widget);
        label_25->setObjectName(QStringLiteral("label_25"));

        formLayout->setWidget(9, QFormLayout::LabelRole, label_25);

        sportCategoriesCB = new QComboBox(widget);
        sportCategoriesCB->setObjectName(QStringLiteral("sportCategoriesCB"));
        sportCategoriesCB->setMaxVisibleItems(69);

        formLayout->setWidget(9, QFormLayout::FieldRole, sportCategoriesCB);

        label_26 = new QLabel(widget);
        label_26->setObjectName(QStringLiteral("label_26"));

        formLayout->setWidget(10, QFormLayout::LabelRole, label_26);

        typesCB = new QComboBox(widget);
        typesCB->setObjectName(QStringLiteral("typesCB"));
        typesCB->setEnabled(true);

        formLayout->setWidget(10, QFormLayout::FieldRole, typesCB);

        label_28 = new QLabel(widget);
        label_28->setObjectName(QStringLiteral("label_28"));

        formLayout->setWidget(11, QFormLayout::LabelRole, label_28);

        clubsCB = new QComboBox(widget);
        clubsCB->setObjectName(QStringLiteral("clubsCB"));
        clubsCB->setMaxVisibleItems(69);

        formLayout->setWidget(11, QFormLayout::FieldRole, clubsCB);

        label_29 = new QLabel(widget);
        label_29->setObjectName(QStringLiteral("label_29"));

        formLayout->setWidget(12, QFormLayout::LabelRole, label_29);

        coachsCB = new QComboBox(widget);
        coachsCB->setObjectName(QStringLiteral("coachsCB"));
        coachsCB->setMaxVisibleItems(69);

        formLayout->setWidget(12, QFormLayout::FieldRole, coachsCB);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(13, QFormLayout::LabelRole, label_3);

        labelTournamentCategories = new QLabel(widget);
        labelTournamentCategories->setObjectName(QStringLiteral("labelTournamentCategories"));

        formLayout->setWidget(13, QFormLayout::FieldRole, labelTournamentCategories);


        gridLayout->addLayout(formLayout, 0, 0, 1, 2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        changeOrderBtn = new QPushButton(widget);
        changeOrderBtn->setObjectName(QStringLiteral("changeOrderBtn"));
        changeOrderBtn->setEnabled(false);

        horizontalLayout_5->addWidget(changeOrderBtn);

        addOrderBtn = new QPushButton(widget);
        addOrderBtn->setObjectName(QStringLiteral("addOrderBtn"));

        horizontalLayout_5->addWidget(addOrderBtn);


        gridLayout->addLayout(horizontalLayout_5, 1, 0, 1, 2);

        pushButtonShowGrid = new QPushButton(widget);
        pushButtonShowGrid->setObjectName(QStringLiteral("pushButtonShowGrid"));

        gridLayout->addWidget(pushButtonShowGrid, 3, 0, 1, 2);

        splitter->addWidget(widget);

        gridLayout_2->addWidget(splitter, 3, 0, 1, 1);

        QWidget::setTabOrder(filterSecondNameLE, filterFirstNameLE);
        QWidget::setTabOrder(filterFirstNameLE, filterSexLE);
        QWidget::setTabOrder(filterSexLE, filterCountryLE);
        QWidget::setTabOrder(filterCountryLE, filterRegionLE);
        QWidget::setTabOrder(filterRegionLE, filterRegionUintLE);
        QWidget::setTabOrder(filterRegionUintLE, filterTournamentCategoriesLE);
        QWidget::setTabOrder(filterTournamentCategoriesLE, filterCoachLE);
        QWidget::setTabOrder(filterCoachLE, secondNameLE);
        QWidget::setTabOrder(secondNameLE, firstNameLE);
        QWidget::setTabOrder(firstNameLE, patronymicLE);
        QWidget::setTabOrder(patronymicLE, birthdayDE);
        QWidget::setTabOrder(birthdayDE, weightDSB);
        QWidget::setTabOrder(weightDSB, countriesCB);
        QWidget::setTabOrder(countriesCB, regionsCB);
        QWidget::setTabOrder(regionsCB, regionUnitsCB);
        QWidget::setTabOrder(regionUnitsCB, gendersCB);
        QWidget::setTabOrder(gendersCB, sportCategoriesCB);
        QWidget::setTabOrder(sportCategoriesCB, typesCB);
        QWidget::setTabOrder(typesCB, clubsCB);
        QWidget::setTabOrder(clubsCB, coachsCB);
        QWidget::setTabOrder(coachsCB, changeOrderBtn);
        QWidget::setTabOrder(changeOrderBtn, addOrderBtn);
        QWidget::setTabOrder(addOrderBtn, pushButtonChangeCategory);
        QWidget::setTabOrder(pushButtonChangeCategory, loadBtn);
        QWidget::setTabOrder(loadBtn, toExcelBtn);

        retranslateUi(CreateTournamentOrdersDialog);

        QMetaObject::connectSlotsByName(CreateTournamentOrdersDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateTournamentOrdersDialog)
    {
        CreateTournamentOrdersDialog->setWindowTitle(QApplication::translate("CreateTournamentOrdersDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\267\320\260\321\217\320\262\320\276\320\272 \320\272 \321\202\321\203\321\200\320\275\320\270\321\200\321\203", 0));
        label->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\241\320\277\321\200\320\260\320\262\320\276\321\207\320\275\320\270\320\272", 0));
        filterSecondNameLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterCountryLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\241\321\202\321\200\320\260\320\275\320\260 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterFirstNameLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\230\320\274\321\217  (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterRegionLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\240\320\265\320\263\320\270\320\276\320\275 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterSexLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\237\320\276\320\273 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterRegionUintLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\235\320\260\321\201\320\265\320\273\320\265\320\275\320\275\321\213\320\271 \320\277\321\203\320\275\320\272\321\202 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterTournamentCategoriesLE->setInputMask(QString());
        filterTournamentCategoriesLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217 \321\202\321\203\321\200\320\275\320\270\321\200\320\260 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        filterCoachLE->setPlaceholderText(QApplication::translate("CreateTournamentOrdersDialog", "\320\242\321\200\320\265\320\275\320\265\321\200 (\321\204\320\270\320\273\321\214\321\202\321\200)", 0));
        loadBtn->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267 excel", 0));
        toExcelBtn->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\222\321\213\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\262 Excel", 0));
        label_4->setText(QApplication::translate("CreateTournamentOrdersDialog", "*\320\237\320\265\321\200\320\265\320\264 \320\267\320\260\320\263\321\200\321\203\320\267\320\272\320\276\320\271 \320\267\320\260\321\217\320\262\320\276\320\272 \320\267\320\260\320\272\321\200\321\213\321\202\321\214 Excel \320\270 \320\262\321\201\320\265 \320\265\320\263\320\276 \320\277\321\200\320\276\321\206\320\265\321\201\321\201\321\213 \320\262 \320\264\320\270\321\201\320\277\320\265\321\202\321\207\320\265\321\200\320\265 \320\267\320\260\320\264\320\260\321\207", 0));
        label_2->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\244\320\270\320\273\321\214\321\202\321\200", 0));
        pushButtonChangeCategory->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\241\320\274\320\265\320\275\320\270\321\202\321\214 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\216 \321\203\321\207\320\260\321\201\321\202\320\275\320\270\320\272\320\260....", 0));
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
        labelTournamentCategories->setText(QApplication::translate("CreateTournamentOrdersDialog", "TextLabel", 0));
        changeOrderBtn->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0));
        addOrderBtn->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\275\320\276\320\262\320\276\320\263\320\276 \321\203\321\207\320\260\321\201\321\202\320\275\320\270\320\272\320\260", 0));
        pushButtonShowGrid->setText(QApplication::translate("CreateTournamentOrdersDialog", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\201\320\265\321\202\320\272\321\203", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateTournamentOrdersDialog: public Ui_CreateTournamentOrdersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETOURNAMENTORDERSDIALOG_H

/********************************************************************************
** Form generated from reading UI file 'createtournamentcategoriesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATETOURNAMENTCATEGORIESDIALOG_H
#define UI_CREATETOURNAMENTCATEGORIESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateTournamentCategoriesDialog
{
public:
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QTableView *tableView;
    QWidget *widget;
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_11;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_9;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_10;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *nameLE;
    QComboBox *sexCB;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonAddAgeCat;
    QComboBox *comboBoxAgeCategory;
    QSpinBox *ageFromSB;
    QSpinBox *ageTillSB;
    QDoubleSpinBox *weightFromDSB;
    QDoubleSpinBox *weightTillDSB;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addTypeBtn;
    QComboBox *typeCB;
    QSpinBox *durationFightingSB;
    QSpinBox *durationBreakSB;
    QSpinBox *roundCountSB;
    QPushButton *applyBtn;
    QPushButton *addBtn;
    QPushButton *pushButtonAddGroupOfCaterories;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *CreateTournamentCategoriesDialog)
    {
        if (CreateTournamentCategoriesDialog->objectName().isEmpty())
            CreateTournamentCategoriesDialog->setObjectName(QStringLiteral("CreateTournamentCategoriesDialog"));
        CreateTournamentCategoriesDialog->setWindowModality(Qt::NonModal);
        CreateTournamentCategoriesDialog->resize(1069, 581);
        gridLayout_2 = new QGridLayout(CreateTournamentCategoriesDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter = new QSplitter(CreateTournamentCategoriesDialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tableView = new QTableView(splitter);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setFocusPolicy(Qt::ClickFocus);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(false);
        splitter->addWidget(tableView);
        tableView->verticalHeader()->setVisible(false);
        tableView->verticalHeader()->setHighlightSections(false);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(300, 0));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        label_11 = new QLabel(widget);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout->addWidget(label_11);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        label_9 = new QLabel(widget);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout->addWidget(label_9);

        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        label_8 = new QLabel(widget);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout->addWidget(label_8);

        label_10 = new QLabel(widget);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout->addWidget(label_10);


        formLayout->setLayout(0, QFormLayout::LabelRole, verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        nameLE = new QLineEdit(widget);
        nameLE->setObjectName(QStringLiteral("nameLE"));

        verticalLayout_2->addWidget(nameLE);

        sexCB = new QComboBox(widget);
        sexCB->setObjectName(QStringLiteral("sexCB"));

        verticalLayout_2->addWidget(sexCB);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        buttonAddAgeCat = new QPushButton(widget);
        buttonAddAgeCat->setObjectName(QStringLiteral("buttonAddAgeCat"));
        buttonAddAgeCat->setMaximumSize(QSize(24, 16777215));

        horizontalLayout->addWidget(buttonAddAgeCat);

        comboBoxAgeCategory = new QComboBox(widget);
        comboBoxAgeCategory->setObjectName(QStringLiteral("comboBoxAgeCategory"));

        horizontalLayout->addWidget(comboBoxAgeCategory);


        verticalLayout_2->addLayout(horizontalLayout);

        ageFromSB = new QSpinBox(widget);
        ageFromSB->setObjectName(QStringLiteral("ageFromSB"));
        ageFromSB->setMaximum(1000);

        verticalLayout_2->addWidget(ageFromSB);

        ageTillSB = new QSpinBox(widget);
        ageTillSB->setObjectName(QStringLiteral("ageTillSB"));
        ageTillSB->setMinimum(1);
        ageTillSB->setMaximum(99);

        verticalLayout_2->addWidget(ageTillSB);

        weightFromDSB = new QDoubleSpinBox(widget);
        weightFromDSB->setObjectName(QStringLiteral("weightFromDSB"));
        weightFromDSB->setMaximum(11200);

        verticalLayout_2->addWidget(weightFromDSB);

        weightTillDSB = new QDoubleSpinBox(widget);
        weightTillDSB->setObjectName(QStringLiteral("weightTillDSB"));
        weightTillDSB->setMinimum(1);
        weightTillDSB->setMaximum(11200);

        verticalLayout_2->addWidget(weightTillDSB);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        addTypeBtn = new QPushButton(widget);
        addTypeBtn->setObjectName(QStringLiteral("addTypeBtn"));
        addTypeBtn->setMaximumSize(QSize(24, 16777215));

        horizontalLayout_3->addWidget(addTypeBtn);

        typeCB = new QComboBox(widget);
        typeCB->setObjectName(QStringLiteral("typeCB"));
        typeCB->setMaxVisibleItems(30);

        horizontalLayout_3->addWidget(typeCB);


        verticalLayout_2->addLayout(horizontalLayout_3);

        durationFightingSB = new QSpinBox(widget);
        durationFightingSB->setObjectName(QStringLiteral("durationFightingSB"));
        durationFightingSB->setMinimum(10);
        durationFightingSB->setMaximum(10000);
        durationFightingSB->setValue(15);

        verticalLayout_2->addWidget(durationFightingSB);

        durationBreakSB = new QSpinBox(widget);
        durationBreakSB->setObjectName(QStringLiteral("durationBreakSB"));
        durationBreakSB->setMinimum(10);
        durationBreakSB->setMaximum(10000);

        verticalLayout_2->addWidget(durationBreakSB);

        roundCountSB = new QSpinBox(widget);
        roundCountSB->setObjectName(QStringLiteral("roundCountSB"));
        roundCountSB->setMinimum(1);

        verticalLayout_2->addWidget(roundCountSB);


        formLayout->setLayout(0, QFormLayout::FieldRole, verticalLayout_2);

        applyBtn = new QPushButton(widget);
        applyBtn->setObjectName(QStringLiteral("applyBtn"));
        applyBtn->setEnabled(false);

        formLayout->setWidget(1, QFormLayout::SpanningRole, applyBtn);

        addBtn = new QPushButton(widget);
        addBtn->setObjectName(QStringLiteral("addBtn"));

        formLayout->setWidget(2, QFormLayout::SpanningRole, addBtn);

        pushButtonAddGroupOfCaterories = new QPushButton(widget);
        pushButtonAddGroupOfCaterories->setObjectName(QStringLiteral("pushButtonAddGroupOfCaterories"));

        formLayout->setWidget(3, QFormLayout::SpanningRole, pushButtonAddGroupOfCaterories);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(4, QFormLayout::LabelRole, verticalSpacer);

        splitter->addWidget(widget);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(CreateTournamentCategoriesDialog);

        QMetaObject::connectSlotsByName(CreateTournamentCategoriesDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateTournamentCategoriesDialog)
    {
        CreateTournamentCategoriesDialog->setWindowTitle(QApplication::translate("CreateTournamentCategoriesDialog", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\271 \320\264\320\273\321\217 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        label_5->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265", 0));
        label_6->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\237\320\276\320\273", 0));
        label_11->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202\320\275\320\260\321\217 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217", 0));
        label->setText(QApplication::translate("CreateTournamentCategoriesDialog", "<html><head/><body><p>\320\222\320\276\320\267\321\200\320\260\321\201\321\202 \320\276\321\202</p></body></html>", 0));
        label_2->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202 \320\264\320\276", 0));
        label_3->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\222\320\265\321\201 \321\201\320\262\321\213\321\210\320\265", 0));
        label_4->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\222\320\265\321\201 \320\264\320\276", 0));
        label_9->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\240\320\260\320\267\320\264\320\265\320\273", 0));
        label_7->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\224\320\273\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \320\261\320\276\321\217, \321\201.", 0));
        label_8->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\237\320\265\321\200\320\265\321\200\321\213\320\262, \321\201.", 0));
        label_10->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\200\320\260\321\203\320\275\320\264\320\276\320\262", 0));
        buttonAddAgeCat->setText(QApplication::translate("CreateTournamentCategoriesDialog", "+", 0));
        addTypeBtn->setText(QApplication::translate("CreateTournamentCategoriesDialog", "+", 0));
        applyBtn->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0));
        addBtn->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\276\320\264\320\275\321\203 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\216 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\216", 0));
        pushButtonAddGroupOfCaterories->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\263\321\200\321\203\320\277\320\277\321\213 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\271 \321\202\321\203\321\200\320\275\320\270\321\200\320\260...", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateTournamentCategoriesDialog: public Ui_CreateTournamentCategoriesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETOURNAMENTCATEGORIESDIALOG_H

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
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QLabel *label_6;
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
    QSpinBox *ageFromSB;
    QSpinBox *ageTillSB;
    QDoubleSpinBox *weightFromDSB;
    QDoubleSpinBox *weightTillDSB;
    QComboBox *typeCB;
    QSpinBox *durationFightingSB;
    QSpinBox *durationBreakSB;
    QSpinBox *roundCountSB;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *applyBtn;
    QPushButton *addBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;

    void setupUi(QDialog *CreateTournamentCategoriesDialog)
    {
        if (CreateTournamentCategoriesDialog->objectName().isEmpty())
            CreateTournamentCategoriesDialog->setObjectName(QStringLiteral("CreateTournamentCategoriesDialog"));
        CreateTournamentCategoriesDialog->resize(646, 333);
        gridLayout_2 = new QGridLayout(CreateTournamentCategoriesDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter = new QSplitter(CreateTournamentCategoriesDialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tableView = new QTableView(splitter);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setFocusPolicy(Qt::NoFocus);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
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
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

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


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        nameLE = new QLineEdit(widget);
        nameLE->setObjectName(QStringLiteral("nameLE"));

        verticalLayout_2->addWidget(nameLE);

        sexCB = new QComboBox(widget);
        sexCB->setObjectName(QStringLiteral("sexCB"));

        verticalLayout_2->addWidget(sexCB);

        ageFromSB = new QSpinBox(widget);
        ageFromSB->setObjectName(QStringLiteral("ageFromSB"));
        ageFromSB->setMaximum(1000);

        verticalLayout_2->addWidget(ageFromSB);

        ageTillSB = new QSpinBox(widget);
        ageTillSB->setObjectName(QStringLiteral("ageTillSB"));
        ageTillSB->setMaximum(1000);

        verticalLayout_2->addWidget(ageTillSB);

        weightFromDSB = new QDoubleSpinBox(widget);
        weightFromDSB->setObjectName(QStringLiteral("weightFromDSB"));
        weightFromDSB->setMaximum(11200);

        verticalLayout_2->addWidget(weightFromDSB);

        weightTillDSB = new QDoubleSpinBox(widget);
        weightTillDSB->setObjectName(QStringLiteral("weightTillDSB"));
        weightTillDSB->setMaximum(11200);

        verticalLayout_2->addWidget(weightTillDSB);

        typeCB = new QComboBox(widget);
        typeCB->setObjectName(QStringLiteral("typeCB"));

        verticalLayout_2->addWidget(typeCB);

        durationFightingSB = new QSpinBox(widget);
        durationFightingSB->setObjectName(QStringLiteral("durationFightingSB"));

        verticalLayout_2->addWidget(durationFightingSB);

        durationBreakSB = new QSpinBox(widget);
        durationBreakSB->setObjectName(QStringLiteral("durationBreakSB"));

        verticalLayout_2->addWidget(durationBreakSB);

        roundCountSB = new QSpinBox(widget);
        roundCountSB->setObjectName(QStringLiteral("roundCountSB"));

        verticalLayout_2->addWidget(roundCountSB);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_5->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout_5, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        splitter->addWidget(widget);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        applyBtn = new QPushButton(CreateTournamentCategoriesDialog);
        applyBtn->setObjectName(QStringLiteral("applyBtn"));
        applyBtn->setEnabled(false);

        horizontalLayout_2->addWidget(applyBtn);

        addBtn = new QPushButton(CreateTournamentCategoriesDialog);
        addBtn->setObjectName(QStringLiteral("addBtn"));

        horizontalLayout_2->addWidget(addBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        okBtn = new QPushButton(CreateTournamentCategoriesDialog);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout_2->addWidget(okBtn);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);


        retranslateUi(CreateTournamentCategoriesDialog);

        QMetaObject::connectSlotsByName(CreateTournamentCategoriesDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateTournamentCategoriesDialog)
    {
        CreateTournamentCategoriesDialog->setWindowTitle(QApplication::translate("CreateTournamentCategoriesDialog", "Dialog", 0));
        label_5->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265", 0));
        label_6->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\237\320\276\320\273", 0));
        label->setText(QApplication::translate("CreateTournamentCategoriesDialog", "<html><head/><body><p>\320\222\320\276\320\267\321\200\320\260\321\201\321\202 \320\276\321\202</p></body></html>", 0));
        label_2->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202 \320\264\320\276", 0));
        label_3->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\222\320\265\321\201 \321\201\320\262\321\213\321\210\320\265", 0));
        label_4->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\222\320\265\321\201 \320\264\320\276", 0));
        label_9->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\240\320\260\320\267\320\264\320\265\320\273", 0));
        label_7->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\224\320\273\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \320\261\320\276\321\217", 0));
        label_8->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\237\320\265\321\200\320\265\321\200\321\213\320\262, \321\201\320\265\320\272", 0));
        label_10->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\200\320\260\321\203\320\275\320\264\320\276\320\262", 0));
        applyBtn->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0));
        addBtn->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\216", 0));
        okBtn->setText(QApplication::translate("CreateTournamentCategoriesDialog", "\320\222\321\213\320\271\321\202\320\270", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateTournamentCategoriesDialog: public Ui_CreateTournamentCategoriesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETOURNAMENTCATEGORIESDIALOG_H

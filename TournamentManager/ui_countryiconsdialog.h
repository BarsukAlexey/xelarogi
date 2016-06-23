/********************************************************************************
** Form generated from reading UI file 'countryiconsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COUNTRYICONSDIALOG_H
#define UI_COUNTRYICONSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CountryIconsDialog
{
public:
    QGridLayout *gridLayout_2;
    QLabel *labelLink;
    QVBoxLayout *verticalLayout_3;
    QLabel *tournamentL;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QRadioButton *countryRB;
    QRadioButton *regionRB;
    QRadioButton *regionUnitRB;
    QRadioButton *clubRB;
    QPushButton *closeBtn;
    QTableWidget *entitiesTW;

    void setupUi(QDialog *CountryIconsDialog)
    {
        if (CountryIconsDialog->objectName().isEmpty())
            CountryIconsDialog->setObjectName(QStringLiteral("CountryIconsDialog"));
        CountryIconsDialog->resize(612, 494);
        gridLayout_2 = new QGridLayout(CountryIconsDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        labelLink = new QLabel(CountryIconsDialog);
        labelLink->setObjectName(QStringLiteral("labelLink"));

        gridLayout_2->addWidget(labelLink, 1, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        tournamentL = new QLabel(CountryIconsDialog);
        tournamentL->setObjectName(QStringLiteral("tournamentL"));
        QFont font;
        font.setPointSize(8);
        font.setItalic(true);
        tournamentL->setFont(font);

        verticalLayout_3->addWidget(tournamentL);

        groupBox = new QGroupBox(CountryIconsDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setFlat(false);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        countryRB = new QRadioButton(groupBox);
        countryRB->setObjectName(QStringLiteral("countryRB"));
        countryRB->setChecked(true);

        gridLayout->addWidget(countryRB, 0, 0, 1, 1);

        regionRB = new QRadioButton(groupBox);
        regionRB->setObjectName(QStringLiteral("regionRB"));

        gridLayout->addWidget(regionRB, 0, 1, 1, 1);

        regionUnitRB = new QRadioButton(groupBox);
        regionUnitRB->setObjectName(QStringLiteral("regionUnitRB"));

        gridLayout->addWidget(regionUnitRB, 0, 2, 1, 1);

        clubRB = new QRadioButton(groupBox);
        clubRB->setObjectName(QStringLiteral("clubRB"));

        gridLayout->addWidget(clubRB, 0, 3, 1, 1);


        verticalLayout_3->addWidget(groupBox);


        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 1);

        closeBtn = new QPushButton(CountryIconsDialog);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));

        gridLayout_2->addWidget(closeBtn, 3, 0, 1, 1);

        entitiesTW = new QTableWidget(CountryIconsDialog);
        if (entitiesTW->columnCount() < 3)
            entitiesTW->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        entitiesTW->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        entitiesTW->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        entitiesTW->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        entitiesTW->setObjectName(QStringLiteral("entitiesTW"));
        entitiesTW->setFocusPolicy(Qt::NoFocus);
        entitiesTW->setEditTriggers(QAbstractItemView::NoEditTriggers);
        entitiesTW->setSelectionMode(QAbstractItemView::NoSelection);
        entitiesTW->horizontalHeader()->setHighlightSections(false);
        entitiesTW->horizontalHeader()->setStretchLastSection(true);
        entitiesTW->verticalHeader()->setVisible(false);
        entitiesTW->verticalHeader()->setDefaultSectionSize(55);
        entitiesTW->verticalHeader()->setHighlightSections(false);
        entitiesTW->verticalHeader()->setMinimumSectionSize(55);

        gridLayout_2->addWidget(entitiesTW, 2, 0, 1, 1);


        retranslateUi(CountryIconsDialog);

        QMetaObject::connectSlotsByName(CountryIconsDialog);
    } // setupUi

    void retranslateUi(QDialog *CountryIconsDialog)
    {
        CountryIconsDialog->setWindowTitle(QApplication::translate("CountryIconsDialog", "\320\244\320\273\320\260\320\263\320\270", 0));
        labelLink->setText(QApplication::translate("CountryIconsDialog", "<a href=\"1\">\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \321\204\320\273\320\260\320\263\320\270...</a>", 0));
        tournamentL->setText(QApplication::translate("CountryIconsDialog", "\320\242\321\203\321\200\320\275\320\270\321\200", 0));
        groupBox->setTitle(QString());
        countryRB->setText(QApplication::translate("CountryIconsDialog", "\320\241\321\202\321\200\320\260\320\275\321\213", 0));
        regionRB->setText(QApplication::translate("CountryIconsDialog", "\320\240\320\265\320\263\320\270\320\276\320\275\321\213", 0));
        regionUnitRB->setText(QApplication::translate("CountryIconsDialog", "\320\235\320\260\321\201\320\265\320\273\320\265\320\275\320\275\321\213\320\265 \320\277\321\203\320\275\320\272\321\202\321\213", 0));
        clubRB->setText(QApplication::translate("CountryIconsDialog", "\320\241\320\277\320\276\321\200\321\202\320\270\320\262\320\275\321\213\320\265 \320\272\320\273\321\203\320\261\321\213", 0));
        closeBtn->setText(QApplication::translate("CountryIconsDialog", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0));
        QTableWidgetItem *___qtablewidgetitem = entitiesTW->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CountryIconsDialog", "\320\244\320\273\320\260\320\263", 0));
        QTableWidgetItem *___qtablewidgetitem1 = entitiesTW->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CountryIconsDialog", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265", 0));
    } // retranslateUi

};

namespace Ui {
    class CountryIconsDialog: public Ui_CountryIconsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COUNTRYICONSDIALOG_H

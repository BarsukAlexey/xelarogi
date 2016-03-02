/********************************************************************************
** Form generated from reading UI file 'trophygeneratorsettingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TROPHYGENERATORSETTINGSDIALOG_H
#define UI_TROPHYGENERATORSETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TrophyGeneratorSettingsDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_13;
    QVBoxLayout *verticalLayout_3;
    QComboBox *fullNameRow;
    QComboBox *placeRow;
    QComboBox *sportCategoryRow;
    QComboBox *regionRow;
    QComboBox *tournamentRow;
    QComboBox *typeRow;
    QComboBox *agesRow;
    QComboBox *weightsRow;
    QComboBox *ageRow;
    QComboBox *weightRow;
    QVBoxLayout *verticalLayout_4;
    QComboBox *fullNameColumn;
    QComboBox *placeColumn;
    QComboBox *sportCategoryColumn;
    QComboBox *regionColumn;
    QComboBox *tournamentColumn;
    QComboBox *typeColumn;
    QComboBox *agesColumn;
    QComboBox *weightsColumn;
    QComboBox *ageColumn;
    QComboBox *weightColumn;

    void setupUi(QDialog *TrophyGeneratorSettingsDialog)
    {
        if (TrophyGeneratorSettingsDialog->objectName().isEmpty())
            TrophyGeneratorSettingsDialog->setObjectName(QStringLiteral("TrophyGeneratorSettingsDialog"));
        TrophyGeneratorSettingsDialog->resize(524, 364);
        gridLayout = new QGridLayout(TrophyGeneratorSettingsDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(TrophyGeneratorSettingsDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(TrophyGeneratorSettingsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(TrophyGeneratorSettingsDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_6 = new QLabel(TrophyGeneratorSettingsDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        label_4 = new QLabel(TrophyGeneratorSettingsDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(TrophyGeneratorSettingsDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        label_7 = new QLabel(TrophyGeneratorSettingsDialog);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        label_8 = new QLabel(TrophyGeneratorSettingsDialog);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout->addWidget(label_8);

        label_9 = new QLabel(TrophyGeneratorSettingsDialog);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout->addWidget(label_9);

        label_10 = new QLabel(TrophyGeneratorSettingsDialog);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout->addWidget(label_10);

        label_12 = new QLabel(TrophyGeneratorSettingsDialog);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout->addWidget(label_12);

        label_13 = new QLabel(TrophyGeneratorSettingsDialog);
        label_13->setObjectName(QStringLiteral("label_13"));

        verticalLayout->addWidget(label_13);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        fullNameRow = new QComboBox(TrophyGeneratorSettingsDialog);
        fullNameRow->setObjectName(QStringLiteral("fullNameRow"));

        verticalLayout_3->addWidget(fullNameRow);

        placeRow = new QComboBox(TrophyGeneratorSettingsDialog);
        placeRow->setObjectName(QStringLiteral("placeRow"));

        verticalLayout_3->addWidget(placeRow);

        sportCategoryRow = new QComboBox(TrophyGeneratorSettingsDialog);
        sportCategoryRow->setObjectName(QStringLiteral("sportCategoryRow"));

        verticalLayout_3->addWidget(sportCategoryRow);

        regionRow = new QComboBox(TrophyGeneratorSettingsDialog);
        regionRow->setObjectName(QStringLiteral("regionRow"));

        verticalLayout_3->addWidget(regionRow);

        tournamentRow = new QComboBox(TrophyGeneratorSettingsDialog);
        tournamentRow->setObjectName(QStringLiteral("tournamentRow"));

        verticalLayout_3->addWidget(tournamentRow);

        typeRow = new QComboBox(TrophyGeneratorSettingsDialog);
        typeRow->setObjectName(QStringLiteral("typeRow"));

        verticalLayout_3->addWidget(typeRow);

        agesRow = new QComboBox(TrophyGeneratorSettingsDialog);
        agesRow->setObjectName(QStringLiteral("agesRow"));

        verticalLayout_3->addWidget(agesRow);

        weightsRow = new QComboBox(TrophyGeneratorSettingsDialog);
        weightsRow->setObjectName(QStringLiteral("weightsRow"));

        verticalLayout_3->addWidget(weightsRow);

        ageRow = new QComboBox(TrophyGeneratorSettingsDialog);
        ageRow->setObjectName(QStringLiteral("ageRow"));

        verticalLayout_3->addWidget(ageRow);

        weightRow = new QComboBox(TrophyGeneratorSettingsDialog);
        weightRow->setObjectName(QStringLiteral("weightRow"));

        verticalLayout_3->addWidget(weightRow);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        fullNameColumn = new QComboBox(TrophyGeneratorSettingsDialog);
        fullNameColumn->setObjectName(QStringLiteral("fullNameColumn"));

        verticalLayout_4->addWidget(fullNameColumn);

        placeColumn = new QComboBox(TrophyGeneratorSettingsDialog);
        placeColumn->setObjectName(QStringLiteral("placeColumn"));

        verticalLayout_4->addWidget(placeColumn);

        sportCategoryColumn = new QComboBox(TrophyGeneratorSettingsDialog);
        sportCategoryColumn->setObjectName(QStringLiteral("sportCategoryColumn"));

        verticalLayout_4->addWidget(sportCategoryColumn);

        regionColumn = new QComboBox(TrophyGeneratorSettingsDialog);
        regionColumn->setObjectName(QStringLiteral("regionColumn"));

        verticalLayout_4->addWidget(regionColumn);

        tournamentColumn = new QComboBox(TrophyGeneratorSettingsDialog);
        tournamentColumn->setObjectName(QStringLiteral("tournamentColumn"));

        verticalLayout_4->addWidget(tournamentColumn);

        typeColumn = new QComboBox(TrophyGeneratorSettingsDialog);
        typeColumn->setObjectName(QStringLiteral("typeColumn"));

        verticalLayout_4->addWidget(typeColumn);

        agesColumn = new QComboBox(TrophyGeneratorSettingsDialog);
        agesColumn->setObjectName(QStringLiteral("agesColumn"));

        verticalLayout_4->addWidget(agesColumn);

        weightsColumn = new QComboBox(TrophyGeneratorSettingsDialog);
        weightsColumn->setObjectName(QStringLiteral("weightsColumn"));

        verticalLayout_4->addWidget(weightsColumn);

        ageColumn = new QComboBox(TrophyGeneratorSettingsDialog);
        ageColumn->setObjectName(QStringLiteral("ageColumn"));

        verticalLayout_4->addWidget(ageColumn);

        weightColumn = new QComboBox(TrophyGeneratorSettingsDialog);
        weightColumn->setObjectName(QStringLiteral("weightColumn"));

        verticalLayout_4->addWidget(weightColumn);


        horizontalLayout->addLayout(verticalLayout_4);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(TrophyGeneratorSettingsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TrophyGeneratorSettingsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TrophyGeneratorSettingsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TrophyGeneratorSettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *TrophyGeneratorSettingsDialog)
    {
        TrophyGeneratorSettingsDialog->setWindowTitle(QApplication::translate("TrophyGeneratorSettingsDialog", "\320\236\320\272\320\275\320\276 \320\267\320\260\320\264\320\260\320\275\320\270\321\217 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\320\262 \320\264\320\273\321\217 \320\263\320\265\320\275\320\265\321\200\320\260\321\206\320\270\320\270 \320\263\321\200\320\260\320\274\320\276\321\202", 0));
        label->setText(QApplication::translate("TrophyGeneratorSettingsDialog", "\320\243\320\272\320\260\320\266\320\270\321\202\320\265 \320\262 \320\272\320\260\320\272\320\270\320\265 \321\217\321\207\320\265\320\271\320\272\320\270 \320\267\320\260\320\275\320\265\321\201\321\202\320\270 \321\201\320\276\320\276\321\202\320\262\320\265\321\202\321\201\320\262\321\203\321\216\321\211\320\270\320\265 \320\267\320\260\320\275\321\207\320\265\320\275\320\270\321\217", 0));
        label_2->setText(QApplication::translate("TrophyGeneratorSettingsDialog", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217 \320\270 \320\270\320\274\321\217 \321\201\320\277\320\276\321\200\321\202\321\201\320\274\320\265\320\275\320\260", 0));
        label_6->setText(QApplication::translate("TrophyGeneratorSettingsDialog", "\320\227\320\260\320\275\321\217\321\202\320\276\320\265 \320\274\320\265\321\201\321\202\320\276 \320\275\320\260 \321\202\321\203\321\200\320\275\320\270\321\200\320\265", 0));
        label_4->setText(QApplication::translate("TrophyGeneratorSettingsDialog", "\320\241\320\277\320\276\321\200\321\202\320\270\320\262\320\275\321\213\320\271 \321\200\320\260\320\267\321\200\321\217\320\264", 0));
        label_5->setText(QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\200\320\265\320\263\320\270\320\276\320\275\320\260, \320\267\320\260 \320\272\320\276\321\202\320\276\321\200\321\213\320\271 \320\262\321\213\321\201\321\202\321\203\320\277\320\260\320\273 \321\201\320\277\320\276\321\200\321\202\321\201\320\274\320\265\320\275", 0));
        label_7->setText(QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        label_8->setText(QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\200\320\260\320\267\320\264\320\265\320\273\320\260", 0));
        label_9->setText(QApplication::translate("TrophyGeneratorSettingsDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202\320\275\320\276\320\271 \320\264\320\270\320\260\320\277\320\276\320\267\320\276\320\275 \320\264\320\273\321\217 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270", 0));
        label_10->setText(QApplication::translate("TrophyGeneratorSettingsDialog", "\320\222\320\265\321\201\320\276\320\262\320\276\320\271 \320\264\320\270\320\260\320\277\320\276\320\267\320\276\320\275 \320\264\320\273\321\217 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270", 0));
        label_12->setText(QApplication::translate("TrophyGeneratorSettingsDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202 \321\201\320\277\320\276\321\200\321\201\321\202\320\274\320\265\320\275\320\260", 0));
        label_13->setText(QApplication::translate("TrophyGeneratorSettingsDialog", "\320\222\320\265\321\201 \321\201\320\277\320\276\321\200\321\202\321\201\320\274\320\265\320\275\320\260", 0));
        fullNameRow->clear();
        fullNameRow->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "A", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "B", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "C", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "D", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "E", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "F", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "G", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "H", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "I", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "J", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "K", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "L", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "M", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "N", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "O", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "P", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Q", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "R", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "S", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "T", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "U", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "V", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "W", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "X", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Y", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Z", 0)
        );
        placeRow->clear();
        placeRow->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "A", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "B", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "C", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "D", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "E", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "F", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "G", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "H", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "I", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "J", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "K", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "L", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "M", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "N", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "O", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "P", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Q", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "R", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "S", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "T", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "U", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "V", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "W", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "X", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Y", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Z", 0)
        );
        sportCategoryRow->clear();
        sportCategoryRow->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "A", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "B", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "C", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "D", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "E", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "F", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "G", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "H", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "I", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "J", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "K", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "L", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "M", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "N", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "O", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "P", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Q", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "R", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "S", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "T", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "U", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "V", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "W", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "X", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Y", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Z", 0)
        );
        regionRow->clear();
        regionRow->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "A", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "B", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "C", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "D", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "E", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "F", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "G", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "H", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "I", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "J", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "K", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "L", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "M", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "N", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "O", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "P", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Q", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "R", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "S", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "T", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "U", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "V", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "W", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "X", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Y", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Z", 0)
        );
        tournamentRow->clear();
        tournamentRow->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "A", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "B", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "C", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "D", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "E", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "F", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "G", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "H", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "I", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "J", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "K", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "L", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "M", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "N", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "O", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "P", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Q", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "R", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "S", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "T", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "U", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "V", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "W", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "X", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Y", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Z", 0)
        );
        typeRow->clear();
        typeRow->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "A", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "B", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "C", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "D", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "E", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "F", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "G", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "H", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "I", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "J", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "K", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "L", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "M", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "N", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "O", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "P", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Q", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "R", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "S", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "T", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "U", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "V", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "W", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "X", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Y", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Z", 0)
        );
        agesRow->clear();
        agesRow->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "A", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "B", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "C", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "D", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "E", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "F", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "G", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "H", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "I", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "J", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "K", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "L", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "M", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "N", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "O", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "P", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Q", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "R", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "S", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "T", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "U", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "V", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "W", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "X", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Y", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Z", 0)
        );
        weightsRow->clear();
        weightsRow->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "A", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "B", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "C", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "D", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "E", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "F", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "G", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "H", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "I", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "J", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "K", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "L", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "M", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "N", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "O", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "P", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Q", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "R", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "S", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "T", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "U", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "V", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "W", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "X", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Y", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Z", 0)
        );
        ageRow->clear();
        ageRow->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "A", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "B", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "C", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "D", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "E", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "F", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "G", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "H", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "I", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "J", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "K", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "L", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "M", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "N", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "O", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "P", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Q", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "R", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "S", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "T", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "U", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "V", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "W", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "X", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Y", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Z", 0)
        );
        weightRow->clear();
        weightRow->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "A", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "B", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "C", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "D", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "E", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "F", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "G", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "H", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "I", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "J", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "K", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "L", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "M", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "N", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "O", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "P", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Q", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "R", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "S", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "T", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "U", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "V", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "W", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "X", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Y", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "Z", 0)
        );
        fullNameColumn->clear();
        fullNameColumn->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "1", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "2", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "3", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "4", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "5", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "6", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "7", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "8", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "9", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "10", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "11", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "12", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "13", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "14", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "15", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "16", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "17", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "18", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "19", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "20", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "21", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "22", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "23", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "24", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "25", 0)
        );
        placeColumn->clear();
        placeColumn->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "1", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "2", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "3", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "4", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "5", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "6", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "7", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "8", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "9", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "10", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "11", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "12", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "13", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "14", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "15", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "16", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "17", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "18", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "19", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "20", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "21", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "22", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "23", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "24", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "25", 0)
        );
        sportCategoryColumn->clear();
        sportCategoryColumn->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "1", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "2", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "3", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "4", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "5", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "6", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "7", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "8", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "9", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "10", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "11", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "12", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "13", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "14", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "15", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "16", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "17", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "18", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "19", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "20", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "21", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "22", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "23", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "24", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "25", 0)
        );
        regionColumn->clear();
        regionColumn->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "1", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "2", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "3", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "4", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "5", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "6", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "7", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "8", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "9", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "10", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "11", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "12", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "13", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "14", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "15", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "16", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "17", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "18", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "19", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "20", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "21", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "22", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "23", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "24", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "25", 0)
        );
        tournamentColumn->clear();
        tournamentColumn->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "1", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "2", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "3", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "4", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "5", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "6", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "7", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "8", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "9", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "10", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "11", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "12", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "13", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "14", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "15", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "16", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "17", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "18", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "19", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "20", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "21", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "22", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "23", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "24", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "25", 0)
        );
        typeColumn->clear();
        typeColumn->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "1", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "2", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "3", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "4", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "5", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "6", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "7", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "8", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "9", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "10", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "11", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "12", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "13", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "14", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "15", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "16", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "17", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "18", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "19", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "20", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "21", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "22", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "23", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "24", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "25", 0)
        );
        agesColumn->clear();
        agesColumn->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "1", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "2", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "3", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "4", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "5", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "6", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "7", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "8", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "9", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "10", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "11", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "12", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "13", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "14", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "15", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "16", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "17", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "18", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "19", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "20", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "21", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "22", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "23", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "24", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "25", 0)
        );
        weightsColumn->clear();
        weightsColumn->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "1", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "2", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "3", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "4", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "5", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "6", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "7", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "8", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "9", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "10", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "11", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "12", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "13", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "14", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "15", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "16", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "17", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "18", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "19", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "20", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "21", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "22", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "23", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "24", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "25", 0)
        );
        ageColumn->clear();
        ageColumn->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "1", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "2", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "3", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "4", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "5", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "6", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "7", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "8", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "9", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "10", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "11", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "12", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "13", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "14", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "15", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "16", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "17", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "18", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "19", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "20", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "21", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "22", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "23", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "24", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "25", 0)
        );
        weightColumn->clear();
        weightColumn->insertItems(0, QStringList()
         << QApplication::translate("TrophyGeneratorSettingsDialog", "\320\235\320\265 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\202\321\201\321\217", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "1", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "2", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "3", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "4", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "5", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "6", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "7", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "8", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "9", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "10", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "11", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "12", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "13", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "14", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "15", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "16", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "17", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "18", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "19", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "20", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "21", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "22", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "23", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "24", 0)
         << QApplication::translate("TrophyGeneratorSettingsDialog", "25", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class TrophyGeneratorSettingsDialog: public Ui_TrophyGeneratorSettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TROPHYGENERATORSETTINGSDIALOG_H

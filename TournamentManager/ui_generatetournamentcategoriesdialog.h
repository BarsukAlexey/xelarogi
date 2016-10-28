/********************************************************************************
** Form generated from reading UI file 'generatetournamentcategoriesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATETOURNAMENTCATEGORIESDIALOG_H
#define UI_GENERATETOURNAMENTCATEGORIESDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GenerateTournamentCategoriesDialog
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QSpinBox *ageFromSB;
    QLineEdit *lineEditAgeTill;
    QLabel *label_4;
    QLineEdit *lineEditTypeAge;
    QLabel *label_15;
    QLineEdit *lineEditAgeFrom;
    QSpinBox *ageTillSB;
    QLabel *label_5;
    QLineEdit *lineEditTypeAge_2;
    QLabel *label_16;
    QLineEdit *lineEditTypeAge_3;
    QLabel *label_17;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *sexCB;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonAddAgeCategory;
    QComboBox *comboBoxAgeCategory;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QComboBox *typeCB;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *label_12;
    QVBoxLayout *verticalLayout_5;
    QSpinBox *duratiobFightingSB;
    QSpinBox *durationBreakSB;
    QSpinBox *roundCountSB;
    QComboBox *comboBoxTie;
    QSpinBox *spinBoxExtraRound;
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEditWeightTill;
    QLabel *label_6;
    QLineEdit *lineEditTypeWeight_2;
    QLineEdit *lineEditWeightFrom;
    QLabel *label_14;
    QLineEdit *lineEditTypeWeight_3;
    QLineEdit *lineEditTypeWeight;
    QLineEdit *weightsLE;

    void setupUi(QDialog *GenerateTournamentCategoriesDialog)
    {
        if (GenerateTournamentCategoriesDialog->objectName().isEmpty())
            GenerateTournamentCategoriesDialog->setObjectName(QStringLiteral("GenerateTournamentCategoriesDialog"));
        GenerateTournamentCategoriesDialog->resize(448, 607);
        gridLayout_2 = new QGridLayout(GenerateTournamentCategoriesDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        groupBox_2 = new QGroupBox(GenerateTournamentCategoriesDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        ageFromSB = new QSpinBox(groupBox_2);
        ageFromSB->setObjectName(QStringLiteral("ageFromSB"));
        ageFromSB->setMaximum(9999);

        gridLayout_3->addWidget(ageFromSB, 0, 1, 1, 1);

        lineEditAgeTill = new QLineEdit(groupBox_2);
        lineEditAgeTill->setObjectName(QStringLiteral("lineEditAgeTill"));

        gridLayout_3->addWidget(lineEditAgeTill, 1, 0, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        lineEditTypeAge = new QLineEdit(groupBox_2);
        lineEditTypeAge->setObjectName(QStringLiteral("lineEditTypeAge"));

        gridLayout_3->addWidget(lineEditTypeAge, 0, 4, 1, 1);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_15, 1, 1, 1, 2);

        lineEditAgeFrom = new QLineEdit(groupBox_2);
        lineEditAgeFrom->setObjectName(QStringLiteral("lineEditAgeFrom"));

        gridLayout_3->addWidget(lineEditAgeFrom, 2, 0, 1, 1);

        ageTillSB = new QSpinBox(groupBox_2);
        ageTillSB->setObjectName(QStringLiteral("ageTillSB"));
        ageTillSB->setMinimum(1);
        ageTillSB->setMaximum(99);
        ageTillSB->setValue(1);

        gridLayout_3->addWidget(ageTillSB, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_5, 0, 2, 1, 1);

        lineEditTypeAge_2 = new QLineEdit(groupBox_2);
        lineEditTypeAge_2->setObjectName(QStringLiteral("lineEditTypeAge_2"));
        lineEditTypeAge_2->setEnabled(false);
        lineEditTypeAge_2->setReadOnly(true);

        gridLayout_3->addWidget(lineEditTypeAge_2, 1, 4, 1, 1);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_16, 2, 1, 1, 2);

        lineEditTypeAge_3 = new QLineEdit(groupBox_2);
        lineEditTypeAge_3->setObjectName(QStringLiteral("lineEditTypeAge_3"));
        lineEditTypeAge_3->setEnabled(false);
        lineEditTypeAge_3->setReadOnly(true);

        gridLayout_3->addWidget(lineEditTypeAge_3, 2, 4, 1, 1);

        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setWordWrap(true);

        gridLayout_3->addWidget(label_17, 3, 0, 1, 5);


        gridLayout_2->addWidget(groupBox_2, 1, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_3 = new QLabel(GenerateTournamentCategoriesDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_3);

        label = new QLabel(GenerateTournamentCategoriesDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(GenerateTournamentCategoriesDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_2);


        horizontalLayout_5->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        sexCB = new QComboBox(GenerateTournamentCategoriesDialog);
        sexCB->setObjectName(QStringLiteral("sexCB"));
        sexCB->setMaxVisibleItems(20);

        verticalLayout_2->addWidget(sexCB);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButtonAddAgeCategory = new QPushButton(GenerateTournamentCategoriesDialog);
        pushButtonAddAgeCategory->setObjectName(QStringLiteral("pushButtonAddAgeCategory"));
        pushButtonAddAgeCategory->setMaximumSize(QSize(24, 16777215));

        horizontalLayout_4->addWidget(pushButtonAddAgeCategory);

        comboBoxAgeCategory = new QComboBox(GenerateTournamentCategoriesDialog);
        comboBoxAgeCategory->setObjectName(QStringLiteral("comboBoxAgeCategory"));

        horizontalLayout_4->addWidget(comboBoxAgeCategory);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton = new QPushButton(GenerateTournamentCategoriesDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(24, 16777215));

        horizontalLayout_2->addWidget(pushButton);

        typeCB = new QComboBox(GenerateTournamentCategoriesDialog);
        typeCB->setObjectName(QStringLiteral("typeCB"));
        typeCB->setMaxVisibleItems(20);

        horizontalLayout_2->addWidget(typeCB);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_5->addLayout(verticalLayout_2);


        gridLayout_2->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_9 = new QLabel(GenerateTournamentCategoriesDialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_4->addWidget(label_9);

        label_10 = new QLabel(GenerateTournamentCategoriesDialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_4->addWidget(label_10);

        label_11 = new QLabel(GenerateTournamentCategoriesDialog);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_4->addWidget(label_11);

        label_13 = new QLabel(GenerateTournamentCategoriesDialog);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_4->addWidget(label_13);

        label_12 = new QLabel(GenerateTournamentCategoriesDialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_4->addWidget(label_12);


        horizontalLayout_3->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        duratiobFightingSB = new QSpinBox(GenerateTournamentCategoriesDialog);
        duratiobFightingSB->setObjectName(QStringLiteral("duratiobFightingSB"));
        duratiobFightingSB->setMinimum(15);
        duratiobFightingSB->setMaximum(9999999);
        duratiobFightingSB->setValue(120);

        verticalLayout_5->addWidget(duratiobFightingSB);

        durationBreakSB = new QSpinBox(GenerateTournamentCategoriesDialog);
        durationBreakSB->setObjectName(QStringLiteral("durationBreakSB"));
        durationBreakSB->setMinimum(10);
        durationBreakSB->setMaximum(9999999);
        durationBreakSB->setValue(60);

        verticalLayout_5->addWidget(durationBreakSB);

        roundCountSB = new QSpinBox(GenerateTournamentCategoriesDialog);
        roundCountSB->setObjectName(QStringLiteral("roundCountSB"));
        roundCountSB->setMinimum(1);
        roundCountSB->setValue(3);

        verticalLayout_5->addWidget(roundCountSB);

        comboBoxTie = new QComboBox(GenerateTournamentCategoriesDialog);
        comboBoxTie->setObjectName(QStringLiteral("comboBoxTie"));

        verticalLayout_5->addWidget(comboBoxTie);

        spinBoxExtraRound = new QSpinBox(GenerateTournamentCategoriesDialog);
        spinBoxExtraRound->setObjectName(QStringLiteral("spinBoxExtraRound"));
        spinBoxExtraRound->setMinimum(5);
        spinBoxExtraRound->setMaximum(100500);

        verticalLayout_5->addWidget(spinBoxExtraRound);


        horizontalLayout_3->addLayout(verticalLayout_5);


        gridLayout_2->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        buttonBox = new QDialogButtonBox(GenerateTournamentCategoriesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 4, 0, 1, 1);

        groupBox = new QGroupBox(GenerateTournamentCategoriesDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_7, 0, 0, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        QFont font;
        font.setPointSize(7);
        font.setItalic(true);
        label_8->setFont(font);

        gridLayout->addWidget(label_8, 2, 0, 1, 1);

        lineEditWeightTill = new QLineEdit(groupBox);
        lineEditWeightTill->setObjectName(QStringLiteral("lineEditWeightTill"));

        gridLayout->addWidget(lineEditWeightTill, 3, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 3, 1, 1, 1);

        lineEditTypeWeight_2 = new QLineEdit(groupBox);
        lineEditTypeWeight_2->setObjectName(QStringLiteral("lineEditTypeWeight_2"));
        lineEditTypeWeight_2->setEnabled(false);
        lineEditTypeWeight_2->setReadOnly(true);

        gridLayout->addWidget(lineEditTypeWeight_2, 3, 2, 1, 1);

        lineEditWeightFrom = new QLineEdit(groupBox);
        lineEditWeightFrom->setObjectName(QStringLiteral("lineEditWeightFrom"));

        gridLayout->addWidget(lineEditWeightFrom, 4, 0, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 4, 1, 1, 1);

        lineEditTypeWeight_3 = new QLineEdit(groupBox);
        lineEditTypeWeight_3->setObjectName(QStringLiteral("lineEditTypeWeight_3"));
        lineEditTypeWeight_3->setEnabled(false);
        lineEditTypeWeight_3->setReadOnly(true);

        gridLayout->addWidget(lineEditTypeWeight_3, 4, 2, 1, 1);

        lineEditTypeWeight = new QLineEdit(groupBox);
        lineEditTypeWeight->setObjectName(QStringLiteral("lineEditTypeWeight"));

        gridLayout->addWidget(lineEditTypeWeight, 1, 2, 1, 1);

        weightsLE = new QLineEdit(groupBox);
        weightsLE->setObjectName(QStringLiteral("weightsLE"));

        gridLayout->addWidget(weightsLE, 1, 0, 1, 2);


        gridLayout_2->addWidget(groupBox, 2, 0, 1, 1);

        buttonBox->raise();
        groupBox->raise();
        groupBox_2->raise();
        QWidget::setTabOrder(sexCB, pushButtonAddAgeCategory);
        QWidget::setTabOrder(pushButtonAddAgeCategory, comboBoxAgeCategory);
        QWidget::setTabOrder(comboBoxAgeCategory, pushButton);
        QWidget::setTabOrder(pushButton, typeCB);
        QWidget::setTabOrder(typeCB, ageFromSB);
        QWidget::setTabOrder(ageFromSB, ageTillSB);
        QWidget::setTabOrder(ageTillSB, lineEditTypeAge);
        QWidget::setTabOrder(lineEditTypeAge, lineEditAgeTill);
        QWidget::setTabOrder(lineEditAgeTill, lineEditTypeAge_2);
        QWidget::setTabOrder(lineEditTypeAge_2, lineEditAgeFrom);
        QWidget::setTabOrder(lineEditAgeFrom, lineEditTypeAge_3);
        QWidget::setTabOrder(lineEditTypeAge_3, weightsLE);
        QWidget::setTabOrder(weightsLE, lineEditTypeWeight);
        QWidget::setTabOrder(lineEditTypeWeight, lineEditWeightTill);
        QWidget::setTabOrder(lineEditWeightTill, lineEditTypeWeight_2);
        QWidget::setTabOrder(lineEditTypeWeight_2, lineEditWeightFrom);
        QWidget::setTabOrder(lineEditWeightFrom, lineEditTypeWeight_3);
        QWidget::setTabOrder(lineEditTypeWeight_3, duratiobFightingSB);
        QWidget::setTabOrder(duratiobFightingSB, durationBreakSB);
        QWidget::setTabOrder(durationBreakSB, roundCountSB);
        QWidget::setTabOrder(roundCountSB, comboBoxTie);
        QWidget::setTabOrder(comboBoxTie, spinBoxExtraRound);

        retranslateUi(GenerateTournamentCategoriesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), GenerateTournamentCategoriesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GenerateTournamentCategoriesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(GenerateTournamentCategoriesDialog);
    } // setupUi

    void retranslateUi(QDialog *GenerateTournamentCategoriesDialog)
    {
        GenerateTournamentCategoriesDialog->setWindowTitle(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\271 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        groupBox_2->setTitle(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202", 0));
        lineEditAgeTill->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\264\320\276", 0));
        label_4->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202 \320\276\321\202", 0));
        lineEditTypeAge->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\273\320\265\321\202", 0));
        label_15->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "5", 0));
        lineEditAgeFrom->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\276\321\202", 0));
        label_5->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\273\320\265\321\202 \320\264\320\276", 0));
        lineEditTypeAge_2->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\273\320\265\321\202", 0));
        label_16->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "35", 0));
        lineEditTypeAge_3->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\273\320\265\321\202", 0));
        label_17->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "<html><head/><body><p>\320\225\321\201\320\273\320\270 \321\203\320\272\320\260\320\267\320\260\321\202\321\214, \320\275\320\260\320\277\321\200\320\270\320\274\320\265\321\200, \320\264\320\270\320\260\320\277\320\260\320\267\320\276\320\275 \320\276\321\202 0 \320\264\320\276 5 \320\273\320\265\321\202, \321\202\320\276 \321\202\320\276\320\263\320\264\320\260 \320\261\321\203\320\264\320\265\321\202 \320\276\320\261\320\276\320\261\321\200\320\260\320\266\320\260\321\202\321\214\321\201\321\217 &quot;\320\264\320\276 7 \320\273\320\265\321\202&quot;</p><p>\320\225\321\201\320\273\320\270 \320\276\321\202 35 \320\273\320\265\321\202 \320\264\320\276 99 \320\273\320\265\321\202, \321\202\320\276 &quot;\320\276\321\202 35 \320\273\320\265\321\202&quot;</p><p>\320\225\321\201\320\273\320\270 \320\276\321\202 18 \320\264\320\276 23 \320\273\320\265\321\202, \321\202\320\276 &quot;18-23 \320\273\320\265\321\202&quot;</p></body></html>", 0));
        label_3->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\237\320\276\320\273", 0));
        label->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202\320\275\320\260\321\217 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217", 0));
        label_2->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\240\320\260\320\267\320\264\320\265\320\273", 0));
        pushButtonAddAgeCategory->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "+", 0));
        pushButton->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "+", 0));
        label_9->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \321\200\320\260\321\203\320\275\320\264\320\260 (\320\262 \321\201\320\265\320\272.)", 0));
        label_10->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \320\277\320\265\321\200\320\265\321\200\321\213\320\262\320\260 (\320\262 \321\201\320\265\320\272.)", 0));
        label_11->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\200\320\260\321\203\320\275\320\264\320\276\320\262", 0));
        label_13->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222 \321\201\320\273\321\203\321\207\320\260\320\265 \320\275\320\270\321\207\321\214\320\270", 0));
        label_12->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222\321\200\320\265\320\274\321\217 \320\264\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\321\214\320\273\320\275\320\276 \321\200\320\260\321\203\320\275\320\264\320\260 (\320\262 \321\201\320\265\320\272\321\203\320\275\320\264\320\260\321\205)", 0));
        groupBox->setTitle(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222\320\265\321\201", 0));
        label_7->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\223\321\200\320\260\320\275\320\270\321\207\320\275\321\213\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217 \320\262\320\265\321\201\320\260", 0));
        label_8->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\321\200\320\260\320\267\320\264\320\265\320\273\321\217\320\271\321\202\320\265 \320\262\320\265\320\273\320\270\321\207\320\270\320\275\321\213 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\274 \";\" (\321\202\320\276\321\207\320\272\320\260 \321\201 \320\267\320\260\320\277\321\217\321\202\320\276\320\271)", 0));
        lineEditWeightTill->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\264\320\276", 0));
        label_6->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "15", 0));
        lineEditTypeWeight_2->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\272\320\263", 0));
        lineEditWeightFrom->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\321\201\320\262\321\213\321\210\320\265", 0));
        label_14->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "80", 0));
        lineEditTypeWeight_3->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\272\320\263", 0));
        lineEditTypeWeight->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\272\320\263", 0));
        weightsLE->setPlaceholderText(QApplication::translate("GenerateTournamentCategoriesDialog", "15;20;35.5;40;48;61.5;80", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateTournamentCategoriesDialog: public Ui_GenerateTournamentCategoriesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATETOURNAMENTCATEGORIESDIALOG_H

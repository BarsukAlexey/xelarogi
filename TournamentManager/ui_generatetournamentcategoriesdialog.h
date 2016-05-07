/********************************************************************************
** Form generated from reading UI file 'generatetournamentcategoriesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GenerateTournamentCategoriesDialog
{
public:
    QVBoxLayout *verticalLayout_6;
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
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QSpinBox *ageFromSB;
    QLabel *label_5;
    QSpinBox *ageTillSB;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_7;
    QLineEdit *weightsLE;
    QLabel *label_8;
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

    void setupUi(QDialog *GenerateTournamentCategoriesDialog)
    {
        if (GenerateTournamentCategoriesDialog->objectName().isEmpty())
            GenerateTournamentCategoriesDialog->setObjectName(QStringLiteral("GenerateTournamentCategoriesDialog"));
        GenerateTournamentCategoriesDialog->setEnabled(true);
        GenerateTournamentCategoriesDialog->resize(437, 511);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GenerateTournamentCategoriesDialog->sizePolicy().hasHeightForWidth());
        GenerateTournamentCategoriesDialog->setSizePolicy(sizePolicy);
        GenerateTournamentCategoriesDialog->setMinimumSize(QSize(304, 311));
        verticalLayout_6 = new QVBoxLayout(GenerateTournamentCategoriesDialog);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
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


        verticalLayout_6->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_4 = new QLabel(GenerateTournamentCategoriesDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        ageFromSB = new QSpinBox(GenerateTournamentCategoriesDialog);
        ageFromSB->setObjectName(QStringLiteral("ageFromSB"));
        ageFromSB->setMaximum(9999);

        horizontalLayout->addWidget(ageFromSB);

        label_5 = new QLabel(GenerateTournamentCategoriesDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);

        ageTillSB = new QSpinBox(GenerateTournamentCategoriesDialog);
        ageTillSB->setObjectName(QStringLiteral("ageTillSB"));
        ageTillSB->setMinimum(1);
        ageTillSB->setMaximum(99);
        ageTillSB->setValue(1);

        horizontalLayout->addWidget(ageTillSB);

        label_6 = new QLabel(GenerateTournamentCategoriesDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout->addWidget(label_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_6->addLayout(horizontalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_7 = new QLabel(GenerateTournamentCategoriesDialog);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_3->addWidget(label_7);

        weightsLE = new QLineEdit(GenerateTournamentCategoriesDialog);
        weightsLE->setObjectName(QStringLiteral("weightsLE"));

        verticalLayout_3->addWidget(weightsLE);

        label_8 = new QLabel(GenerateTournamentCategoriesDialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        QFont font;
        font.setPointSize(7);
        font.setItalic(true);
        label_8->setFont(font);

        verticalLayout_3->addWidget(label_8);


        verticalLayout_6->addLayout(verticalLayout_3);

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


        verticalLayout_6->addLayout(horizontalLayout_3);

        buttonBox = new QDialogButtonBox(GenerateTournamentCategoriesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_6->addWidget(buttonBox);

        buttonBox->raise();
        label_12->raise();
        label_13->raise();
        label_9->raise();
        label_10->raise();
        label_11->raise();
        duratiobFightingSB->raise();
        roundCountSB->raise();
        durationBreakSB->raise();
        comboBoxTie->raise();
        spinBoxExtraRound->raise();

        retranslateUi(GenerateTournamentCategoriesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), GenerateTournamentCategoriesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GenerateTournamentCategoriesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(GenerateTournamentCategoriesDialog);
    } // setupUi

    void retranslateUi(QDialog *GenerateTournamentCategoriesDialog)
    {
        GenerateTournamentCategoriesDialog->setWindowTitle(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\271 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        label_3->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\237\320\276\320\273", 0));
        label->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202\320\275\320\260\321\217 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217", 0));
        label_2->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\240\320\260\320\267\320\264\320\265\320\273", 0));
        pushButtonAddAgeCategory->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "+", 0));
        pushButton->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "+", 0));
        label_4->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202 \320\276\321\202", 0));
        label_5->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\273\320\265\321\202 \320\264\320\276", 0));
        label_6->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\273\320\265\321\202", 0));
        label_7->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\223\321\200\320\260\320\275\320\270\321\207\320\275\321\213\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217 \320\262\320\265\321\201\320\260", 0));
        weightsLE->setPlaceholderText(QApplication::translate("GenerateTournamentCategoriesDialog", "15;20;35.5;40;48;61.5;80", 0));
        label_8->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\321\200\320\260\320\267\320\264\320\265\320\273\321\217\320\271\321\202\320\265 \320\262\320\265\320\273\320\270\321\207\320\270\320\275\321\213 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\274 \";\" (\321\202\320\276\321\207\320\272\320\260 \321\201 \320\267\320\260\320\277\321\217\321\202\320\276\320\271)", 0));
        label_9->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \321\200\320\260\321\203\320\275\320\264\320\260 (\320\262 \321\201\320\265\320\272.)", 0));
        label_10->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \320\277\320\265\321\200\320\265\321\200\321\213\320\262\320\260 (\320\262 \321\201\320\265\320\272.)", 0));
        label_11->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\200\320\260\321\203\320\275\320\264\320\276\320\262", 0));
        label_13->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222 \321\201\320\273\321\203\321\207\320\260\320\265 \320\275\320\270\321\207\321\214\320\270", 0));
        label_12->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222\321\200\320\265\320\274\321\217 \320\264\320\276\320\277\320\276\320\273\320\275\320\270\321\202\320\265\321\214\320\273\320\275\320\276 \321\200\320\260\321\203\320\275\320\264\320\260 (\320\262 \321\201\320\265\320\272\321\203\320\275\320\264\320\260\321\205)", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateTournamentCategoriesDialog: public Ui_GenerateTournamentCategoriesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATETOURNAMENTCATEGORIESDIALOG_H

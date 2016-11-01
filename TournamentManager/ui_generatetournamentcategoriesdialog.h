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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
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
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonAddType;
    QComboBox *typeCB;
    QLabel *label_3;
    QComboBox *sexCB;
    QLabel *label;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButtonAddAgeCategory;
    QComboBox *comboBoxAgeCategory;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QSpinBox *ageFromSB;
    QLabel *label_5;
    QSpinBox *ageTillSB;
    QLineEdit *lineEditTypeAge;
    QLineEdit *lineEditAgeTill;
    QLineEdit *lineEditAgeFrom;
    QLabel *label_17;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QLineEdit *weightsLE;
    QLineEdit *lineEditTypeWeight;
    QLineEdit *lineEditWeightTill;
    QLineEdit *lineEditWeightFrom;
    QFormLayout *formLayout_2;
    QLabel *label_11;
    QSpinBox *roundCountSB;
    QLabel *label_9;
    QSpinBox *duratiobFightingSB;
    QLabel *label_10;
    QSpinBox *durationBreakSB;
    QLabel *label_13;
    QComboBox *comboBoxTie;
    QLabel *label_12;
    QSpinBox *spinBoxExtraRound;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GenerateTournamentCategoriesDialog)
    {
        if (GenerateTournamentCategoriesDialog->objectName().isEmpty())
            GenerateTournamentCategoriesDialog->setObjectName(QStringLiteral("GenerateTournamentCategoriesDialog"));
        GenerateTournamentCategoriesDialog->resize(450, 617);
        verticalLayout = new QVBoxLayout(GenerateTournamentCategoriesDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_2 = new QLabel(GenerateTournamentCategoriesDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonAddType = new QPushButton(GenerateTournamentCategoriesDialog);
        pushButtonAddType->setObjectName(QStringLiteral("pushButtonAddType"));
        pushButtonAddType->setMaximumSize(QSize(24, 16777215));

        horizontalLayout->addWidget(pushButtonAddType);

        typeCB = new QComboBox(GenerateTournamentCategoriesDialog);
        typeCB->setObjectName(QStringLiteral("typeCB"));
        typeCB->setMaxVisibleItems(20);

        horizontalLayout->addWidget(typeCB);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout);

        label_3 = new QLabel(GenerateTournamentCategoriesDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        sexCB = new QComboBox(GenerateTournamentCategoriesDialog);
        sexCB->setObjectName(QStringLiteral("sexCB"));
        sexCB->setMaxVisibleItems(20);

        formLayout->setWidget(1, QFormLayout::FieldRole, sexCB);

        label = new QLabel(GenerateTournamentCategoriesDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButtonAddAgeCategory = new QPushButton(GenerateTournamentCategoriesDialog);
        pushButtonAddAgeCategory->setObjectName(QStringLiteral("pushButtonAddAgeCategory"));
        pushButtonAddAgeCategory->setMaximumSize(QSize(24, 16777215));

        horizontalLayout_4->addWidget(pushButtonAddAgeCategory);

        comboBoxAgeCategory = new QComboBox(GenerateTournamentCategoriesDialog);
        comboBoxAgeCategory->setObjectName(QStringLiteral("comboBoxAgeCategory"));

        horizontalLayout_4->addWidget(comboBoxAgeCategory);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_4);


        verticalLayout->addLayout(formLayout);

        groupBox_2 = new QGroupBox(GenerateTournamentCategoriesDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_4);

        ageFromSB = new QSpinBox(groupBox_2);
        ageFromSB->setObjectName(QStringLiteral("ageFromSB"));
        ageFromSB->setMaximum(99);

        horizontalLayout_2->addWidget(ageFromSB);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_5);

        ageTillSB = new QSpinBox(groupBox_2);
        ageTillSB->setObjectName(QStringLiteral("ageTillSB"));
        ageTillSB->setMinimum(1);
        ageTillSB->setMaximum(99);
        ageTillSB->setValue(1);

        horizontalLayout_2->addWidget(ageTillSB);

        lineEditTypeAge = new QLineEdit(groupBox_2);
        lineEditTypeAge->setObjectName(QStringLiteral("lineEditTypeAge"));

        horizontalLayout_2->addWidget(lineEditTypeAge);


        verticalLayout_2->addLayout(horizontalLayout_2);

        lineEditAgeTill = new QLineEdit(groupBox_2);
        lineEditAgeTill->setObjectName(QStringLiteral("lineEditAgeTill"));

        verticalLayout_2->addWidget(lineEditAgeTill);

        lineEditAgeFrom = new QLineEdit(groupBox_2);
        lineEditAgeFrom->setObjectName(QStringLiteral("lineEditAgeFrom"));

        verticalLayout_2->addWidget(lineEditAgeFrom);

        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setWordWrap(true);

        verticalLayout_2->addWidget(label_17);


        verticalLayout->addWidget(groupBox_2);

        groupBox = new QGroupBox(GenerateTournamentCategoriesDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_7);

        weightsLE = new QLineEdit(groupBox);
        weightsLE->setObjectName(QStringLiteral("weightsLE"));

        horizontalLayout_3->addWidget(weightsLE);

        lineEditTypeWeight = new QLineEdit(groupBox);
        lineEditTypeWeight->setObjectName(QStringLiteral("lineEditTypeWeight"));

        horizontalLayout_3->addWidget(lineEditTypeWeight);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        lineEditWeightTill = new QLineEdit(groupBox);
        lineEditWeightTill->setObjectName(QStringLiteral("lineEditWeightTill"));

        gridLayout->addWidget(lineEditWeightTill, 1, 0, 1, 1);

        lineEditWeightFrom = new QLineEdit(groupBox);
        lineEditWeightFrom->setObjectName(QStringLiteral("lineEditWeightFrom"));

        gridLayout->addWidget(lineEditWeightFrom, 2, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_11 = new QLabel(GenerateTournamentCategoriesDialog);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_11);

        roundCountSB = new QSpinBox(GenerateTournamentCategoriesDialog);
        roundCountSB->setObjectName(QStringLiteral("roundCountSB"));
        roundCountSB->setMinimum(1);
        roundCountSB->setValue(3);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, roundCountSB);

        label_9 = new QLabel(GenerateTournamentCategoriesDialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_9);

        duratiobFightingSB = new QSpinBox(GenerateTournamentCategoriesDialog);
        duratiobFightingSB->setObjectName(QStringLiteral("duratiobFightingSB"));
        duratiobFightingSB->setMinimum(15);
        duratiobFightingSB->setMaximum(9999999);
        duratiobFightingSB->setValue(120);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, duratiobFightingSB);

        label_10 = new QLabel(GenerateTournamentCategoriesDialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_10);

        durationBreakSB = new QSpinBox(GenerateTournamentCategoriesDialog);
        durationBreakSB->setObjectName(QStringLiteral("durationBreakSB"));
        durationBreakSB->setMinimum(10);
        durationBreakSB->setMaximum(9999999);
        durationBreakSB->setValue(60);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, durationBreakSB);

        label_13 = new QLabel(GenerateTournamentCategoriesDialog);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_13);

        comboBoxTie = new QComboBox(GenerateTournamentCategoriesDialog);
        comboBoxTie->setObjectName(QStringLiteral("comboBoxTie"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, comboBoxTie);

        label_12 = new QLabel(GenerateTournamentCategoriesDialog);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_12);

        spinBoxExtraRound = new QSpinBox(GenerateTournamentCategoriesDialog);
        spinBoxExtraRound->setObjectName(QStringLiteral("spinBoxExtraRound"));
        spinBoxExtraRound->setMinimum(5);
        spinBoxExtraRound->setMaximum(100500);
        spinBoxExtraRound->setValue(30);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, spinBoxExtraRound);


        verticalLayout->addLayout(formLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(GenerateTournamentCategoriesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        buttonBox->raise();
        groupBox->raise();
        groupBox_2->raise();
        QWidget::setTabOrder(typeCB, sexCB);
        QWidget::setTabOrder(sexCB, pushButtonAddAgeCategory);
        QWidget::setTabOrder(pushButtonAddAgeCategory, comboBoxAgeCategory);
        QWidget::setTabOrder(comboBoxAgeCategory, ageFromSB);
        QWidget::setTabOrder(ageFromSB, ageTillSB);
        QWidget::setTabOrder(ageTillSB, lineEditTypeAge);
        QWidget::setTabOrder(lineEditTypeAge, lineEditAgeTill);
        QWidget::setTabOrder(lineEditAgeTill, lineEditAgeFrom);
        QWidget::setTabOrder(lineEditAgeFrom, weightsLE);
        QWidget::setTabOrder(weightsLE, lineEditTypeWeight);
        QWidget::setTabOrder(lineEditTypeWeight, lineEditWeightTill);
        QWidget::setTabOrder(lineEditWeightTill, lineEditWeightFrom);
        QWidget::setTabOrder(lineEditWeightFrom, roundCountSB);
        QWidget::setTabOrder(roundCountSB, duratiobFightingSB);
        QWidget::setTabOrder(duratiobFightingSB, durationBreakSB);
        QWidget::setTabOrder(durationBreakSB, comboBoxTie);
        QWidget::setTabOrder(comboBoxTie, spinBoxExtraRound);

        retranslateUi(GenerateTournamentCategoriesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), GenerateTournamentCategoriesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GenerateTournamentCategoriesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(GenerateTournamentCategoriesDialog);
    } // setupUi

    void retranslateUi(QDialog *GenerateTournamentCategoriesDialog)
    {
        GenerateTournamentCategoriesDialog->setWindowTitle(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\271 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        label_2->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\240\320\260\320\267\320\264\320\265\320\273", 0));
        pushButtonAddType->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "+", 0));
        label_3->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\237\320\276\320\273", 0));
        label->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202\320\275\320\260\321\217 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217", 0));
        pushButtonAddAgeCategory->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "+", 0));
        groupBox_2->setTitle(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202", 0));
        label_4->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202 \320\276\321\202", 0));
        label_5->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\273\320\265\321\202 \320\264\320\276", 0));
        lineEditTypeAge->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\273\320\265\321\202", 0));
        lineEditAgeTill->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\264\320\276", 0));
        lineEditAgeFrom->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\276\321\202", 0));
        label_17->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "<html><head/><body><p>\320\225\321\201\320\273\320\270 \321\203\320\272\320\260\320\267\320\260\321\202\321\214, \320\275\320\260\320\277\321\200\320\270\320\274\320\265\321\200, \320\264\320\270\320\260\320\277\320\260\320\267\320\276\320\275 \320\276\321\202 0 \320\264\320\276 5 \320\273\320\265\321\202, \321\202\320\276 \321\202\320\276\320\263\320\264\320\260 \320\261\321\203\320\264\320\265\321\202 \320\276\320\261\320\276\320\261\321\200\320\260\320\266\320\260\321\202\321\214\321\201\321\217 &quot;\320\264\320\276 5 \320\273\320\265\321\202&quot;</p><p>\320\225\321\201\320\273\320\270 \320\276\321\202 35 \320\273\320\265\321\202 \320\264\320\276 99 \320\273\320\265\321\202, \321\202\320\276 &quot;\320\276\321\202 35 \320\273\320\265\321\202&quot;</p><p>\320\225\321\201\320\273\320\270 \320\276\321\202 18 \320\264\320\276 23 \320\273\320\265\321\202, \321\202\320\276 &quot;18-23 \320\273\320\265\321\202&quot;</p></body></html>", 0));
        groupBox->setTitle(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222\320\265\321\201", 0));
        label_7->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\223\321\200\320\260\320\275\320\270\321\207\320\275\321\213\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217 \320\262\320\265\321\201\320\260", 0));
        weightsLE->setPlaceholderText(QApplication::translate("GenerateTournamentCategoriesDialog", "20;35.5;40;48", 0));
        lineEditTypeWeight->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\272\320\263", 0));
        lineEditWeightTill->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\264\320\276", 0));
        lineEditWeightFrom->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\321\201\320\262\321\213\321\210\320\265", 0));
        label_11->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\200\320\260\321\203\320\275\320\264\320\276\320\262", 0));
        label_9->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\221\320\276\320\271", 0));
        label_10->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\237\320\265\321\200\320\265\321\200\321\213\320\262", 0));
        label_13->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222 \321\201\320\273\321\203\321\207\320\260\320\265 \320\275\320\270\321\207\321\214\320\270", 0));
        label_12->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\224\320\276\320\277. \321\200\320\260\321\203\320\275\320\264", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateTournamentCategoriesDialog: public Ui_GenerateTournamentCategoriesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATETOURNAMENTCATEGORIESDIALOG_H

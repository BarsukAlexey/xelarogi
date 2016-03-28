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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GenerateTournamentCategoriesDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *nameLE;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QComboBox *typeCB;
    QComboBox *sexCB;
    QHBoxLayout *horizontalLayout;
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
    QVBoxLayout *verticalLayout_5;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QVBoxLayout *verticalLayout_6;
    QSpinBox *duratiobFightingSB;
    QSpinBox *durationBreakSB;
    QSpinBox *roundCountSB;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GenerateTournamentCategoriesDialog)
    {
        if (GenerateTournamentCategoriesDialog->objectName().isEmpty())
            GenerateTournamentCategoriesDialog->setObjectName(QStringLiteral("GenerateTournamentCategoriesDialog"));
        GenerateTournamentCategoriesDialog->setEnabled(true);
        GenerateTournamentCategoriesDialog->resize(304, 311);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GenerateTournamentCategoriesDialog->sizePolicy().hasHeightForWidth());
        GenerateTournamentCategoriesDialog->setSizePolicy(sizePolicy);
        GenerateTournamentCategoriesDialog->setMinimumSize(QSize(304, 311));
        GenerateTournamentCategoriesDialog->setMaximumSize(QSize(304, 311));
        layoutWidget = new QWidget(GenerateTournamentCategoriesDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 12, 280, 286));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);


        horizontalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        nameLE = new QLineEdit(layoutWidget);
        nameLE->setObjectName(QStringLiteral("nameLE"));

        verticalLayout_2->addWidget(nameLE);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(24, 16777215));

        horizontalLayout_2->addWidget(pushButton);

        typeCB = new QComboBox(layoutWidget);
        typeCB->setObjectName(QStringLiteral("typeCB"));
        typeCB->setMaxVisibleItems(20);

        horizontalLayout_2->addWidget(typeCB);


        verticalLayout_2->addLayout(horizontalLayout_2);

        sexCB = new QComboBox(layoutWidget);
        sexCB->setObjectName(QStringLiteral("sexCB"));
        sexCB->setMaxVisibleItems(20);

        verticalLayout_2->addWidget(sexCB);


        horizontalLayout_4->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        ageFromSB = new QSpinBox(layoutWidget);
        ageFromSB->setObjectName(QStringLiteral("ageFromSB"));
        ageFromSB->setMaximum(9999);

        horizontalLayout->addWidget(ageFromSB);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);

        ageTillSB = new QSpinBox(layoutWidget);
        ageTillSB->setObjectName(QStringLiteral("ageTillSB"));
        ageTillSB->setMinimum(1);
        ageTillSB->setMaximum(99);
        ageTillSB->setValue(1);

        horizontalLayout->addWidget(ageTillSB);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout->addWidget(label_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_3->addWidget(label_7);

        weightsLE = new QLineEdit(layoutWidget);
        weightsLE->setObjectName(QStringLiteral("weightsLE"));

        verticalLayout_3->addWidget(weightsLE);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        QFont font;
        font.setPointSize(7);
        font.setItalic(true);
        label_8->setFont(font);

        verticalLayout_3->addWidget(label_8);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_5->addWidget(label_9);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_5->addWidget(label_10);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_5->addWidget(label_11);


        horizontalLayout_3->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        duratiobFightingSB = new QSpinBox(layoutWidget);
        duratiobFightingSB->setObjectName(QStringLiteral("duratiobFightingSB"));
        duratiobFightingSB->setMinimum(15);
        duratiobFightingSB->setMaximum(9999999);
        duratiobFightingSB->setValue(120);

        verticalLayout_6->addWidget(duratiobFightingSB);

        durationBreakSB = new QSpinBox(layoutWidget);
        durationBreakSB->setObjectName(QStringLiteral("durationBreakSB"));
        durationBreakSB->setMinimum(10);
        durationBreakSB->setMaximum(9999999);
        durationBreakSB->setValue(60);

        verticalLayout_6->addWidget(durationBreakSB);

        roundCountSB = new QSpinBox(layoutWidget);
        roundCountSB->setObjectName(QStringLiteral("roundCountSB"));
        roundCountSB->setMinimum(1);
        roundCountSB->setValue(3);

        verticalLayout_6->addWidget(roundCountSB);


        horizontalLayout_3->addLayout(verticalLayout_6);


        verticalLayout_4->addLayout(horizontalLayout_3);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(buttonBox);


        retranslateUi(GenerateTournamentCategoriesDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), GenerateTournamentCategoriesDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), GenerateTournamentCategoriesDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(GenerateTournamentCategoriesDialog);
    } // setupUi

    void retranslateUi(QDialog *GenerateTournamentCategoriesDialog)
    {
        GenerateTournamentCategoriesDialog->setWindowTitle(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\271 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        label->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265", 0));
        label_2->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\240\320\260\320\267\320\264\320\265\320\273", 0));
        label_3->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\237\320\276\320\273", 0));
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
    } // retranslateUi

};

namespace Ui {
    class GenerateTournamentCategoriesDialog: public Ui_GenerateTournamentCategoriesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATETOURNAMENTCATEGORIESDIALOG_H

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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GenerateTournamentCategoriesDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *nameLE;
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
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *GenerateTournamentCategoriesDialog)
    {
        if (GenerateTournamentCategoriesDialog->objectName().isEmpty())
            GenerateTournamentCategoriesDialog->setObjectName(QStringLiteral("GenerateTournamentCategoriesDialog"));
        GenerateTournamentCategoriesDialog->resize(315, 230);
        gridLayout = new QGridLayout(GenerateTournamentCategoriesDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(GenerateTournamentCategoriesDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        label_2 = new QLabel(GenerateTournamentCategoriesDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(GenerateTournamentCategoriesDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        nameLE = new QLineEdit(GenerateTournamentCategoriesDialog);
        nameLE->setObjectName(QStringLiteral("nameLE"));

        verticalLayout_2->addWidget(nameLE);

        typeCB = new QComboBox(GenerateTournamentCategoriesDialog);
        typeCB->setObjectName(QStringLiteral("typeCB"));

        verticalLayout_2->addWidget(typeCB);

        sexCB = new QComboBox(GenerateTournamentCategoriesDialog);
        sexCB->setObjectName(QStringLiteral("sexCB"));

        verticalLayout_2->addWidget(sexCB);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(GenerateTournamentCategoriesDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        ageFromSB = new QSpinBox(GenerateTournamentCategoriesDialog);
        ageFromSB->setObjectName(QStringLiteral("ageFromSB"));

        horizontalLayout->addWidget(ageFromSB);

        label_5 = new QLabel(GenerateTournamentCategoriesDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);

        ageTillSB = new QSpinBox(GenerateTournamentCategoriesDialog);
        ageTillSB->setObjectName(QStringLiteral("ageTillSB"));

        horizontalLayout->addWidget(ageTillSB);

        label_6 = new QLabel(GenerateTournamentCategoriesDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout->addWidget(label_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout);

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


        verticalLayout_4->addLayout(verticalLayout_3);


        gridLayout->addLayout(verticalLayout_4, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(GenerateTournamentCategoriesDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


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
        label_4->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202 \320\276\321\202", 0));
        label_5->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\273\320\265\321\202 \320\264\320\276", 0));
        label_6->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\273\320\265\321\202", 0));
        label_7->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\320\223\321\200\320\260\320\275\320\270\321\207\320\275\321\213\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\321\217 \320\262\320\265\321\201\320\260", 0));
        weightsLE->setPlaceholderText(QApplication::translate("GenerateTournamentCategoriesDialog", "15;20;35.5;40;48;61.5;80", 0));
        label_8->setText(QApplication::translate("GenerateTournamentCategoriesDialog", "\321\200\320\260\320\267\320\264\320\265\320\273\321\217\320\271\321\202\320\265 \320\262\320\265\320\273\320\270\321\207\320\270\320\275\321\213 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\274 \";\" (\321\202\320\276\321\207\320\272\320\260 \321\201 \320\267\320\260\320\277\321\217\321\202\320\276\320\271)", 0));
    } // retranslateUi

};

namespace Ui {
    class GenerateTournamentCategoriesDialog: public Ui_GenerateTournamentCategoriesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATETOURNAMENTCATEGORIESDIALOG_H

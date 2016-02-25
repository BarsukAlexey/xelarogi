/********************************************************************************
** Form generated from reading UI file 'addorderdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDORDERDIALOG_H
#define UI_ADDORDERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddOrderDialog
{
public:
    QGridLayout *gridLayout_2;
    QLabel *tournamentLabel;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *secondNameLE;
    QLineEdit *firstNameLE;
    QLineEdit *PatronymicLE;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QVBoxLayout *verticalLayout_4;
    QDateEdit *birthdayDE;
    QDoubleSpinBox *weightDSB;
    QComboBox *countriesCB;
    QComboBox *regionsCB;
    QComboBox *regionUnitsCB;
    QComboBox *gendersCB;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QVBoxLayout *verticalLayout_6;
    QComboBox *sportCategoriesCB;
    QComboBox *typesCB;
    QComboBox *tournamentCategoriesCB;
    QComboBox *clubsCB;
    QComboBox *coachsCB;

    void setupUi(QDialog *AddOrderDialog)
    {
        if (AddOrderDialog->objectName().isEmpty())
            AddOrderDialog->setObjectName(QStringLiteral("AddOrderDialog"));
        AddOrderDialog->resize(472, 353);
        gridLayout_2 = new QGridLayout(AddOrderDialog);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tournamentLabel = new QLabel(AddOrderDialog);
        tournamentLabel->setObjectName(QStringLiteral("tournamentLabel"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        tournamentLabel->setFont(font);

        gridLayout_2->addWidget(tournamentLabel, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(AddOrderDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 5, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(AddOrderDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setPointSize(8);
        label->setFont(font1);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(AddOrderDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(AddOrderDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        secondNameLE = new QLineEdit(AddOrderDialog);
        secondNameLE->setObjectName(QStringLiteral("secondNameLE"));

        verticalLayout_2->addWidget(secondNameLE);

        firstNameLE = new QLineEdit(AddOrderDialog);
        firstNameLE->setObjectName(QStringLiteral("firstNameLE"));

        verticalLayout_2->addWidget(firstNameLE);

        PatronymicLE = new QLineEdit(AddOrderDialog);
        PatronymicLE->setObjectName(QStringLiteral("PatronymicLE"));

        verticalLayout_2->addWidget(PatronymicLE);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_4 = new QLabel(AddOrderDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_3->addWidget(label_4);

        label_5 = new QLabel(AddOrderDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_3->addWidget(label_5);

        label_11 = new QLabel(AddOrderDialog);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_3->addWidget(label_11);

        label_12 = new QLabel(AddOrderDialog);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_3->addWidget(label_12);

        label_13 = new QLabel(AddOrderDialog);
        label_13->setObjectName(QStringLiteral("label_13"));

        verticalLayout_3->addWidget(label_13);

        label_14 = new QLabel(AddOrderDialog);
        label_14->setObjectName(QStringLiteral("label_14"));

        verticalLayout_3->addWidget(label_14);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        birthdayDE = new QDateEdit(AddOrderDialog);
        birthdayDE->setObjectName(QStringLiteral("birthdayDE"));

        verticalLayout_4->addWidget(birthdayDE);

        weightDSB = new QDoubleSpinBox(AddOrderDialog);
        weightDSB->setObjectName(QStringLiteral("weightDSB"));
        weightDSB->setMaximum(1000);
        weightDSB->setValue(50);

        verticalLayout_4->addWidget(weightDSB);

        countriesCB = new QComboBox(AddOrderDialog);
        countriesCB->setObjectName(QStringLiteral("countriesCB"));

        verticalLayout_4->addWidget(countriesCB);

        regionsCB = new QComboBox(AddOrderDialog);
        regionsCB->setObjectName(QStringLiteral("regionsCB"));

        verticalLayout_4->addWidget(regionsCB);

        regionUnitsCB = new QComboBox(AddOrderDialog);
        regionUnitsCB->setObjectName(QStringLiteral("regionUnitsCB"));

        verticalLayout_4->addWidget(regionUnitsCB);

        gendersCB = new QComboBox(AddOrderDialog);
        gendersCB->setObjectName(QStringLiteral("gendersCB"));

        verticalLayout_4->addWidget(gendersCB);


        horizontalLayout_2->addLayout(verticalLayout_4);


        gridLayout_2->addLayout(horizontalLayout_2, 2, 0, 2, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_6 = new QLabel(AddOrderDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout_5->addWidget(label_6);

        label_7 = new QLabel(AddOrderDialog);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_5->addWidget(label_7);

        label_8 = new QLabel(AddOrderDialog);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_5->addWidget(label_8);

        label_9 = new QLabel(AddOrderDialog);
        label_9->setObjectName(QStringLiteral("label_9"));

        verticalLayout_5->addWidget(label_9);

        label_10 = new QLabel(AddOrderDialog);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_5->addWidget(label_10);


        horizontalLayout_3->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        sportCategoriesCB = new QComboBox(AddOrderDialog);
        sportCategoriesCB->setObjectName(QStringLiteral("sportCategoriesCB"));

        verticalLayout_6->addWidget(sportCategoriesCB);

        typesCB = new QComboBox(AddOrderDialog);
        typesCB->setObjectName(QStringLiteral("typesCB"));

        verticalLayout_6->addWidget(typesCB);

        tournamentCategoriesCB = new QComboBox(AddOrderDialog);
        tournamentCategoriesCB->setObjectName(QStringLiteral("tournamentCategoriesCB"));

        verticalLayout_6->addWidget(tournamentCategoriesCB);

        clubsCB = new QComboBox(AddOrderDialog);
        clubsCB->setObjectName(QStringLiteral("clubsCB"));

        verticalLayout_6->addWidget(clubsCB);

        coachsCB = new QComboBox(AddOrderDialog);
        coachsCB->setObjectName(QStringLiteral("coachsCB"));

        verticalLayout_6->addWidget(coachsCB);


        horizontalLayout_3->addLayout(verticalLayout_6);


        gridLayout_2->addLayout(horizontalLayout_3, 1, 1, 2, 1);

        buttonBox->raise();
        tournamentLabel->raise();

        retranslateUi(AddOrderDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddOrderDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddOrderDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddOrderDialog);
    } // setupUi

    void retranslateUi(QDialog *AddOrderDialog)
    {
        AddOrderDialog->setWindowTitle(QApplication::translate("AddOrderDialog", "\320\224\320\276\320\261\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\275\320\276\320\262\320\276\320\271 \320\267\320\260\321\217\320\262\320\272\320\270", 0));
        tournamentLabel->setText(QApplication::translate("AddOrderDialog", "TextLabel", 0));
        label->setText(QApplication::translate("AddOrderDialog", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217", 0));
        label_2->setText(QApplication::translate("AddOrderDialog", "\320\230\320\274\321\217", 0));
        label_3->setText(QApplication::translate("AddOrderDialog", "\320\236\321\202\321\207\320\265\321\201\321\202\320\262\320\276", 0));
        label_4->setText(QApplication::translate("AddOrderDialog", "\320\224\320\260\321\202\320\260 \321\200\320\276\320\266\320\264\320\265\320\275\320\270\321\217", 0));
        label_5->setText(QApplication::translate("AddOrderDialog", "\320\222\320\265\321\201", 0));
        label_11->setText(QApplication::translate("AddOrderDialog", "\320\241\321\202\321\200\320\260\320\275\320\260", 0));
        label_12->setText(QApplication::translate("AddOrderDialog", "\320\240\320\265\320\263\320\270\320\276\320\275", 0));
        label_13->setText(QApplication::translate("AddOrderDialog", "\320\235\320\260\321\201\320\265\320\273\320\265\320\275\320\275\321\213\320\271 \320\277\321\203\320\275\320\272\321\202", 0));
        label_14->setText(QApplication::translate("AddOrderDialog", "\320\237\320\276\320\273", 0));
        label_6->setText(QApplication::translate("AddOrderDialog", "\320\241\320\277\320\276\321\200\321\202\320\270\320\262\320\275\321\213\320\271 \321\200\320\260\320\267\321\200\321\217\320\264", 0));
        label_7->setText(QApplication::translate("AddOrderDialog", "\320\240\320\260\320\267\320\264\320\265\320\273 \321\201\320\276\321\200\320\265\320\262\320\275\320\276\320\262\320\260\320\275\320\270\321\217", 0));
        label_8->setText(QApplication::translate("AddOrderDialog", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217 \321\202\321\203\321\200\320\275\320\270\321\200\320\260", 0));
        label_9->setText(QApplication::translate("AddOrderDialog", "\320\232\320\273\321\203\320\261", 0));
        label_10->setText(QApplication::translate("AddOrderDialog", "\320\242\321\200\320\265\320\275\320\265\321\200", 0));
    } // retranslateUi

};

namespace Ui {
    class AddOrderDialog: public Ui_AddOrderDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDORDERDIALOG_H

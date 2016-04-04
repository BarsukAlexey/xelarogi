/********************************************************************************
** Form generated from reading UI file 'dialog_create_age_category.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_CREATE_AGE_CATEGORY_H
#define UI_DIALOG_CREATE_AGE_CATEGORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateAgeCategory
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBoxSex;
    QLineEdit *lineEditAgeCategory;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CreateAgeCategory)
    {
        if (CreateAgeCategory->objectName().isEmpty())
            CreateAgeCategory->setObjectName(QStringLiteral("CreateAgeCategory"));
        CreateAgeCategory->resize(438, 96);
        gridLayout = new QGridLayout(CreateAgeCategory);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(CreateAgeCategory);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(CreateAgeCategory);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        comboBoxSex = new QComboBox(CreateAgeCategory);
        comboBoxSex->setObjectName(QStringLiteral("comboBoxSex"));

        verticalLayout_2->addWidget(comboBoxSex);

        lineEditAgeCategory = new QLineEdit(CreateAgeCategory);
        lineEditAgeCategory->setObjectName(QStringLiteral("lineEditAgeCategory"));

        verticalLayout_2->addWidget(lineEditAgeCategory);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(CreateAgeCategory);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 2);


        retranslateUi(CreateAgeCategory);
        QObject::connect(buttonBox, SIGNAL(accepted()), CreateAgeCategory, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateAgeCategory, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateAgeCategory);
    } // setupUi

    void retranslateUi(QDialog *CreateAgeCategory)
    {
        CreateAgeCategory->setWindowTitle(QApplication::translate("CreateAgeCategory", "Dialog", 0));
        label->setText(QApplication::translate("CreateAgeCategory", "\320\237\320\276\320\273", 0));
        label_2->setText(QApplication::translate("CreateAgeCategory", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202\320\275\320\260\321\217 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217", 0));
    } // retranslateUi

};

namespace Ui {
    class CreateAgeCategory: public Ui_CreateAgeCategory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_CREATE_AGE_CATEGORY_H

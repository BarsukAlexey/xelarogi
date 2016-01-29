/********************************************************************************
** Form generated from reading UI file 'onefieldsetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONEFIELDSETUPDIALOG_H
#define UI_ONEFIELDSETUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OneFieldSetupDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QListWidget *incorrectLW;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *toCorrectBtn;
    QSpacerItem *verticalSpacer_3;
    QPushButton *toIncorrectBtn;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QListWidget *correctLW;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *OneFieldSetupDialog)
    {
        if (OneFieldSetupDialog->objectName().isEmpty())
            OneFieldSetupDialog->setObjectName(QStringLiteral("OneFieldSetupDialog"));
        OneFieldSetupDialog->resize(565, 327);
        gridLayout = new QGridLayout(OneFieldSetupDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(OneFieldSetupDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(OneFieldSetupDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lineEdit = new QLineEdit(OneFieldSetupDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout_2->addLayout(horizontalLayout_2);

        incorrectLW = new QListWidget(OneFieldSetupDialog);
        incorrectLW->setObjectName(QStringLiteral("incorrectLW"));
        incorrectLW->setSelectionMode(QAbstractItemView::MultiSelection);

        verticalLayout_2->addWidget(incorrectLW);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        toCorrectBtn = new QPushButton(OneFieldSetupDialog);
        toCorrectBtn->setObjectName(QStringLiteral("toCorrectBtn"));
        toCorrectBtn->setMaximumSize(QSize(50, 16777215));

        verticalLayout->addWidget(toCorrectBtn);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        toIncorrectBtn = new QPushButton(OneFieldSetupDialog);
        toIncorrectBtn->setObjectName(QStringLiteral("toIncorrectBtn"));
        toIncorrectBtn->setMaximumSize(QSize(50, 16777215));

        verticalLayout->addWidget(toIncorrectBtn);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_2 = new QLabel(OneFieldSetupDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_3->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(OneFieldSetupDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        lineEdit_2 = new QLineEdit(OneFieldSetupDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout->addWidget(lineEdit_2);


        verticalLayout_3->addLayout(horizontalLayout);

        correctLW = new QListWidget(OneFieldSetupDialog);
        correctLW->setObjectName(QStringLiteral("correctLW"));
        correctLW->setSelectionMode(QAbstractItemView::MultiSelection);

        verticalLayout_3->addWidget(correctLW);


        horizontalLayout_3->addLayout(verticalLayout_3);


        gridLayout->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(OneFieldSetupDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(OneFieldSetupDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), OneFieldSetupDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), OneFieldSetupDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(OneFieldSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *OneFieldSetupDialog)
    {
        OneFieldSetupDialog->setWindowTitle(QApplication::translate("OneFieldSetupDialog", "Dialog", 0));
        label->setText(QApplication::translate("OneFieldSetupDialog", "\320\235\320\265 \320\277\321\200\320\276\320\271\320\265\320\264\320\275\320\276", 0));
        label_3->setText(QApplication::translate("OneFieldSetupDialog", "\320\244\320\270\320\273\321\214\321\202\321\200", 0));
        toCorrectBtn->setText(QApplication::translate("OneFieldSetupDialog", ">", 0));
        toIncorrectBtn->setText(QApplication::translate("OneFieldSetupDialog", "<", 0));
        label_2->setText(QApplication::translate("OneFieldSetupDialog", "\320\237\321\200\320\276\320\271\320\264\320\265\320\275\320\276", 0));
        label_4->setText(QApplication::translate("OneFieldSetupDialog", "\320\244\320\270\320\273\321\214\321\202\321\200", 0));
    } // retranslateUi

};

namespace Ui {
    class OneFieldSetupDialog: public Ui_OneFieldSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONEFIELDSETUPDIALOG_H

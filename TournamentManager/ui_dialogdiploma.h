/********************************************************************************
** Form generated from reading UI file 'dialogdiploma.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDIPLOMA_H
#define UI_DIALOGDIPLOMA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogDiploma
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogDiploma)
    {
        if (DialogDiploma->objectName().isEmpty())
            DialogDiploma->setObjectName(QStringLiteral("DialogDiploma"));
        DialogDiploma->resize(882, 704);
        gridLayout = new QGridLayout(DialogDiploma);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(DialogDiploma);
        widget->setObjectName(QStringLiteral("widget"));

        gridLayout->addWidget(widget, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DialogDiploma);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);


        retranslateUi(DialogDiploma);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogDiploma, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogDiploma, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogDiploma);
    } // setupUi

    void retranslateUi(QDialog *DialogDiploma)
    {
        DialogDiploma->setWindowTitle(QApplication::translate("DialogDiploma", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogDiploma: public Ui_DialogDiploma {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDIPLOMA_H

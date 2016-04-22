/********************************************************************************
** Form generated from reading UI file 'form_advertisement.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_ADVERTISEMENT_H
#define UI_FORM_ADVERTISEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormAdvertisement
{
public:
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QWidget *FormAdvertisement)
    {
        if (FormAdvertisement->objectName().isEmpty())
            FormAdvertisement->setObjectName(QStringLiteral("FormAdvertisement"));
        FormAdvertisement->resize(578, 447);
        FormAdvertisement->setStyleSheet(QStringLiteral("background-color:black"));
        gridLayout = new QGridLayout(FormAdvertisement);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(FormAdvertisement);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(FormAdvertisement);

        QMetaObject::connectSlotsByName(FormAdvertisement);
    } // setupUi

    void retranslateUi(QWidget *FormAdvertisement)
    {
        FormAdvertisement->setWindowTitle(QApplication::translate("FormAdvertisement", "Form", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FormAdvertisement: public Ui_FormAdvertisement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_ADVERTISEMENT_H

/********************************************************************************
** Form generated from reading UI file 'tempform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPFORM_H
#define UI_TEMPFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <aspect_ratio_pixmap_label.h>
#include <aspectratiotextlabel.h>

QT_BEGIN_NAMESPACE

class Ui_tempForm
{
public:
    QGridLayout *gridLayout;
    AspectRatioTextLabel *label;
    QLabel *label_2;
    AspectRatioPixmapLabel *label_3;

    void setupUi(QWidget *tempForm)
    {
        if (tempForm->objectName().isEmpty())
            tempForm->setObjectName(QStringLiteral("tempForm"));
        tempForm->resize(674, 477);
        gridLayout = new QGridLayout(tempForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new AspectRatioTextLabel(tempForm);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(tempForm);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_3 = new AspectRatioPixmapLabel(tempForm);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        gridLayout->setRowStretch(0, 10);
        gridLayout->setRowStretch(1, 80);
        gridLayout->setRowStretch(2, 10);

        retranslateUi(tempForm);

        QMetaObject::connectSlotsByName(tempForm);
    } // setupUi

    void retranslateUi(QWidget *tempForm)
    {
        tempForm->setWindowTitle(QApplication::translate("tempForm", "Form", 0));
        label->setText(QApplication::translate("tempForm", "LoLKA", 0));
        label_2->setText(QString());
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class tempForm: public Ui_tempForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPFORM_H

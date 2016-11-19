/********************************************************************************
** Form generated from reading UI file 'dialogschedule2inputtype.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSCHEDULE2INPUTTYPE_H
#define UI_DIALOGSCHEDULE2INPUTTYPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialogschedule2InputType
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QTextEdit *textEdit;
    QLabel *label_2;
    QTimeEdit *timeEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialogschedule2InputType)
    {
        if (Dialogschedule2InputType->objectName().isEmpty())
            Dialogschedule2InputType->setObjectName(QStringLiteral("Dialogschedule2InputType"));
        Dialogschedule2InputType->resize(292, 283);
        gridLayout = new QGridLayout(Dialogschedule2InputType);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(Dialogschedule2InputType);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        textEdit = new QTextEdit(widget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout_2->addWidget(textEdit, 0, 0, 1, 2);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        timeEdit = new QTimeEdit(widget);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setMinimumTime(QTime(0, 1, 0));

        gridLayout_2->addWidget(timeEdit, 1, 1, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(Dialogschedule2InputType);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(Dialogschedule2InputType);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialogschedule2InputType, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialogschedule2InputType, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialogschedule2InputType);
    } // setupUi

    void retranslateUi(QDialog *Dialogschedule2InputType)
    {
        Dialogschedule2InputType->setWindowTitle(QApplication::translate("Dialogschedule2InputType", "Dialog", 0));
        textEdit->setPlaceholderText(QApplication::translate("Dialogschedule2InputType", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\270\320\265 \320\274\320\265\321\200\320\276\320\277\321\200\320\270\321\217\321\202\320\270\321\217: \320\277\320\265\321\200\320\265\321\200\321\213\320\262, \320\276\320\261\320\265\320\264, \321\210\320\276\321\203 ...", 0));
        label_2->setText(QApplication::translate("Dialogschedule2InputType", "\320\224\320\273\320\270\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \320\274\320\265\321\200\320\276\320\277\321\200\320\270\321\217\321\202\320\270\321\217 (\321\207\321\207:\320\274\320\274):", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialogschedule2InputType: public Ui_Dialogschedule2InputType {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSCHEDULE2INPUTTYPE_H

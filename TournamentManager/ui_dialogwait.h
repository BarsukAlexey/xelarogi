/********************************************************************************
** Form generated from reading UI file 'dialogwait.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGWAIT_H
#define UI_DIALOGWAIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_DialogWait
{
public:

    void setupUi(QDialog *DialogWait)
    {
        if (DialogWait->objectName().isEmpty())
            DialogWait->setObjectName(QStringLiteral("DialogWait"));
        DialogWait->resize(400, 300);

        retranslateUi(DialogWait);

        QMetaObject::connectSlotsByName(DialogWait);
    } // setupUi

    void retranslateUi(QDialog *DialogWait)
    {
        DialogWait->setWindowTitle(QApplication::translate("DialogWait", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogWait: public Ui_DialogWait {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGWAIT_H

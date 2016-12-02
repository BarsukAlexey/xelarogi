/********************************************************************************
** Form generated from reading UI file 'dialogawardpanel.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGAWARDPANEL_H
#define UI_DIALOGAWARDPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_DialogAwardPanel
{
public:

    void setupUi(QDialog *DialogAwardPanel)
    {
        if (DialogAwardPanel->objectName().isEmpty())
            DialogAwardPanel->setObjectName(QStringLiteral("DialogAwardPanel"));
        DialogAwardPanel->resize(400, 300);

        retranslateUi(DialogAwardPanel);

        QMetaObject::connectSlotsByName(DialogAwardPanel);
    } // setupUi

    void retranslateUi(QDialog *DialogAwardPanel)
    {
        DialogAwardPanel->setWindowTitle(QApplication::translate("DialogAwardPanel", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogAwardPanel: public Ui_DialogAwardPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGAWARDPANEL_H

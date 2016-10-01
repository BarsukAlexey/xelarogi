/********************************************************************************
** Form generated from reading UI file 'fightingpairs.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIGHTINGPAIRS_H
#define UI_FIGHTINGPAIRS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FightingPairs
{
public:

    void setupUi(QWidget *FightingPairs)
    {
        if (FightingPairs->objectName().isEmpty())
            FightingPairs->setObjectName(QStringLiteral("FightingPairs"));
        FightingPairs->resize(400, 300);

        retranslateUi(FightingPairs);

        QMetaObject::connectSlotsByName(FightingPairs);
    } // setupUi

    void retranslateUi(QWidget *FightingPairs)
    {
        FightingPairs->setWindowTitle(QApplication::translate("FightingPairs", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class FightingPairs: public Ui_FightingPairs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIGHTINGPAIRS_H

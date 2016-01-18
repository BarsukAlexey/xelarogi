/********************************************************************************
** Form generated from reading UI file 'tournamentadmindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOURNAMENTADMINDIALOG_H
#define UI_TOURNAMENTADMINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TournamentAdminDialog
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *TournamentAdminDialog)
    {
        if (TournamentAdminDialog->objectName().isEmpty())
            TournamentAdminDialog->setObjectName(QStringLiteral("TournamentAdminDialog"));
        TournamentAdminDialog->resize(669, 459);
        buttonBox = new QDialogButtonBox(TournamentAdminDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(310, 410, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        pushButton = new QPushButton(TournamentAdminDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(240, 90, 141, 81));
        pushButton_2 = new QPushButton(TournamentAdminDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 180, 141, 51));
        pushButton_3 = new QPushButton(TournamentAdminDialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(240, 240, 141, 51));
        pushButton_4 = new QPushButton(TournamentAdminDialog);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(240, 300, 141, 51));
        label = new QLabel(TournamentAdminDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(390, 100, 101, 16));
        label_2 = new QLabel(TournamentAdminDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(390, 120, 101, 16));
        label_3 = new QLabel(TournamentAdminDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(390, 140, 211, 16));

        retranslateUi(TournamentAdminDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TournamentAdminDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TournamentAdminDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TournamentAdminDialog);
    } // setupUi

    void retranslateUi(QDialog *TournamentAdminDialog)
    {
        TournamentAdminDialog->setWindowTitle(QApplication::translate("TournamentAdminDialog", "Dialog", 0));
        pushButton->setText(QApplication::translate("TournamentAdminDialog", "\320\227\320\260\321\217\320\262\320\272\320\270", 0));
        pushButton_2->setText(QApplication::translate("TournamentAdminDialog", "\320\242\321\203\321\200\320\275\320\270\321\200\320\275\320\260\321\217 \321\201\320\265\321\202\320\272\320\260", 0));
        pushButton_3->setText(QApplication::translate("TournamentAdminDialog", "\320\236\321\202\321\207\320\265\321\202\321\213", 0));
        pushButton_4->setText(QApplication::translate("TournamentAdminDialog", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270", 0));
        label->setText(QApplication::translate("TournamentAdminDialog", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", 0));
        label_2->setText(QApplication::translate("TournamentAdminDialog", "\320\230\320\274\320\277\320\276\321\200\321\202", 0));
        label_3->setText(QApplication::translate("TournamentAdminDialog", "\320\222\320\267\320\262\320\265\321\210\320\270\320\262\320\260\320\275\320\270\320\265 / \320\236\320\277\320\273\320\260\321\202\320\260 / \320\220\320\272\320\272\321\200\320\265\320\264\320\270\321\202\320\260\321\206\320\270\321\217", 0));
    } // retranslateUi

};

namespace Ui {
    class TournamentAdminDialog: public Ui_TournamentAdminDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOURNAMENTADMINDIALOG_H

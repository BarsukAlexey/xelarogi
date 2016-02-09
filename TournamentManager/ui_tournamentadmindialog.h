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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TournamentAdminDialog
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *testLabel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *createOrdersBtn;
    QVBoxLayout *verticalLayout;
    QPushButton *ordersPayedBtn;
    QPushButton *ordersWeightBtn;
    QPushButton *ordersMedicalBtn;
    QPushButton *ordersAccreditationBtn;

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
        label->setGeometry(QRect(420, 70, 101, 16));
        label_2 = new QLabel(TournamentAdminDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(450, 90, 101, 16));
        testLabel = new QLabel(TournamentAdminDialog);
        testLabel->setObjectName(QStringLiteral("testLabel"));
        testLabel->setGeometry(QRect(30, 30, 161, 21));
        layoutWidget = new QWidget(TournamentAdminDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(220, 70, 174, 99));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        createOrdersBtn = new QPushButton(layoutWidget);
        createOrdersBtn->setObjectName(QStringLiteral("createOrdersBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(createOrdersBtn->sizePolicy().hasHeightForWidth());
        createOrdersBtn->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(createOrdersBtn);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        ordersPayedBtn = new QPushButton(layoutWidget);
        ordersPayedBtn->setObjectName(QStringLiteral("ordersPayedBtn"));
        sizePolicy.setHeightForWidth(ordersPayedBtn->sizePolicy().hasHeightForWidth());
        ordersPayedBtn->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(ordersPayedBtn);

        ordersWeightBtn = new QPushButton(layoutWidget);
        ordersWeightBtn->setObjectName(QStringLiteral("ordersWeightBtn"));
        sizePolicy.setHeightForWidth(ordersWeightBtn->sizePolicy().hasHeightForWidth());
        ordersWeightBtn->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(ordersWeightBtn);

        ordersMedicalBtn = new QPushButton(layoutWidget);
        ordersMedicalBtn->setObjectName(QStringLiteral("ordersMedicalBtn"));
        sizePolicy.setHeightForWidth(ordersMedicalBtn->sizePolicy().hasHeightForWidth());
        ordersMedicalBtn->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(ordersMedicalBtn);

        ordersAccreditationBtn = new QPushButton(layoutWidget);
        ordersAccreditationBtn->setObjectName(QStringLiteral("ordersAccreditationBtn"));
        sizePolicy.setHeightForWidth(ordersAccreditationBtn->sizePolicy().hasHeightForWidth());
        ordersAccreditationBtn->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(ordersAccreditationBtn);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(TournamentAdminDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TournamentAdminDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TournamentAdminDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TournamentAdminDialog);
    } // setupUi

    void retranslateUi(QDialog *TournamentAdminDialog)
    {
        TournamentAdminDialog->setWindowTitle(QApplication::translate("TournamentAdminDialog", "Dialog", 0));
        pushButton_2->setText(QApplication::translate("TournamentAdminDialog", "\320\242\321\203\321\200\320\275\320\270\321\200\320\275\320\260\321\217 \321\201\320\265\321\202\320\272\320\260", 0));
        pushButton_3->setText(QApplication::translate("TournamentAdminDialog", "\320\236\321\202\321\207\320\265\321\202\321\213", 0));
        pushButton_4->setText(QApplication::translate("TournamentAdminDialog", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270", 0));
        label->setText(QApplication::translate("TournamentAdminDialog", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", 0));
        label_2->setText(QApplication::translate("TournamentAdminDialog", "\320\230\320\274\320\277\320\276\321\200\321\202", 0));
        testLabel->setText(QApplication::translate("TournamentAdminDialog", "TextLabel", 0));
        createOrdersBtn->setText(QApplication::translate("TournamentAdminDialog", "\320\227\320\260\321\217\320\262\320\272\320\270", 0));
        ordersPayedBtn->setText(QApplication::translate("TournamentAdminDialog", "\320\236\320\277\320\273\320\260\321\202\320\260", 0));
        ordersWeightBtn->setText(QApplication::translate("TournamentAdminDialog", "\320\222\320\267\320\262\320\265\321\210\320\270\320\262\320\260\320\275\320\270\320\265", 0));
        ordersMedicalBtn->setText(QApplication::translate("TournamentAdminDialog", "\320\234\320\265\320\264. \320\276\321\201\320\274\320\276\321\202\321\200", 0));
        ordersAccreditationBtn->setText(QApplication::translate("TournamentAdminDialog", "\320\220\320\272\320\272\321\200\320\265\320\264\320\270\321\202\320\260\321\206\320\270\321\217", 0));
    } // retranslateUi

};

namespace Ui {
    class TournamentAdminDialog: public Ui_TournamentAdminDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOURNAMENTADMINDIALOG_H

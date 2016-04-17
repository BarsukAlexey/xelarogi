/********************************************************************************
** Form generated from reading UI file 'countryiconsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COUNTRYICONSDIALOG_H
#define UI_COUNTRYICONSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CountryIconsDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *countryCB;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *oldImageL;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QPushButton *loadNewImageBtn;
    QLabel *newImageL;
    QSpacerItem *verticalSpacer_2;
    QPushButton *saveBtn;

    void setupUi(QDialog *CountryIconsDialog)
    {
        if (CountryIconsDialog->objectName().isEmpty())
            CountryIconsDialog->setObjectName(QStringLiteral("CountryIconsDialog"));
        CountryIconsDialog->resize(612, 254);
        verticalLayout_3 = new QVBoxLayout(CountryIconsDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(CountryIconsDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        countryCB = new QComboBox(CountryIconsDialog);
        countryCB->setObjectName(QStringLiteral("countryCB"));

        horizontalLayout->addWidget(countryCB);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(CountryIconsDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        oldImageL = new QLabel(CountryIconsDialog);
        oldImageL->setObjectName(QStringLiteral("oldImageL"));

        verticalLayout->addWidget(oldImageL);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(CountryIconsDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        loadNewImageBtn = new QPushButton(CountryIconsDialog);
        loadNewImageBtn->setObjectName(QStringLiteral("loadNewImageBtn"));

        horizontalLayout_3->addWidget(loadNewImageBtn);


        verticalLayout_2->addLayout(horizontalLayout_3);

        newImageL = new QLabel(CountryIconsDialog);
        newImageL->setObjectName(QStringLiteral("newImageL"));

        verticalLayout_2->addWidget(newImageL);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        saveBtn = new QPushButton(CountryIconsDialog);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));

        verticalLayout_3->addWidget(saveBtn);


        retranslateUi(CountryIconsDialog);

        QMetaObject::connectSlotsByName(CountryIconsDialog);
    } // setupUi

    void retranslateUi(QDialog *CountryIconsDialog)
    {
        CountryIconsDialog->setWindowTitle(QApplication::translate("CountryIconsDialog", "\320\222\321\213\320\261\320\276\321\200 \320\270\320\272\320\276\320\275\320\276\320\272 \320\264\320\273\321\217 \321\201\321\202\321\200\320\260\320\275", 0));
        label->setText(QApplication::translate("CountryIconsDialog", "\320\222\321\213\320\261\320\265\321\200\320\265\321\202\320\265 \321\201\321\202\321\200\320\260\320\275\321\203", 0));
        label_2->setText(QApplication::translate("CountryIconsDialog", "\321\202\320\265\320\272\321\203\321\211\320\260\321\217 \320\270\320\272\320\276\320\275\320\272\320\260", 0));
        oldImageL->setText(QString());
        label_3->setText(QApplication::translate("CountryIconsDialog", "\320\275\320\276\320\262\320\260\321\217 \320\270\320\272\320\276\320\275\320\272\320\260", 0));
        loadNewImageBtn->setText(QApplication::translate("CountryIconsDialog", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", 0));
        newImageL->setText(QString());
        saveBtn->setText(QApplication::translate("CountryIconsDialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class CountryIconsDialog: public Ui_CountryIconsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COUNTRYICONSDIALOG_H

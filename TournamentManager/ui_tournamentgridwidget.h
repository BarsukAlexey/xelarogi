/********************************************************************************
** Form generated from reading UI file 'tournamentgridwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOURNAMENTGRIDWIDGET_H
#define UI_TOURNAMENTGRIDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TournamentGridWidget
{
public:
    QPushButton *pushButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpinBox *spinBox;
    QLabel *label;
    QSpinBox *spinBox_2;
    QPushButton *pushButton_2;

    void setupUi(QWidget *TournamentGridWidget)
    {
        if (TournamentGridWidget->objectName().isEmpty())
            TournamentGridWidget->setObjectName(QStringLiteral("TournamentGridWidget"));
        TournamentGridWidget->resize(778, 483);
        TournamentGridWidget->setMouseTracking(true);
        pushButton = new QPushButton(TournamentGridWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 20, 112, 23));
        widget = new QWidget(TournamentGridWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(180, 20, 245, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        spinBox = new QSpinBox(widget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMaximum(999);
        spinBox->setValue(80);

        horizontalLayout->addWidget(spinBox);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        spinBox_2 = new QSpinBox(widget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMaximum(999);
        spinBox_2->setValue(20);

        horizontalLayout->addWidget(spinBox_2);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        retranslateUi(TournamentGridWidget);

        QMetaObject::connectSlotsByName(TournamentGridWidget);
    } // setupUi

    void retranslateUi(QWidget *TournamentGridWidget)
    {
        TournamentGridWidget->setWindowTitle(QApplication::translate("TournamentGridWidget", "Form", 0));
        pushButton->setText(QApplication::translate("TournamentGridWidget", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272 Excel", 0));
        label->setText(QApplication::translate("TournamentGridWidget", "X", 0));
        pushButton_2->setText(QApplication::translate("TournamentGridWidget", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214 \321\200\320\260\320\267\320\274\320\265\321\200 \320\272\320\273\320\265\321\202\320\272\320\270", 0));
    } // retranslateUi

};

namespace Ui {
    class TournamentGridWidget: public Ui_TournamentGridWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOURNAMENTGRIDWIDGET_H

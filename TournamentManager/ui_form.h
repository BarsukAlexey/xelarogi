/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QSplitter *splitter;
    QTableView *tableView;
    QWidget *widget;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_26;
    QLabel *label_28;
    QVBoxLayout *verticalLayout_2;
    QComboBox *clubsCB;
    QComboBox *tournamentCategoriesCB;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->setEnabled(true);
        Form->resize(1020, 556);
        splitter = new QSplitter(Form);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(130, 140, 601, 261));
        splitter->setOrientation(Qt::Horizontal);
        tableView = new QTableView(splitter);
        tableView->setObjectName(QStringLiteral("tableView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);
        tableView->setFocusPolicy(Qt::ClickFocus);
        tableView->setContextMenuPolicy(Qt::CustomContextMenu);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setAlternatingRowColors(true);
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setSortingEnabled(true);
        splitter->addWidget(tableView);
        tableView->horizontalHeader()->setCascadingSectionResizes(true);
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(false);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 0));
        widget1 = new QWidget(widget);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(30, 90, 191, 50));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_26 = new QLabel(widget1);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_26);

        label_28 = new QLabel(widget1);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_28);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        clubsCB = new QComboBox(widget1);
        clubsCB->setObjectName(QStringLiteral("clubsCB"));
        clubsCB->setMaxVisibleItems(69);

        verticalLayout_2->addWidget(clubsCB);

        tournamentCategoriesCB = new QComboBox(widget1);
        tournamentCategoriesCB->setObjectName(QStringLiteral("tournamentCategoriesCB"));
        tournamentCategoriesCB->setMaxVisibleItems(69);

        verticalLayout_2->addWidget(tournamentCategoriesCB);


        horizontalLayout->addLayout(verticalLayout_2);

        splitter->addWidget(widget);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        label_26->setText(QApplication::translate("Form", "\320\240\320\260\320\267\320\264\320\265\320\273 \321\201\320\276\321\200\320\265\320\262\320\275\320\276\320\262\320\260\320\275\320\270\321\217", 0));
        label_28->setText(QApplication::translate("Form", "\320\232\320\273\321\203\320\261", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H

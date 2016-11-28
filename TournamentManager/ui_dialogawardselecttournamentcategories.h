/********************************************************************************
** Form generated from reading UI file 'dialogawardselecttournamentcategories.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGAWARDSELECTTOURNAMENTCATEGORIES_H
#define UI_DIALOGAWARDSELECTTOURNAMENTCATEGORIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogAwardSelectTournamentCategories
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *tableWidget;
    QPushButton *pushButtonShowGridLeft;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QTableWidget *tableWidgetReady;
    QPushButton *pushButtonShowGridRight;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogAwardSelectTournamentCategories)
    {
        if (DialogAwardSelectTournamentCategories->objectName().isEmpty())
            DialogAwardSelectTournamentCategories->setObjectName(QStringLiteral("DialogAwardSelectTournamentCategories"));
        DialogAwardSelectTournamentCategories->resize(599, 388);
        gridLayout = new QGridLayout(DialogAwardSelectTournamentCategories);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(DialogAwardSelectTournamentCategories);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        tableWidget = new QTableWidget(widget);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout->addWidget(tableWidget);

        pushButtonShowGridLeft = new QPushButton(widget);
        pushButtonShowGridLeft->setObjectName(QStringLiteral("pushButtonShowGridLeft"));

        verticalLayout->addWidget(pushButtonShowGridLeft);

        splitter->addWidget(widget);
        widget1 = new QWidget(splitter);
        widget1->setObjectName(QStringLiteral("widget1"));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        tableWidgetReady = new QTableWidget(widget1);
        if (tableWidgetReady->columnCount() < 7)
            tableWidgetReady->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetReady->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetReady->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetReady->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidgetReady->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidgetReady->setHorizontalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidgetReady->setHorizontalHeaderItem(5, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidgetReady->setHorizontalHeaderItem(6, __qtablewidgetitem13);
        tableWidgetReady->setObjectName(QStringLiteral("tableWidgetReady"));
        tableWidgetReady->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgetReady->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetReady->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_2->addWidget(tableWidgetReady);

        pushButtonShowGridRight = new QPushButton(widget1);
        pushButtonShowGridRight->setObjectName(QStringLiteral("pushButtonShowGridRight"));

        verticalLayout_2->addWidget(pushButtonShowGridRight);

        splitter->addWidget(widget1);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DialogAwardSelectTournamentCategories);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(DialogAwardSelectTournamentCategories);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogAwardSelectTournamentCategories, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogAwardSelectTournamentCategories, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogAwardSelectTournamentCategories);
    } // setupUi

    void retranslateUi(QDialog *DialogAwardSelectTournamentCategories)
    {
        label->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\235\320\265 \320\263\320\276\321\202\320\276\320\262\321\213", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\240\320\260\320\267\320\264\320\265\320\273", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\237\320\276\320\273", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202 \320\276\321\202", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202 \320\264\320\276", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\222\320\265\321\201 \320\276\321\202", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\222\320\265\321\201 \320\264\320\276", 0));
        pushButtonShowGridLeft->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\201\320\265\321\202\320\272\321\203", 0));
        label_2->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\223\320\276\321\202\320\276\320\262\321\213", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidgetReady->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidgetReady->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\240\320\260\320\267\320\264\320\265\320\273", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidgetReady->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\237\320\276\320\273", 0));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidgetReady->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202 \320\276\321\202", 0));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidgetReady->horizontalHeaderItem(4);
        ___qtablewidgetitem11->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\222\320\276\320\267\321\200\320\260\321\201\321\202 \320\264\320\276", 0));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidgetReady->horizontalHeaderItem(5);
        ___qtablewidgetitem12->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\222\320\265\321\201 \320\276\321\202", 0));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidgetReady->horizontalHeaderItem(6);
        ___qtablewidgetitem13->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\222\320\265\321\201 \320\264\320\276", 0));
        pushButtonShowGridRight->setText(QApplication::translate("DialogAwardSelectTournamentCategories", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\201\320\265\321\202\320\272\321\203", 0));
        Q_UNUSED(DialogAwardSelectTournamentCategories);
    } // retranslateUi

};

namespace Ui {
    class DialogAwardSelectTournamentCategories: public Ui_DialogAwardSelectTournamentCategories {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGAWARDSELECTTOURNAMENTCATEGORIES_H

#include "fighting_pairs.h"
#include "bd_utils.h"

#include <QLabel>
#include <QGridLayout>
#include <QListWidget>
#include <QDebug>
#include <algorithm>


FightingPairs::FightingPairs(const QSqlDatabase &_database, long long _tournamentUID, QWidget* parent) :
    QDialog(parent),
    database(_database),
    tournamentUID(_tournamentUID)
{
    qListWidget = new QListWidget;
    globalListsOfPairs = BDUtils::getListsOfPairs(database, tournamentUID);
    for(const QVector<BDUtils::Fighing>& x : globalListsOfPairs)
    {
        QString str = BDUtils::get_NAME_FROM_TOURNAMENT_CATEGORIES(database, x[0].TOURNAMENT_CATEGORIES_FK) +
                "; кол-во пар: " + QString::number(x.size());
        qListWidget->addItem(str);
    }
    qListWidget->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);


    ringSpinBox = new QSpinBox;
    ringSpinBox->setMaximum(100);
    ringSpinBox->setMinimum(1);
    ringSpinBox->setValue(3);


    qPushButton = new QPushButton("GO!");

    QGridLayout *qGridLayout = new QGridLayout;
    qGridLayout->addWidget(qListWidget, 0, 0, 1, 2);
    qGridLayout->addWidget(new QLabel(QString("Кол-во рингов:")), 1, 0, Qt::AlignRight);
    qGridLayout->addWidget(ringSpinBox, 1, 1);
    qGridLayout->addWidget(qPushButton, 2, 0, 1, 2);

    setLayout(qGridLayout);

    resize(800, 800);
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);


    connect(qPushButton, SIGNAL(clicked()), SLOT(onGoPress()));
}

FightingPairs::~FightingPairs()
{

}



void FightingPairs::onGoPress()
{
    QVector<QVector<BDUtils::Fighing> > listsOfPairs;
    for(QModelIndex index : qListWidget->selectionModel()->selectedIndexes())
    {
        int row = index.row();
        qDebug() << "row: " << row;
        listsOfPairs.push_back(globalListsOfPairs[row]);
    }

    std::random_shuffle(listsOfPairs.begin(), listsOfPairs.end());
    std::sort(std::begin(listsOfPairs), std::end(listsOfPairs),
              [this] (const QVector<BDUtils::Fighing>& lhs, const QVector<BDUtils::Fighing>& rhs) {
        return
            BDUtils::get__AGE_TILL__FROM__TOURNAMENT_CATEGORIES(database, lhs[0].TOURNAMENT_CATEGORIES_FK) <
            BDUtils::get__AGE_TILL__FROM__TOURNAMENT_CATEGORIES(database, rhs[0].TOURNAMENT_CATEGORIES_FK);
    });

    QVector<BDUtils::Fighing> fighing;
    for (QVector<BDUtils::Fighing>& a : listsOfPairs)
    {
        std::random_shuffle(a.begin(), a.end());
        std::sort(std::begin(a), std::end(a), [] (const BDUtils::Fighing& lhs, const BDUtils::Fighing& rhs) {
            return lhs.VERTEX < rhs.VERTEX;
        });
        fighing += a;
    }

    int ringCount = ringSpinBox->value();

}


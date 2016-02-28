#include "fighting_pairs.h"
#include "db_utils.h"
#include "excel_utils.h"

#include <QLabel>
#include <QGridLayout>
#include <QListWidget>
#include <QDebug>
#include <algorithm>
#include <QAxWidget>
#include <QAxObject>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonValuePtr>
#include <QJsonValueRef>
#include <QJsonValueRefPtr>
#include <QVariantMap>
#include <QFileDialog>

#include <QSqlQuery>
#include <QSqlError>

#include <algorithm>


FightingPairs::FightingPairs(const QSqlDatabase &_database, long long _tournamentUID, QWidget* parent) :
    QDialog(parent),
    database(_database),
    tournamentUID(_tournamentUID)
{
    qListWidget = new QListWidget;
    globalListsOfPairs = DBUtils::getListsOfPairs(database, tournamentUID);
    for(const QVector<DBUtils::Fighing>& x : globalListsOfPairs)
    {
        QSqlQuery queryCOUNT("SELECT count() AS COUNT FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? AND IS_VALID = ? GROUP BY TOURNAMENT_CATEGORY_FK", database);
        queryCOUNT.bindValue(0, x[0].TOURNAMENT_CATEGORIES_FK);
        queryCOUNT.bindValue(1, 1);
        if (!queryCOUNT.exec())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryCOUNT.lastError().text() << " " << queryCOUNT.lastQuery();
            continue;
        }
        int count = 0;
        if (queryCOUNT.next())
            count = queryCOUNT.value("COUNT").toInt();
        QVector<int> fights;
        for (int fight = 1; ; fight *= 2)
        {
            if (count < 2 * fight)
            {
                if (0 < count - fight) fights.push_back(count - fight);
                break;
            }
            else
                fights.push_back(fight);
        }
        std::reverse(fights.begin(), fights.end());
        QString foo;
        foo += "(";
        for (int x : fights)
            foo = foo + " " + QString::number(x);
        foo += ")";


        QString str = DBUtils::get__NAME_OF_TOURNAMENT_CATEGORIES(database, x[0].TOURNAMENT_CATEGORIES_FK) +
                "; кол-во пар: " + QString::number(x.size()) +
                "; кол-во участников: " + QString::number(count) +
                "; распределение боёв: " + foo
                ;
        qListWidget->addItem(str);
    }
    qListWidget->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);


    ringSpinBox = new QSpinBox;
    ringSpinBox->setMaximum(100);
    ringSpinBox->setMinimum(1);
    ringSpinBox->setValue(1);


    qPushButton = new QPushButton("GO!");

    QGridLayout *qGridLayout = new QGridLayout;
    qGridLayout->addWidget(qListWidget, 0, 0, 1, 2);
    qGridLayout->addWidget(new QLabel(QString("Кол-во рингов:")), 1, 0, Qt::AlignRight);
    qGridLayout->addWidget(ringSpinBox, 1, 1);
    qGridLayout->addWidget(new QLabel(QString("Дата + {утро, день, вечер}:")), 2, 0, Qt::AlignRight);
    qGridLayout->addWidget(qLineEdit = new QLineEdit(), 2, 1);
    qGridLayout->addWidget(qPushButton, 3, 0, 1, 2);

    setLayout(qGridLayout);

    resize(800, 800);
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);


    connect(qPushButton, SIGNAL(clicked()), SLOT(onGoPress()));
}

FightingPairs::~FightingPairs()
{

}

void FightingPairs::printInExcel(QAxObject *sheet, const QVector<DBUtils::Fighing>& fighting, int ring)
{


    int currentRow = 1;

    ExcelUtils::setValue(sheet, currentRow, 1, "Состав пар");
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    ExcelUtils::setValue(sheet, currentRow, 1, qLineEdit->text());
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    ExcelUtils::setValue(sheet, currentRow, 1, "Ринг #" + QString::number(ring));
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    for (int i = 0, pair = 1; i < fighting.size(); ++i, ++pair)
    {
        DBUtils::Fighing f = fighting[i];
        if (i == 0 || f.TOURNAMENT_CATEGORIES_FK != fighting[i - 1].TOURNAMENT_CATEGORIES_FK)
        {
            ++currentRow;
            ++currentRow;

            ExcelUtils::setValue(sheet, currentRow, 1,DBUtils::getField(database, "NAME", "TYPES", DBUtils::getField(database, "TYPE_FK", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK)));
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
            ++currentRow;

            ExcelUtils::setValue(sheet, currentRow, 1, "Возраст: " +
                                 QString::number(DBUtils::get__AGE_FROM(database, f.TOURNAMENT_CATEGORIES_FK)) +
                                 " - " +
                                 QString::number(DBUtils::get__AGE_TILL(database, f.TOURNAMENT_CATEGORIES_FK))
                                 );
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
            ++currentRow;

            ExcelUtils::setValue(sheet, currentRow, 1, "Вес: " +
                                 DBUtils::get__WEIGHT_FROM(database, f.TOURNAMENT_CATEGORIES_FK) +
                                 " - " +
                                 DBUtils::get__WEIGHT_TILL(database, f.TOURNAMENT_CATEGORIES_FK) +
                                 " кг"
                                 );
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
            ++currentRow;
        }

        ExcelUtils::setValue(sheet, currentRow, 1, QString::number(pair));
        ExcelUtils::setValue(sheet, currentRow, 2, DBUtils::getField(database, "SECOND_NAME", "ORDERS", f.UID0) + " " + DBUtils::getField(database, "FIRST_NAME", "ORDERS", f.UID0) + "(" +
                             DBUtils::getField(database, "NAME", "REGIONS", DBUtils::getField(database, "REGION_FK", "ORDERS", f.UID0)) +
                             ")");
        ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::getField(database, "SECOND_NAME", "ORDERS", f.UID1) + " " + DBUtils::getField(database, "FIRST_NAME", "ORDERS", f.UID1) + "(" +
                             DBUtils::getField(database, "NAME", "REGIONS", DBUtils::getField(database, "REGION_FK", "ORDERS", f.UID1)) +
                             ")");
        ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, 3);
        ++currentRow;
    }

    for (int column = 1; column <= 3; ++column)
        ExcelUtils::setColumnAutoFit(sheet, column);
}

void FightingPairs::printInJSON(const QVector<DBUtils::Fighing>& fighting, int ring, const QString& existingDirectory)
{
    QJsonArray arr;
    int fightingId = 1;
    for (const DBUtils::Fighing& f : fighting)
    {
        QJsonObject a;
        a["nameOfLeftFighter" ] = DBUtils::getField(database, "SECOND_NAME", "ORDERS", f.UID0) + " " + DBUtils::getField(database, "FIRST_NAME", "ORDERS", f.UID0);
        a["nameOfRightFighter"] = DBUtils::getField(database, "SECOND_NAME", "ORDERS", f.UID1) + " " + DBUtils::getField(database, "FIRST_NAME", "ORDERS", f.UID1);

        a["fightId"] = fightingId;
        a["categoryOfFighting"] = DBUtils::getField(database, "WEIGHT_TILL", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);

        a["countOfRounds"  ] = DBUtils::getField(database, "ROUND_COUNT"     , "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);
        a["durationOfRound"] = DBUtils::getField(database, "DURATION_FIGHING", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);
        a["durationOfBreak"] = DBUtils::getField(database, "DURATION_BREAK"  , "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);

        a["countryOfLeftFighter" ] = DBUtils::getField(database, "NAME", "REGIONS", DBUtils::getField(database, "REGION_FK", "ORDERS", f.UID0));
        a["countryOfRightFighter"] = DBUtils::getField(database, "NAME", "REGIONS", DBUtils::getField(database, "REGION_FK", "ORDERS", f.UID1));

        a["TOURNAMENT_CATEGORIES_FK"] = f.TOURNAMENT_CATEGORIES_FK;
        a["VERTEX"] = f.VERTEX;
        a["orderUID_left"] = f.UID0;
        a["orderUID_right"] = f.UID1;

        arr.push_back(a);
        //
        ++fightingId;
    }

    const QString path = existingDirectory + QDir::separator() + "ring " + QString::number(ring) + ".json";
    QFile saveFile(path);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        qDebug() << saveFile.errorString();
        //qDebug() << path;
        return;
    }
    qDebug() << "writing: " << saveFile.write(QJsonDocument(arr).toJson()) << "БайТ";
}



void FightingPairs::onGoPress()
{
    QString existingDirectory = QFileDialog::getExistingDirectory(this);

    QVector<QVector<DBUtils::Fighing> > listsOfPairs;
    for(QModelIndex index : qListWidget->selectionModel()->selectedIndexes())
    {
        int row = index.row();
        qDebug() << "row: " << row;
        listsOfPairs.push_back(globalListsOfPairs[row]);
    }

    std::random_shuffle(listsOfPairs.begin(), listsOfPairs.end());
    std::sort(std::begin(listsOfPairs), std::end(listsOfPairs),
              [this] (const QVector<DBUtils::Fighing>& lhs, const QVector<DBUtils::Fighing>& rhs) {
        return
                DBUtils::get__AGE_TILL(database, lhs[0].TOURNAMENT_CATEGORIES_FK) <
                DBUtils::get__AGE_TILL(database, rhs[0].TOURNAMENT_CATEGORIES_FK);
    });

    QVector<DBUtils::Fighing> fighing;
    for (QVector<DBUtils::Fighing>& a : listsOfPairs)
    {
        std::random_shuffle(a.begin(), a.end());
        std::sort(std::begin(a), std::end(a), [] (const DBUtils::Fighing& lhs, const DBUtils::Fighing& rhs) {
            return lhs.VERTEX > rhs.VERTEX;
        });
        fighing += a;
    }


    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");

    for (int ringCount = ringSpinBox->value(), idRind = 1; 1 <= ringCount; --ringCount, ++idRind)
    {
        int time = 0;
        for (const DBUtils::Fighing& f : fighing)
        {
            time += DBUtils::get__DURATION_FIGHING(database, f.TOURNAMENT_CATEGORIES_FK) *
                    DBUtils::get__ROUND_COUNT(database, f.TOURNAMENT_CATEGORIES_FK) +

                    DBUtils::get__DURATION_BREAK(database, f.TOURNAMENT_CATEGORIES_FK) *
                    (DBUtils::get__ROUND_COUNT(database, f.TOURNAMENT_CATEGORIES_FK) - 1);
        }
        time /= ringCount;

        int curTime = 0;
        QVector<DBUtils::Fighing> curFighing;
        while (fighing.size())
        {
            DBUtils::Fighing f = fighing.front();
            curTime += DBUtils::get__DURATION_FIGHING(database, f.TOURNAMENT_CATEGORIES_FK) *
                       DBUtils::get__ROUND_COUNT(database, f.TOURNAMENT_CATEGORIES_FK) +

                       DBUtils::get__DURATION_BREAK(database, f.TOURNAMENT_CATEGORIES_FK) *
                       (DBUtils::get__ROUND_COUNT(database, f.TOURNAMENT_CATEGORIES_FK) - 1);
            curFighing += f;
            fighing.pop_front();
            if (time <= curTime && 2 <= ringCount)
                break;
        }

        sheets->querySubObject("Add");
        QAxObject *sheet = sheets->querySubObject( "Item( int )", 1);
        printInExcel(sheet, curFighing, idRind);
        printInJSON(curFighing, idRind, existingDirectory);

        delete sheet;
    }

    delete sheets;
    delete workbook;
    delete workbooks;
}


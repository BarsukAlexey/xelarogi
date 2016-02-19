#include "weighing_protocol.h"
#include "db_utils.h"
#include "excel_utils.h"

#include <QAxWidget>
#include <QAxObject>
#include <QStringList>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>


WeighingProtocol::WeighingProtocol(const QSqlDatabase& database, const long long tournamentUID, QObject* parent)
    : QObject(parent)
{
    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");

    const int countColumns = 9;

    for (const long long uidCategory : DBUtils::get_UIDs_of_TOURNAMENT_CATEGORIES(database, tournamentUID))
    {
        QVector<DBUtils::NodeOfTournirGrid> leafOFTree = DBUtils::getLeafOFTree(database, uidCategory);
        if (leafOFTree.empty()) continue;

        sheets->querySubObject("Add");
        QAxObject *sheet = sheets->querySubObject( "Item( int )", 1);

        int currentRow = 2;

        ExcelUtils::setValue  (sheet, currentRow, 1, DBUtils::getNameTournamentByUID(database, tournamentUID));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        ExcelUtils::setValue  (sheet, currentRow, 1, "Протокол взвешивания");
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        ExcelUtils::setValue  (sheet, currentRow, 1, "Раздел: " + DBUtils::getField(database, "NAME", "TYPES", DBUtils::getField(database, "TYPE_FK", "TOURNAMENT_CATEGORIES", uidCategory)));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        ExcelUtils::setValue  (sheet, currentRow, 1, "Возраст от " + DBUtils::getField(database, "AGE_FROM", "TOURNAMENT_CATEGORIES", uidCategory) + " до " + DBUtils::getField(database, "AGE_TILL", "TOURNAMENT_CATEGORIES", uidCategory));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        ExcelUtils::setValue  (sheet, currentRow, 1, "Вес от " + DBUtils::getField(database, "WEIGHT_FROM", "TOURNAMENT_CATEGORIES", uidCategory) + " до " + DBUtils::getField(database, "WEIGHT_TILL", "TOURNAMENT_CATEGORIES", uidCategory));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        ExcelUtils::setValue  (sheet, currentRow, 1, "Пол: " + DBUtils::getField(database, "SHORTNAME", "SEXES", DBUtils::getField(database, "SEX_FK", "TOURNAMENT_CATEGORIES", uidCategory)));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        QStringList heads;
        heads << "#" << "Фамилия, Имя" << "Дата рождения" << "Город" << "Клуб" << "Спортивный\r\nразряд" << "Вес" << "Тренер" << "Номер\r\nжеребьёвки";
        for (int i = 0, column = 1; i < heads.size(); ++i, ++column)
            ExcelUtils::setValue(sheet, currentRow, column, heads[i]);
        ++currentRow;

        int maxVertex = 1;
        for(const DBUtils::NodeOfTournirGrid& leaf : leafOFTree) maxVertex = qMax(maxVertex, leaf.v);

        int number = 1;
        for(const DBUtils::NodeOfTournirGrid& leaf : leafOFTree)
        {
            ExcelUtils::setValue(sheet, currentRow, 1, QString::number(number));
            ExcelUtils::setValue(sheet, currentRow, 2, DBUtils::getSecondNameAndOneLetterOfName(database, leaf.UID));
            ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::getFieldDate(database, "BIRTHDATE", "ORDERS", leaf.UID));
            ExcelUtils::setValue(sheet, currentRow, 4, DBUtils::getField(database, "NAME", "REGIONS", DBUtils::getField(database, "REGION_FK", "ORDERS", leaf.UID)));
            ExcelUtils::setValue(sheet, currentRow, 5, DBUtils::getField(database, "NAME", "CLUBS", DBUtils::getField(database, "CLUB_FK", "ORDERS", leaf.UID)));
            ExcelUtils::setValue(sheet, currentRow, 6, DBUtils::getField(database, "NAME", "SPORT_CATEGORIES", DBUtils::getField(database, "SPORT_CATEGORY_FK", "ORDERS", leaf.UID)));
            ExcelUtils::setValue(sheet, currentRow, 7, DBUtils::getField(database, "WEIGHT", "ORDERS", leaf.UID));
            ExcelUtils::setValue(sheet, currentRow, 8, DBUtils::getField(database, "LAST_NAME", "COACHS", DBUtils::getField(database, "COACH_FK", "ORDERS", leaf.UID)) + " " + DBUtils::getField(database, "FIRST_NAME", "COACHS", DBUtils::getField(database, "COACH_FK", "ORDERS", leaf.UID)).left(1) + ".");
            ExcelUtils::setValue(sheet, currentRow, 9, QString::number(maxVertex - leaf.v + 1));
            ++currentRow;
            ++number;
        }


//        QSqlQuery querySEX_FK("SELECT DISTINCT SEX_FK FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? AND TYPE_FK = ? AND AGE_FROM = ? ORDER BY SEX_FK", database);
//        querySEX_FK.bindValue(0, tournamentUID);
//        querySEX_FK.bindValue(1, TYPE_FK);
//        querySEX_FK.bindValue(2, AGE_FROM);
//        if (!querySEX_FK.exec())
//        {
//            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << querySEX_FK.lastError().text() << " " << querySEX_FK.lastQuery();
//            return;
//        }
//        while (querySEX_FK.next())
//        {
//            long long SEX_FK = querySEX_FK.value("SEX_FK").toLongLong();

//            ExcelUtils::setValue  (sheet, currentRow, 1, DBUtils::get_SHORTNAME_FROM_SEXES(database, SEX_FK), 0);
//            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());
//            ++currentRow;

//            QSqlQuery queryWEIGHT_FROM("SELECT WEIGHT_FROM, WEIGHT_TILL FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? AND TYPE_FK = ?  AND AGE_FROM = ? AND SEX_FK = ? GROUP BY WEIGHT_FROM, WEIGHT_TILL ORDER BY WEIGHT_FROM", database);
//            queryWEIGHT_FROM.bindValue(0, tournamentUID);
//            queryWEIGHT_FROM.bindValue(1, TYPE_FK);
//            queryWEIGHT_FROM.bindValue(2, AGE_FROM);
//            queryWEIGHT_FROM.bindValue(3, SEX_FK);
//            if (!queryWEIGHT_FROM.exec())
//            {
//                qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryWEIGHT_FROM.lastError().text() << " " << queryWEIGHT_FROM.lastQuery();
//                return;
//            }



//            while (queryWEIGHT_FROM.next())
//            {
//                QString WEIGHT_FROM = queryWEIGHT_FROM.value("WEIGHT_FROM").toString();
//                QString WEIGHT_TILL = queryWEIGHT_FROM.value("WEIGHT_TILL").toString();

//                ExcelUtils::setValue(sheet, currentRow, 1, WEIGHT_FROM + " - " + WEIGHT_TILL + " кг");
//                ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());


//                QSqlQuery queryTOURNAMENT_CATEGORIES_UID("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? AND TYPE_FK = ? AND SEX_FK = ? AND AGE_FROM = ? AND WEIGHT_FROM = ?", database);
//                queryTOURNAMENT_CATEGORIES_UID.bindValue(0, tournamentUID);
//                queryTOURNAMENT_CATEGORIES_UID.bindValue(1, TYPE_FK);
//                queryTOURNAMENT_CATEGORIES_UID.bindValue(2, SEX_FK);
//                queryTOURNAMENT_CATEGORIES_UID.bindValue(3, AGE_FROM);
//                queryTOURNAMENT_CATEGORIES_UID.bindValue(4, WEIGHT_FROM);
//                if (!queryTOURNAMENT_CATEGORIES_UID.exec() || !queryTOURNAMENT_CATEGORIES_UID.next()){
//                    qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryTOURNAMENT_CATEGORIES_UID.lastError().text() << " " << queryTOURNAMENT_CATEGORIES_UID.lastQuery();
//                    return;
//                }

//                long long UID_TOURNAMENT_CATEGORY = queryTOURNAMENT_CATEGORIES_UID.value("UID").toLongLong();

//                QSqlQuery queryCOUNT("SELECT count() AS COUNT FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? AND IS_VALID = ? GROUP BY TOURNAMENT_CATEGORY_FK", database);
//                queryCOUNT.bindValue(0, UID_TOURNAMENT_CATEGORY);
//                queryCOUNT.bindValue(1, "true");
//                if (!queryCOUNT.exec())
//                {
//                    qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryCOUNT.lastError().text() << " " << queryCOUNT.lastQuery();
//                    return;
//                }
//                int count = 0;
//                if (queryCOUNT.next())
//                    count = queryCOUNT.value("COUNT").toInt();
//                //qDebug() << TYPE_FK << AGE_FROM << SEX_FK << WEIGHT_FROM << UID_TOURNAMENT_CATEGORY << ": " << count;

//                ExcelUtils::setValue(sheet, currentRow, 2, QString::number(count));
//                totalPeople += count;


//                if (0 < count)
//                {
//                    QVector<int> fights;
//                    for (int fight = 1; ; fight *= 2)
//                    {
//                        if (count < 2 * fight)
//                        {
//                            if (0 < count - fight) fights.push_back(count - fight);
//                            break;
//                        }
//                        else
//                            fights.push_back(fight);
//                    }

//                    if (fights.size() <= 3 * fights.size() )
//                    {
//                        const int onOneDay = fights.size() / days.size();
//                        int rest = fights.size() % days.size();
//                        for (int d = qMax(0, days.size() - fights.size()); d < days.size(); ++d)
//                        {
//                            for (int f = 0; f < onOneDay + (0 < rest? 1 : 0); ++f)
//                            {
//                                if (!fights.empty())
//                                {
//                                    ExcelUtils::setValue(sheet, currentRow, 3 + 3 * d + f, QString::number(fights.back()));
//                                    totalSum[3 * d + f] += fights.back();
//                                    fights.pop_back();
//                                }
//                            }
//                            if (0 < rest) --rest;
//                        }
//                    }
//                }
//                ++currentRow;
//            }
//        }



        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ExcelUtils::setValue(sheet, currentRow, 1, "Главный судья: " + DBUtils::get_MAIN_JUDGE(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ExcelUtils::setValue(sheet, currentRow, 1, "Главный секретарь: " + DBUtils::get_MAIN_SECRETARY(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ExcelUtils::setValue(sheet, currentRow, 1, "Заместитель главного судьи: " + DBUtils::get_ASSOCIATE_MAIN_JUDGE(database, tournamentUID), 0);
        ++currentRow;

        delete sheet;
    }


    delete sheets;
    delete workbook;
    delete workbooks;
}

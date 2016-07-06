#include "fiting_distribution.h"

#include "db_utils.h"
#include "dialogchosedata.h"
#include "excel_utils.h"
#include "tournamentgriddialog2.h"


#include <QAxObject>
#include <QAxWidget>
#include <QDate>
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>





FitingDistribution::FitingDistribution(const long long tournamentUID)
{
    DialogChoseData dlg(DialogChoseData::Type::fiting_distribution);
    if (dlg.exec() != QDialog::Accepted)
        return;
    translate = dlg.getTranslations();


    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");

    QStringList days = DBUtils::get_DAYS_FROM_TOURNAMENTS(tournamentUID);


    QSqlQuery queryTYPE_FK_AGE_FROM("SELECT MAX(UID) as MAX_UID_TC, TYPE_FK, AGE_FROM, AGE_TILL "
                                    "FROM TOURNAMENT_CATEGORIES "
                                    "WHERE TOURNAMENT_FK = ? "
                                    "GROUP BY TYPE_FK, AGE_FROM, AGE_TILL "
                                    "ORDER BY TYPE_FK, AGE_FROM, AGE_TILL");
    queryTYPE_FK_AGE_FROM.addBindValue(tournamentUID);
    if (!queryTYPE_FK_AGE_FROM.exec())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryTYPE_FK_AGE_FROM.lastError().text() << queryTYPE_FK_AGE_FROM.lastQuery();
        return ;
    }
    while (queryTYPE_FK_AGE_FROM.next())
    {
        long long TYPE_FK = queryTYPE_FK_AGE_FROM.value("TYPE_FK").toLongLong();
        QString AGE_FROM = queryTYPE_FK_AGE_FROM.value("AGE_FROM").toString();
        QString AGE_TILL = queryTYPE_FK_AGE_FROM.value("AGE_TILL").toString();
        long long MAX_UID_TC = queryTYPE_FK_AGE_FROM.value("MAX_UID_TC").toLongLong();
        QVector<int> totalSum(3 * days.size());
        int totalPeople = 0;


        QAxObject* sheet = ExcelUtils::addNewSheet(sheets);
        sheet->setProperty("Name", (DBUtils::getField("AGE", "TOURNAMENT_CATEGORIES", MAX_UID_TC) + ", " +
                                    DBUtils::getField("NAME", "TYPES", TYPE_FK)).left(31));

        int currentRow = 1;


        ExcelUtils::setTournamentName(sheet, DBUtils::getTournamentNameAsHeadOfDocument(tournamentUID), currentRow, 1, currentRow, 2 + 3 * days.size());
        ++currentRow;
        ExcelUtils::setValue  (sheet, currentRow, 1,
                               DBUtils::getField("NAME", "TYPES", TYPE_FK) + ", " +
                               DBUtils::getField("AGE", "TOURNAMENT_CATEGORIES", MAX_UID_TC));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());
        ++currentRow;

        initTableHeads(sheet, currentRow, days);

        QSqlQuery querySEX_FK("SELECT AGE_CATEGORY_FK, SEX_FK "
                              "FROM TOURNAMENT_CATEGORIES "
                              "WHERE TOURNAMENT_FK = ? AND TYPE_FK = ? AND AGE_FROM = ? AND AGE_TILL = ? "
                              "GROUP BY AGE_CATEGORY_FK, SEX_FK "
                              "ORDER BY SEX_FK");
        querySEX_FK.addBindValue(tournamentUID);
        querySEX_FK.addBindValue(TYPE_FK);
        querySEX_FK.addBindValue(AGE_FROM);
        querySEX_FK.addBindValue(AGE_TILL);
        if (!querySEX_FK.exec())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << querySEX_FK.lastError().text() << " " << querySEX_FK.lastQuery();
            return;
        }

        while (querySEX_FK.next())
        {
            long long SEX_FK = querySEX_FK.value("SEX_FK").toLongLong();
            long long ageCatUID = querySEX_FK.value("AGE_CATEGORY_FK").toLongLong();

            ExcelUtils::setValue  (sheet, currentRow, 1, DBUtils::getField("NAME", "AGE_CATEGORIES", ageCatUID), 0);
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());
            ++currentRow;

            QSqlQuery queryWEIGHT_FROM("SELECT UID AS UID_TC, WEIGHT_FROM, WEIGHT_TILL "
                                       "FROM TOURNAMENT_CATEGORIES "
                                       "WHERE TOURNAMENT_FK = ? AND TYPE_FK = ?  AND AGE_FROM = ? AND SEX_FK = ? AND AGE_CATEGORY_FK = ? "
                                       "GROUP BY WEIGHT_FROM, WEIGHT_TILL "
                                       "ORDER BY WEIGHT_FROM, WEIGHT_TILL");
            queryWEIGHT_FROM.addBindValue(tournamentUID);
            queryWEIGHT_FROM.addBindValue(TYPE_FK);
            queryWEIGHT_FROM.addBindValue(AGE_FROM);
            queryWEIGHT_FROM.addBindValue(SEX_FK);
            queryWEIGHT_FROM.addBindValue(ageCatUID);
            if (!queryWEIGHT_FROM.exec())
            {
                qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryWEIGHT_FROM.lastError().text() << " " << queryWEIGHT_FROM.lastQuery();
                return;
            }

            while (queryWEIGHT_FROM.next())
            {
                QString UID_TC = queryWEIGHT_FROM.value("UID_TC").toString();
                QString WEIGHT_FROM = queryWEIGHT_FROM.value("WEIGHT_FROM").toString();
                QString WEIGHT_TILL = queryWEIGHT_FROM.value("WEIGHT_TILL").toString();


                ExcelUtils::setValue(sheet, currentRow, 1, DBUtils::getField("WEIGHT", "TOURNAMENT_CATEGORIES", UID_TC));
                ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());


                QSqlQuery queryTOURNAMENT_CATEGORIES_UID("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? AND TYPE_FK = ? AND SEX_FK = ? AND AGE_FROM = ? AND WEIGHT_FROM = ?");
                queryTOURNAMENT_CATEGORIES_UID.bindValue(0, tournamentUID);
                queryTOURNAMENT_CATEGORIES_UID.bindValue(1, TYPE_FK);
                queryTOURNAMENT_CATEGORIES_UID.bindValue(2, SEX_FK);
                queryTOURNAMENT_CATEGORIES_UID.bindValue(3, AGE_FROM);
                queryTOURNAMENT_CATEGORIES_UID.bindValue(4, WEIGHT_FROM);
                if (!queryTOURNAMENT_CATEGORIES_UID.exec() || !queryTOURNAMENT_CATEGORIES_UID.next()){
                    qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryTOURNAMENT_CATEGORIES_UID.lastError().text() << " " << queryTOURNAMENT_CATEGORIES_UID.lastQuery();
                    return;
                }

                long long UID_TOURNAMENT_CATEGORY = queryTOURNAMENT_CATEGORIES_UID.value("UID").toLongLong();

                ExcelUtils::setValue(sheet, currentRow, 1, DBUtils::getNormanWeightRangeFromTOURNAMENT_CATEGORIES(UID_TOURNAMENT_CATEGORY));

                QSqlQuery queryCOUNT("SELECT count() AS COUNT FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? GROUP BY TOURNAMENT_CATEGORY_FK");
                queryCOUNT.bindValue(0, UID_TOURNAMENT_CATEGORY);
                if (!queryCOUNT.exec())
                {
                    qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryCOUNT.lastError().text() << " " << queryCOUNT.lastQuery();
                    return;
                }
                int count = 0;
                if (queryCOUNT.next())
                    count = queryCOUNT.value("COUNT").toInt();
                //qDebug() << TYPE_FK << AGE_FROM << SEX_FK << WEIGHT_FROM << UID_TOURNAMENT_CATEGORY << ": " << count;

                ExcelUtils::setValue(sheet, currentRow, 2, QString::number(count));
                totalPeople += count;


                if (0 < count)
                {
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

                    if (3 * days.size() < fights.size())
                    {
                        QMessageBox::warning(0, QString("Проблема"), QString("Для сетки \"%1\" необходимо %2 боя (боёв), но имеется только %3 день (дня, дней)").arg(DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", UID_TOURNAMENT_CATEGORY)).arg(fights.size()).arg(days.size()));
                    }
                    else if (fights.size() <= 3 * fights.size() )
                    {
                        const int onOneDay = fights.size() / days.size();
                        int rest = fights.size() % days.size();
                        for (int d = qMax(0, days.size() - fights.size()); d < days.size(); ++d)
                        {
                            for (int f = 0; f < onOneDay + (0 < rest? 1 : 0); ++f)
                            {
                                if (!fights.empty())
                                {
                                    ExcelUtils::setValue(sheet, currentRow, 3 + 3 * d + f, QString::number(fights.back()));
                                    totalSum[3 * d + f] += fights.back();
                                    fights.pop_back();
                                }
                            }
                            if (0 < rest) --rest;
                        }
                    }
                }
                ++currentRow;
            }
        }

        ExcelUtils::setValue(sheet, currentRow, 1, translate["Всего:"]);
        ExcelUtils::setValue(sheet, currentRow, 2, QString::number(totalPeople));
        ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());


        for (int i = 0; i < totalSum.size(); ++i)
            if (totalSum[i])
                ExcelUtils::setValue(sheet, currentRow, 3 + i, QString::number(totalSum[i]));
        ++currentRow;
        ++currentRow;

        ExcelUtils::setFooter(sheet, currentRow, 1, 3, 25, dlg.getJudges(), DBUtils::getJudges(tournamentUID));

        ExcelUtils::setColumnAutoFit(sheet, 1);

        ExcelUtils::setPageOrientation(sheet, 2);
        ExcelUtils::setFitToPagesWide(sheet, 1);


        delete sheet;
    }


    delete sheets;
    delete workbook;
    delete workbooks;
}

void FitingDistribution::initTableHeads(QAxObject* sheet, int& currentRow, const QStringList& days)
{

    ExcelUtils::setBorder(sheet, currentRow, 1, currentRow + 1, 2 + 3 * days.size());

    ExcelUtils::setValue(sheet, currentRow, 1, translate["Вес"]);
    ExcelUtils::setValue(sheet, currentRow, 2, translate["Кол-во\nчеловек"]);
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow + 1, 1);
    ExcelUtils::uniteRange(sheet, currentRow, 2, currentRow + 1, 2);

    for (int column = 3, i = 0; i < days.size(); ++i, column += 3)
    {
        ExcelUtils::uniteRange(sheet, currentRow, column, currentRow, column + 2);
        ExcelUtils::setValue(sheet, currentRow, column, days[i]);

        int shift = 0;
        for(const QString& s : {translate["Утро"], translate["День"], translate["Вечер"]})
        {
            ExcelUtils::setValue(sheet, currentRow + 1, column + shift, s);
            ++shift;
        }
    }

    currentRow += 2;
}




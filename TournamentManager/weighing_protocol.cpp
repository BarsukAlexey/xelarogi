#include "weighing_protocol.h"
#include "db_utils.h"
#include "excel_utils.h"

#include <QAxWidget>
#include <QAxObject>
#include <QStringList>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QFile>


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

        ExcelUtils::setValue  (sheet, currentRow, 1, "Возраст: от " + DBUtils::getField(database, "AGE_FROM", "TOURNAMENT_CATEGORIES", uidCategory) + " до " + DBUtils::getField(database, "AGE_TILL", "TOURNAMENT_CATEGORIES", uidCategory));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        ExcelUtils::setValue  (sheet, currentRow, 1, "Вес: от " + DBUtils::getField(database, "WEIGHT_FROM", "TOURNAMENT_CATEGORIES", uidCategory) + " до " + DBUtils::getField(database, "WEIGHT_TILL", "TOURNAMENT_CATEGORIES", uidCategory));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        ExcelUtils::setValue  (sheet, currentRow, 1, "Пол: " + DBUtils::getField(database, "SHORTNAME", "SEXES", DBUtils::getField(database, "SEX_FK", "TOURNAMENT_CATEGORIES", uidCategory)));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        QStringList heads;
        heads << "#" << "Фамилия, Имя" << "Дата\r\nрождения" << "Город" << "Клуб" << "Спортивный\r\nразряд" << "Вес" << "Тренер" << "Номер\r\nжеребьёвки";
        for (int i = 0, column = 1; i < heads.size(); ++i, ++column)
        {
            ExcelUtils::setValue(sheet, currentRow, column, heads[i]);
            ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, heads.size());
            //ExcelUtils::setColumnAutoFit(sheet, column);
        }
        ++currentRow;

        int maxVertex = 1;
        for(const DBUtils::NodeOfTournirGrid& leaf : leafOFTree) maxVertex = qMax(maxVertex, leaf.v);

        int number = 1;
        for(const DBUtils::NodeOfTournirGrid& leaf : leafOFTree)
        {
            ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, heads.size());

            ExcelUtils::setValue(sheet, currentRow, 1, QString::number(number));
            ExcelUtils::setValue(sheet, currentRow, 2, DBUtils::getSecondNameAndOneLetterOfName(database, leaf.UID));
            ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::getFieldDate(database, "BIRTHDATE", "ORDERS", leaf.UID));
            ExcelUtils::setValue(sheet, currentRow, 4, DBUtils::getField(database, "NAME", "REGIONS", DBUtils::getField(database, "REGION_FK", "ORDERS", leaf.UID)));
            ExcelUtils::setValue(sheet, currentRow, 5, DBUtils::getField(database, "NAME", "CLUBS", DBUtils::getField(database, "CLUB_FK", "ORDERS", leaf.UID)));
            ExcelUtils::setValue(sheet, currentRow, 6, DBUtils::getField(database, "SHORTNAME", "SPORT_CATEGORIES", DBUtils::getField(database, "SPORT_CATEGORY_FK", "ORDERS", leaf.UID)));
            ExcelUtils::setValue(sheet, currentRow, 7, DBUtils::getField(database, "WEIGHT", "ORDERS", leaf.UID));
            ExcelUtils::setValue(sheet, currentRow, 8, DBUtils::getField(database, "LAST_NAME", "COACHS", DBUtils::getField(database, "COACH_FK", "ORDERS", leaf.UID)) + " " + DBUtils::getField(database, "FIRST_NAME", "COACHS", DBUtils::getField(database, "COACH_FK", "ORDERS", leaf.UID)).left(1) + ".");
            ExcelUtils::setValue(sheet, currentRow, 9, QString::number(maxVertex - leaf.v + 1));
            ++currentRow;
            ++number;
        }

        for (int i = 0, column = 1; i < heads.size(); ++i, ++column)
        {
            ExcelUtils::setColumnAutoFit(sheet, column);
        }

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ExcelUtils::setValue(sheet, currentRow, 1, "Главный судья: " + DBUtils::get_MAIN_JUDGE(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ExcelUtils::setValue(sheet, currentRow, 1, "Главный секретарь: " + DBUtils::get_MAIN_SECRETARY(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ExcelUtils::setValue(sheet, currentRow, 1, "Заместитель главного судьи: " + DBUtils::get_ASSOCIATE_MAIN_JUDGE(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::setPageOrientation(sheet, 2);

        delete sheet;
    }

    delete sheets;
    delete workbook;
    delete workbooks;
}

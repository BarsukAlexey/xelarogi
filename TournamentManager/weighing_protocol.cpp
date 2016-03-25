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
        QString sheetName = DBUtils::getField("SHORTNAME", "SEXES", DBUtils::getField("SEX_FK", "TOURNAMENT_CATEGORIES", uidCategory)) + "," +
                            DBUtils::getField("NAME", "TYPES", DBUtils::getField("TYPE_FK", "TOURNAMENT_CATEGORIES", uidCategory)) + "," +
                            DBUtils::getField("AGE_FROM", "TOURNAMENT_CATEGORIES", uidCategory) + "-" + DBUtils::getField("AGE_TILL", "TOURNAMENT_CATEGORIES", uidCategory) + "л," +
                            (DBUtils::getNormanWeightRangeFromTOURNAMENT_CATEGORIES(uidCategory).remove(QRegExp(" ")))
                            ;
        sheet->setProperty("Name", sheetName.left(31));

        int currentRow = 1;

//        ExcelUtils::setValue   (sheet, currentRow, 1, DBUtils::getNameTournamentByUID(database, tournamentUID));
//        ExcelUtils::uniteRange (sheet, currentRow, 1, currentRow, countColumns);
//        ExcelUtils::setFontBold(sheet, currentRow, 1, true);
        ExcelUtils::setTournamentName(sheet, DBUtils::getTournamentNameAsHeadOfDocument(database, tournamentUID), currentRow, 1, currentRow, countColumns);
        ++currentRow;

        ExcelUtils::setValue  (sheet, currentRow, 1, "Протокол взвешивания");
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        ExcelUtils::setValue  (sheet, currentRow, 1, "Раздел: " + DBUtils::getField("NAME", "TYPES", DBUtils::getField("TYPE_FK", "TOURNAMENT_CATEGORIES", uidCategory)));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        ExcelUtils::setValue  (sheet, currentRow, 1, "Возраст: от " + DBUtils::getField("AGE_FROM", "TOURNAMENT_CATEGORIES", uidCategory) + " до " + DBUtils::getField("AGE_TILL", "TOURNAMENT_CATEGORIES", uidCategory));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        ExcelUtils::setValue  (sheet, currentRow, 1, "Вес: " + DBUtils::getNormanWeightRangeFromTOURNAMENT_CATEGORIES(uidCategory));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        ExcelUtils::setValue  (sheet, currentRow, 1, "Пол: " + DBUtils::getField("SHORTNAME", "SEXES", DBUtils::getField("SEX_FK", "TOURNAMENT_CATEGORIES", uidCategory)));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, countColumns);
        ++currentRow;

        QStringList heads;
        heads << "#" << "Фамилия, Имя" << "Дата\nрождения" << "Город" << "Клуб" << "Спортивный\nразряд" << "Вес" << "Тренер" << "Номер\nжеребьёвки";
        //heads << "sdsdsdd" << "sdsdsdd" << "sdsdsdd" << "sdsdsdd" << "sdsdsdd" << "sdsdsdd" << "sdsdsdd";
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
            ExcelUtils::setValue(sheet, currentRow, 2, DBUtils::getField("SECOND_NAME", "ORDERS", leaf.UID) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", leaf.UID));
            ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::getFieldDate(database, "BIRTHDATE", "ORDERS", leaf.UID));
            ExcelUtils::setValue(sheet, currentRow, 4, DBUtils::getField("NAME", "REGIONS", DBUtils::getField("REGION_FK", "ORDERS", leaf.UID)));
            ExcelUtils::setValue(sheet, currentRow, 5, DBUtils::getField("NAME", "CLUBS", DBUtils::getField("CLUB_FK", "ORDERS", leaf.UID)));
            ExcelUtils::setValue(sheet, currentRow, 6, DBUtils::getField("NAME", "SPORT_CATEGORIES", DBUtils::getField("SPORT_CATEGORY_FK", "ORDERS", leaf.UID)));
            //ExcelUtils::setValue(sheet, currentRow, 7, DBUtils::getField("WEIGHT", "ORDERS", leaf.UID));
            ExcelUtils::setValue(sheet, currentRow, 7, DBUtils::roundDouble(DBUtils::getField("WEIGHT", "ORDERS", leaf.UID).toDouble(), 3));
            ExcelUtils::setValue(sheet, currentRow, 8, DBUtils::getField("NAME", "COACHS", DBUtils::getField("COACH_FK", "ORDERS", leaf.UID)));
            ExcelUtils::setValue(sheet, currentRow, 9, QString::number(maxVertex - leaf.v + 1));
            ++currentRow;
            ++number;
        }

        for (int i = 0, column = 1; i < heads.size(); ++i, ++column)
        {
            ExcelUtils::setColumnAutoFit(sheet, column);
        }

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2);
        ExcelUtils::setRowHeight(sheet, currentRow, 25);
        ExcelUtils::setValue(sheet, currentRow, 1, "Главный судья: ", 0);
        ExcelUtils::setValue(sheet, currentRow, 4, DBUtils::get_MAIN_JUDGE(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2);
        ExcelUtils::setRowHeight(sheet, currentRow, 25);
        ExcelUtils::setValue(sheet, currentRow, 1, "Главный секретарь: ", 0);
        ExcelUtils::setValue(sheet, currentRow, 4, DBUtils::get_MAIN_SECRETARY(database, tournamentUID), 0);
        ++currentRow;

        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2);
        ExcelUtils::setRowHeight(sheet, currentRow, 25);
        ExcelUtils::setValue(sheet, currentRow, 1, "Зам. главного судьи: ", 0);
        ExcelUtils::setValue(sheet, currentRow, 4, DBUtils::get_ASSOCIATE_MAIN_JUDGE(database, tournamentUID), 0);
        ++currentRow;


        ExcelUtils::setFitToPagesWide(sheet);
        ExcelUtils::setPageOrientation(sheet, 1);
        ExcelUtils::setCenterHorizontally(sheet, true);

        delete sheet;
    }


    delete sheets;
    delete workbook;
    delete workbooks;
}

#include "winner_report.h"





WinnerReport::WinnerReport(const long long tournamentUID, QObject* parent)
    : QObject(parent)
{
    DialogChoseData dlg(DialogChoseData::Type::WinnerReport);
    if (dlg.exec() != QDialog::Accepted)
        return;

    QStringList heads;
    QVector<std::pair<QString, QVector<std::pair<DBUtils::TypeField, QString> > > > data = dlg.getData();
    for (std::pair<QString, QVector<std::pair<DBUtils::TypeField, QString> > > pair : data)
    {
        heads << pair.first;
    }
    if (heads.isEmpty())
        return;


    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");


    QSqlQuery query(
                "SELECT "
                    "TYPE_FK, AGE_FROM, AGE_TILL, SEX_FK, AGE_CATEGORY_FK, MAX(UID) AS MAX_UID_TC "
                "FROM "
                    "TOURNAMENT_CATEGORIES "
                "WHERE "
                    "TOURNAMENT_FK = ? "
                "GROUP BY "
                    "TYPE_FK, AGE_FROM, AGE_TILL, SEX_FK, AGE_CATEGORY_FK "
                "ORDER BY "
                    "TYPE_FK, AGE_TILL, SEX_FK");

    query.addBindValue(tournamentUID);
    if (!query.exec())
    {
        qDebug() << __LINE__ << __PRETTY_FUNCTION__ << query.lastError().text() << query.lastQuery();
        return ;
    }

    while (query.next())
    {

        const long long type_fk    = query.value("TYPE_FK").toLongLong();
        const long long age_from   = query.value("AGE_FROM").toLongLong();
        const long long age_till   = query.value("AGE_TILL").toLongLong();
        const long long sex_fk     = query.value("SEX_FK").toLongLong();
        const long long ageCatUID  = query.value("AGE_CATEGORY_FK").toLongLong();
        const long long MAX_UID_TC = query.value("MAX_UID_TC").toLongLong();

        qDebug() << DBUtils::getField("NAME", "SEXES", sex_fk) << DBUtils::getField("NAME", "TYPES", type_fk) << age_from << age_till;


        std::map<QString, QVector<long long> > stdMap = DBUtils::get_weight_and_orderUIDs(tournamentUID, type_fk, age_from, age_till, sex_fk, dlg.getMaxPlace()).toStdMap();
        if (stdMap.empty()) continue;
//        continue;


        int currentRow = 1;

        QAxObject *sheet = ExcelUtils::addNewSheet(sheets);

        QString sheetName =
                DBUtils::getField("SHORTNAME", "SEXES", sex_fk) + ", " +
                DBUtils::getField("AGE", "TOURNAMENT_CATEGORIES", MAX_UID_TC) + ", " +
                DBUtils::getField("NAME", "TYPES", type_fk);
        sheet->setProperty("Name", sheetName.left(31));

        ExcelUtils::setTournamentName(sheet, DBUtils::getTournamentNameAsHeadOfDocument(tournamentUID), currentRow, 1, currentRow, heads.size());

        ++currentRow;

        ExcelUtils::setValue     (sheet, currentRow, 1, dlg.getTitle());
        ExcelUtils::uniteRange   (sheet, currentRow, 1, currentRow, heads.size());
        ++currentRow;

        ExcelUtils::setValue     (sheet, currentRow, 1,
                                  DBUtils::getField("NAME", "TYPES", type_fk) + ", " +
                                  DBUtils::getField("NAME", "AGE_CATEGORIES", ageCatUID) + ", " +
                                  DBUtils::getField("AGE", "TOURNAMENT_CATEGORIES", MAX_UID_TC));
        ExcelUtils::uniteRange   (sheet, currentRow, 1, currentRow, heads.size());
        ++currentRow;

        {
            int  column = 1;
            for (const QString& s : heads)
            {
                ExcelUtils::setValue(sheet, currentRow, column, s);
                ExcelUtils::setBorder(sheet, currentRow, column, currentRow, column);
                ++column;
            }
            ++currentRow;
        }

        for (const auto & val : stdMap)
        {
            const QString& weight = val.first;

            ExcelUtils::setValue     (sheet, currentRow, 1, weight);
            ExcelUtils::uniteRange   (sheet, currentRow, 1, currentRow, heads.size());
            ++currentRow;
            //qDebug() << "\t" << weight;


            int number = 1;
            for (const long long orderUID : val.second)
            {
                if (orderUID == 0)
                    break;
                for (int column = 0; column < data.size(); ++column)
                {
                    QString string = DBUtils::get(data[column].second, orderUID, number);
                    ExcelUtils::setValue(sheet, currentRow, column + 1, string);
                }

                ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, heads.size());
                ++currentRow;
            }
        }

        for (int column = 1; column <= heads.size(); ++column)
            ExcelUtils::setColumnAutoFit(sheet, column);


        ExcelUtils::setFooter(sheet, currentRow, 1, 3, 25, dlg.getJudges(), DBUtils::getJudges(tournamentUID));

        ExcelUtils::setPageOrientation(sheet, 1);
        ExcelUtils::setCenterHorizontally(sheet, true);

        delete sheet;
    }

    delete sheets;
    delete workbook;
    delete workbooks;
}


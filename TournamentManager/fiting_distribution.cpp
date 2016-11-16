#include "fiting_distribution.h"







FitingDistribution::FitingDistribution(const long long tournamentUID, QObject* parent) :
    QObject(parent)
{
    DialogChoseData dlg(DialogChoseData::Type::fiting_distribution);
    if (dlg.exec() != QDialog::Accepted)
        return;
    translate = dlg.getTranslations();


    QAxWidget excel("Excel.Application");
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");

    QProgressDialog progress;
    progress.setMaximum(DBUtils::get_MAX_UID_TC___TYPE_FK___AGE_FROM___AGE_TILL(tournamentUID).size());
    progress.setWindowModality(Qt::ApplicationModal);
    progress.setMinimumDuration(0);

    int iteration = 1;
    QStringList days = DBUtils::get_DAYS_FROM_TOURNAMENTS(tournamentUID);
    for (const std::tuple<int, int, int, int> tuple : DBUtils::get_MAX_UID_TC___TYPE_FK___AGE_FROM___AGE_TILL(tournamentUID))
    {
        int MAX_UID_TC = std::get<0>(tuple);
        int TYPE_FK    = std::get<1>(tuple);
        int AGE_FROM   = std::get<2>(tuple);
        int AGE_TILL   = std::get<3>(tuple);

        progress.setValue(iteration++);
        if (progress.wasCanceled())
            break;
        QApplication::processEvents();

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

        QSqlQuery* modelAGE_CATEGORY_FK___SEX_FK =
                DBUtils::get___AGE_CATEGORY_FK___SEX_FK(tournamentUID, TYPE_FK, AGE_FROM, AGE_TILL);

        while (modelAGE_CATEGORY_FK___SEX_FK->next())
        {
            int SEX_FK    = modelAGE_CATEGORY_FK___SEX_FK->value("SEX_FK").toInt();
            int ageCatUID = modelAGE_CATEGORY_FK___SEX_FK->value("AGE_CATEGORY_FK").toInt();

            ExcelUtils::setValue  (sheet, currentRow, 1, DBUtils::getField("NAME", "AGE_CATEGORIES", ageCatUID), 0);
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());
            ++currentRow;

            QSqlQuery* modelWEIGHTS =
                    DBUtils::get___WEIGHT_FROM___WEIGHT_TILL(tournamentUID, TYPE_FK, AGE_FROM, AGE_TILL, SEX_FK, ageCatUID);

            while (modelWEIGHTS->next())
            {
                int WEIGHT_FROM = modelWEIGHTS->value("WEIGHT_FROM").toInt();
                int WEIGHT_TILL = modelWEIGHTS->value("WEIGHT_TILL").toInt();

                QSqlQuery* modelUidTc = DBUtils::get___TC_UIDS(tournamentUID, TYPE_FK, AGE_FROM, AGE_TILL, SEX_FK, ageCatUID, WEIGHT_FROM, WEIGHT_TILL);
                while (modelUidTc->next())
                {

                    long long UID_TOURNAMENT_CATEGORY = modelUidTc->value("UID").toLongLong();

                    ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, 2 + 3 * days.size());
                    ExcelUtils::setValue (sheet, currentRow, 1, DBUtils::getField("WEIGHT", "TOURNAMENT_CATEGORIES", UID_TOURNAMENT_CATEGORY));


                    int countPeople = 0;
                    QVector<std::map<int, int>> countFights;
                    for (const DBUtils::NodeOfTournirGrid& node : DBUtils::getNodes(UID_TOURNAMENT_CATEGORY))
                    {
                        if (node.isFight)
                        {
                            int t = 3 * node.DAY_FIGHT + node.TIME_FIGHT;
                            if (countFights.size() <= t) countFights.resize(t + 1);
                            ++countFights[t][Utils::log2(node.v)];
                        }
                        else
                        {
                            ++countPeople;
                            ++totalPeople;
                        }
                    }

                    ExcelUtils::setValue(sheet, currentRow, 2, QString::number(countPeople));

                    for (int i = 0; i < countFights.size(); ++i){
                        if (countFights[i].size())
                        {
                            QString str;
                            for (auto it = countFights[i].rbegin(); it != countFights[i].rend(); ++it)
                            {
                                if (!str.isEmpty()) str += ", ";
                                str += QString::number(it->second);
                                totalSum[i] += it->second;
                            }
                            ExcelUtils::setValue(sheet, currentRow, 3 + i, str);
                        }
                    }

                    ++currentRow;
                }
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


    excel.setProperty("Visible", true);
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




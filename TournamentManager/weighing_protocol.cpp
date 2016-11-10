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


WeighingProtocol::WeighingProtocol(const long long tournamentUID, QObject* parent)
    : QObject(parent)
{
    DialogChoseData dlg(DialogChoseData::Type::weight_report);
    if (dlg.exec() != QDialog::Accepted)
        return;

    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");





    for (const long long uidTC: DBUtils::getTournamentCategoryUIDs(tournamentUID))
    {
        QVector<DBUtils::NodeOfTournirGrid> leafOFTree = DBUtils::getLeafOFTree(uidTC);
        QStringList heads;
        QVector<std::pair<QString, QVector<std::pair<DBUtils::TypeField, QString> > > > data = dlg.getData();
        for (std::pair<QString, QVector<std::pair<DBUtils::TypeField, QString> > > pair : data)
        {
            heads << pair.first;
        }
        if (heads.isEmpty())
            continue;

        if (leafOFTree.empty()) continue;


        QAxObject *sheet = ExcelUtils::addNewSheet(sheets);
        sheet->setProperty("Name", DBUtils::getNameForExcelSheet(uidTC));



        int currentRow = 1;

        ExcelUtils::setTournamentName(sheet, DBUtils::getTournamentNameAsHeadOfDocument(tournamentUID), currentRow, 1, currentRow, heads.size());
        ++currentRow;

        ExcelUtils::setValue   (sheet, currentRow, 1, dlg.getTitle());
        ExcelUtils::uniteRange (sheet, currentRow, 1, currentRow, heads.size());
        ExcelUtils::setFontBold(sheet, currentRow, 1, true);
        ++currentRow;

        ExcelUtils::setValue  (sheet, currentRow, 1, DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", uidTC));
        ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, heads.size());
        ++currentRow;



        for (int i = 0, column = 1; i < heads.size(); ++i, ++column)
        {
            ExcelUtils::setValue (sheet, currentRow, column, heads[i]);
            ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, heads.size());
        }
        ++currentRow;

        int number = 1;
        if (0 < heads.size())
        {
            for(const DBUtils::NodeOfTournirGrid& leaf : leafOFTree)
            {
                ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, heads.size());

                for (int column = 0; column < data.size(); ++column)
                {
                    QString string = DBUtils::get(data[column].second, leaf.UID, number);
                    ExcelUtils::setValue(sheet, currentRow, column + 1, string);
                }
                ++currentRow;
                ++number;
            }
        }

        for (int i = 0; i < heads.size(); ++i)
        {
            ExcelUtils::setColumnAutoFit(sheet, i + 1);
        }

        ExcelUtils::setFooter(sheet, currentRow, 1, 3, 25, dlg.getJudges(), DBUtils::getJudges(tournamentUID));

        ExcelUtils::setFitToPagesWide(sheet);
        ExcelUtils::setPageOrientation(sheet, 1);
        ExcelUtils::setCenterHorizontally(sheet, true);

        delete sheet;
    }

    delete sheets;
    delete workbook;
    delete workbooks;
}

#include "excel_utils.h"

void ExcelUtils::uniteRange(QAxObject* sheet, int row0, int column0, int row1, int column1)
{
    QAxObject* cell1 = sheet->querySubObject("Cells(QVariant&, QVariant&)", row0, column0);
    QAxObject* cell2 = sheet->querySubObject("Cells(QVariant&, QVariant&)", row1, column1);
    QAxObject* range = sheet->querySubObject("Range(const QVariant&, const QVariant&)", cell1->asVariant(), cell2->asVariant() );
    range->dynamicCall("Select()");
    range->dynamicCall("MergeCells", true);
    range->dynamicCall("HorizontalAlignment", -4108);
    delete range;
    delete cell2;
    delete cell1;
}

void ExcelUtils::setValue(QAxObject* sheet, int row, int column, QString text)
{
    QAxObject *cell = sheet->querySubObject( "Cells( int, int )", row, column);
    cell->setProperty("Value", text);
    delete cell;
}

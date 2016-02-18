#include "excel_utils.h"

#include <QVector>


void ExcelUtils::uniteRange(QAxObject* sheet, int row0, int column0, int row1, int column1)
{
    QAxObject* cell1 = sheet->querySubObject("Cells(QVariant&, QVariant&)", row0, column0);
    QAxObject* cell2 = sheet->querySubObject("Cells(QVariant&, QVariant&)", row1, column1);
    QAxObject* range = sheet->querySubObject("Range(const QVariant&, const QVariant&)", cell1->asVariant(), cell2->asVariant() );
    range->dynamicCall("Select()");
    range->dynamicCall("MergeCells", true);
    //range->dynamicCall("HorizontalAlignment", -4108);
    delete range;
    delete cell2;
    delete cell1;
}

void ExcelUtils::setValue(QAxObject* sheet, int row, int column, QString text, int hAligment, int vAligment)
{
    QAxObject *cell = sheet->querySubObject( "Cells( int, int )", row, column);
    cell->setProperty("Value", text);

    QVector<int> a; a << -4131 << -4108 << -4152;
    cell->dynamicCall("HorizontalAlignment", a[hAligment]);

    QVector<int> b; b << -4160 << -4108 << -4107; // -4160 Выравнивание по центру: -4108 Выравнивание по нижнему краю: -4107
    cell->dynamicCall("VerticalAlignment", b[vAligment]);

    delete cell;
}

void ExcelUtils::setBorder(QAxObject* sheet, int row0, int column0, int row1, int column1)
{
    QAxObject* cell1 = sheet->querySubObject("Cells(QVariant&, QVariant&)", row0, column0);
    QAxObject* cell2 = sheet->querySubObject("Cells(QVariant&, QVariant&)", row1, column1);
    QAxObject* range = sheet->querySubObject("Range(const QVariant&, const QVariant&)", cell1->asVariant(), cell2->asVariant() );


    // xlEdgeTop(верхняя граница) (xlEdgeLeft) левая,
    // (xlEdgeRight) правая,(xlEdgeBottom) нижняя
    // и 2 диагонали (xlDiagonalDown) (xlDiagonalUp)
    QAxObject *border = range->querySubObject("Borders()");
    // тип линии (там пунктиры,сплошная и так далее)
    border->setProperty("LineStyle",1);
    // толщина
    border->setProperty("Weight",2);
}


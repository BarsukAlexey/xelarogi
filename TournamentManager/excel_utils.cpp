#include "excel_utils.h"

#include <QVector>
#include <QFile>
#include <QDebug>
#include <QVariant>
#include <QDir>



void ExcelUtils::uniteRange(QAxObject* sheet, int row0, int column0, int row1, int column1)
{
    QAxObject* cell1 = sheet->querySubObject("Cells(QVariant&, QVariant&)", row0, column0);
    QAxObject* cell2 = sheet->querySubObject("Cells(QVariant&, QVariant&)", row1, column1);
    QAxObject* range = sheet->querySubObject("Range(const QVariant&, const QVariant&)", cell1->asVariant(), cell2->asVariant() );
    range->dynamicCall("Select()");
    range->dynamicCall("MergeCells", true);
    delete range;
    delete cell2;
    delete cell1;
}

void ExcelUtils::setValue(QAxObject* sheet, int row, int column, QString text, int hAligment, int vAligment)
{
    if (text.simplified().isEmpty()) return;

    QAxObject *cell = sheet->querySubObject( "Cells( int, int )", row, column);
    cell->setProperty("NumberFormat","@"); // ctrl+1 -> "формат ячеек" -> текстовый
    // теперь excel никогда число в дату не исправит !

    cell->setProperty("Value", text);

    QVector<int> a; a << -4131 << -4108 << -4152;
    cell->dynamicCall("HorizontalAlignment", a[hAligment]);

    QVector<int> b; b << -4160 << -4108 << -4107; // -4160 Выравнивание по центру: -4108 Выравнивание по нижнему краю: -4107
    cell->dynamicCall("VerticalAlignment", b[vAligment]);

    delete cell;
}

void ExcelUtils::setBorder(QAxObject* sheet, int row0, int column0, int row1, int column1, int Weight, Border border2)
{
    QAxObject* cell1 = sheet->querySubObject("Cells(QVariant&, QVariant&)", row0, column0);
    QAxObject* cell2 = sheet->querySubObject("Cells(QVariant&, QVariant&)", row1, column1);
    QAxObject* range = sheet->querySubObject("Range(const QVariant&, const QVariant&)", cell1->asVariant(), cell2->asVariant() );

    QAxObject *borders = range->querySubObject( ("Borders(" + bordertoString(border2) + ")").toStdString().c_str() );
    // тип линии (там пунктиры,сплошная и так далее)
    borders->setProperty("LineStyle", 1);
    // толщина
    borders->setProperty("Weight", Weight);
}

void ExcelUtils::setColumnAutoFit(QAxObject* sheet, int column)
{
    QAxObject *pColumn = sheet->querySubObject("Columns(QVariant&)", column);
    pColumn->dynamicCall("AutoFit()");
    delete pColumn;
}

void ExcelUtils::setRowAutoFit(QAxObject* sheet, int row)
{
    QAxObject *pRow = sheet->querySubObject("Rows(QVariant&)", row);
    pRow->dynamicCall("AutoFit()");
    delete pRow;
}

void ExcelUtils::setRowHeight(QAxObject* sheet, int row, int height)
{
//    QAxObject *rangec = sheet->querySubObject( "Range(const QVariant&)",QVariant("A1"));
//    // получаю указатель на строку
//    QAxObject *razmer = rangec->querySubObject("Rows");
//    // устанавливаю её размер.
//    razmer->setProperty("RowHeight",100);
    QAxObject *pRow = sheet->querySubObject("Rows(QVariant&)", row);
    pRow->setProperty("RowHeight", height);
    delete pRow;
}

void ExcelUtils::setColumnWidth(QAxObject* sheet, int column, int width)
{
    QAxObject *pRow = sheet->querySubObject("Columns(QVariant&)", column);
    pRow->setProperty("ColumnWidth", width);
    delete pRow;
}

// 1 - портретная, 2 - альбомная
void ExcelUtils::setPageOrientation(QAxObject* sheet, int orientation)
{
    QAxObject *pageSetup = sheet->querySubObject("PageSetup");
    pageSetup->dynamicCall("SetOrientation(XlPageOrientation)", orientation);
    delete pageSetup;
}

void ExcelUtils::setWrapText(QAxObject* sheet, int row, int column)
{
    QAxObject* cell = sheet->querySubObject("Cells(QVariant&, QVariant&)", row, column);
    // выбираю её
    cell->dynamicCall("Select()");
    // устанавливаю свойство разрешения переноса
    cell->dynamicCall("WrapText", true);
    delete cell;
}

void ExcelUtils::generateDocumentation(QAxObject* p, const QString& name)
{
    QString localGenerateDocumentation = p->generateDocumentation();
    QFile file("../" + name + ".html");
    file.open(QIODevice::WriteOnly);
    file.write(localGenerateDocumentation.toStdString().c_str());
    file.close();

    //QAxObject *pageSetup = sheet->querySubObject("PageSetup");
    //sheet->setProperty("FitToPagesWide", 1);
    //sheet->setProperty("FitToPagesTall", 1);
    //for (auto x : pageSetup->propertyBag().keys()) qDebug() << x << pageSetup->propertyBag()[x];
}

void ExcelUtils::setFontBold(QAxObject* sheet, int row, int column, bool isBold)
{
    QAxObject *cell = sheet->querySubObject( "Cells( int, int )", row, column);
    QAxObject *font = cell->querySubObject("Font");
    font->setProperty("Bold", isBold);
    delete font;
    delete cell;
}


void ExcelUtils::setFitToPagesWide(QAxObject* sheet, int countPageDown)
{
    // http://aboutqt.blogspot.ru/2012_03_01_archive.html
    QAxObject *pageSetup = sheet->querySubObject("PageSetup");
    pageSetup->dynamicCall("Zoom", false); // Отключаем свойство Zoom
    pageSetup->dynamicCall("FitToPagesTall", countPageDown); // В 100 страницы по высоте
    pageSetup->dynamicCall("FitToPagesWide", 1); // В 1 страницу по ширине
    delete pageSetup;
}

void ExcelUtils::saveAsFile(QAxObject* workbook, QString dirPath, QString fileName)
{
    QString localFilePath = QDir::toNativeSeparators(QDir(dirPath).filePath(fileName));

    QList<QVariant> lstParam;
    lstParam.append(localFilePath);
    lstParam.append(-4143);
    lstParam.append("");
    lstParam.append("");
    lstParam.append(false);
    lstParam.append(false);
    lstParam.append(1);
    lstParam.append(2);
    lstParam.append(false);
    lstParam.append(false);
    lstParam.append(false);
    lstParam.append(false);

    workbook->dynamicCall("SaveAs(QVariant, QVariant, QVariant, QVariant, QVariant, QVariant, QVariant, QVariant, QVariant, QVariant, QVariant, QVariant)", lstParam);
}

void ExcelUtils::setCenterHorizontally(QAxObject* sheet, bool flag)
{
    QAxObject *pageSetup = sheet->querySubObject("PageSetup");
    pageSetup->dynamicCall("SetCenterHorizontally(bool)", flag);
    delete pageSetup;
}

void ExcelUtils::setTournamentName(QAxObject* sheet, QString text, int row0, int column0, int row1, int column1)
{
    ExcelUtils::setValue(sheet, row0, column0, text);
    ExcelUtils::setFontBold(sheet, row0, column0, true);
    ExcelUtils::uniteRange(sheet, row0, column0, row1, column1);
    ExcelUtils::setRowHeight(sheet, row0, 50);
}

QString ExcelUtils::getValue(QAxObject* sheet, int row, int column)
{
    QAxObject* cell = sheet->querySubObject("Cells( int, int )", row, column);
    QString value = cell->dynamicCall("Value()").toString().simplified();
    delete cell;
    if (value.isNull())
    {
        return "";
    }
    return value;
}

void ExcelUtils::setFooter(QAxObject* sheet, int row, int column0, int column1, int height, QVector<std::pair<int, QString> > what, QVector<QString> names){
    for (int i = 0; i < what.size(); ++i)
    {
        ExcelUtils::setRowHeight(sheet, row, height);
        ExcelUtils::setValue(sheet, row, column0, what[i].second, 0);
        ExcelUtils::setValue(sheet, row, column1, names[what[i].first], 0);
        ++row;
    }
}

QAxObject*ExcelUtils::addNewSheet(QAxObject* sheets)
{
    int intCount = sheets->property("Count").toInt();
    // Capture last sheet and add new sheet
    QAxObject* lastSheet = sheets->querySubObject("Item(int)", intCount);
    sheets->dynamicCall("Add(QVariant)", lastSheet->asVariant());
    delete lastSheet;
    // Capture the new sheet and move to after last sheet
    QAxObject* sheet = sheets->querySubObject("Item(int)", intCount);
    return sheet;
}

void ExcelUtils::normalizeColumnWidth(QAxObject* sheet, int column, int infWidth)
{
    QAxObject *pColumn = sheet->querySubObject("Columns(QVariant&)", column);
    if (qAbs(infWidth - pColumn->property("ColumnWidth").toDouble()) < 1e-7 ||
        pColumn->property("ColumnWidth").toDouble() < 8.43)
    {
        pColumn->setProperty("ColumnWidth", 8.43);
    }
    delete pColumn;
}

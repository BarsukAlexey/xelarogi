#ifndef EXCELUTILS_H
#define EXCELUTILS_H

#include <QAxObject>

// http://www.wiki.crossplatform.ru/index.php/%D0%A0%D0%B0%D0%B1%D0%BE%D1%82%D0%B0_%D1%81_MS_Office_%D1%81_%D0%BF%D0%BE%D0%BC%D0%BE%D1%89%D1%8C%D1%8E_ActiveQt

class ExcelUtils
{
public:
    static void uniteRange(QAxObject *, int, int, int, int);
    static void setValue(QAxObject* sheet, int row, int column, QString text, int hAligment = 1, int vAligment = 1);
    static void setBorder(QAxObject* sheet, int row0, int column0, int row1, int column1, int Weight = 2);
    static void setColumnAutoFit(QAxObject *sheet, int column);

    static void setRowAutoFit(QAxObject *sheet, int row);
    static void setRowHeight(QAxObject *sheet, int row, int height);

    static void setColumnWidth(QAxObject *sheet, int column, int height);

    static void setPageOrientation(QAxObject* sheet, int orientation);
    static void setWrapText(QAxObject* sheet, int row, int column);
    static void generateDocumentation(QAxObject* p);

    static void setFontBold(QAxObject* sheet, int row, int column, bool isBold);
    static void setFitToPagesWide(QAxObject* sheet, int cnt);
};

#endif // EXCELUTILS_H

#ifndef EXCELUTILS_H
#define EXCELUTILS_H

#include <QAxObject>

class ExcelUtils
{
public:
    static void uniteRange(QAxObject *, int, int, int, int);
    static void setValue(QAxObject* sheet, int row, int column, QString text, int hAligment = 1, int vAligment = 1);
    static void setBorder(QAxObject* sheet, int row0, int column0, int row1, int column1);
    static void setColumnAutoFit(QAxObject *sheet, int column);
    static void setPageOrientation(QAxObject* sheet, int orientation);
    static void generateDocumentation(QAxObject* p);
};

#endif // EXCELUTILS_H

#ifndef EXCELUTILS_H
#define EXCELUTILS_H

#include <QAxObject>

class ExcelUtils
{
public:
    static void uniteRange(QAxObject *, int, int, int, int);
    static void setValue(QAxObject* sheet, int row, int column, QString text, int hAligment = 1, int vAligment = 1);
    static void setBorder(QAxObject *, int, int, int, int);
};

#endif // EXCELUTILS_H

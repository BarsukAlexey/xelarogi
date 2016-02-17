#ifndef EXCELUTILS_H
#define EXCELUTILS_H

#include <QAxObject>

class ExcelUtils
{
public:
    static void uniteRange(QAxObject *, int, int, int, int);
    static void setValue(QAxObject *, int, int, QString);

};

#endif // EXCELUTILS_H

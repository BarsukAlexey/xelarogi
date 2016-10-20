#ifndef EXCELUTILS_H
#define EXCELUTILS_H

#include <QAxObject>
#include <QString>
#include <QVector>

// http://www.wiki.crossplatform.ru/index.php/%D0%A0%D0%B0%D0%B1%D0%BE%D1%82%D0%B0_%D1%81_MS_Office_%D1%81_%D0%BF%D0%BE%D0%BC%D0%BE%D1%89%D1%8C%D1%8E_ActiveQt
// http://www.forum.crossplatform.ru/lofiversion/index.php/t2450.html
class ExcelUtils
{

public:

    enum Border
    {
        all, xlEdgeTop, xlEdgeLeft, xlEdgeRight, xlEdgeBottom, xlDiagonalDown, xlDiagonalUp
    };

private:
    static QString bordertoString(Border v)
    {
        switch (v)
        {
            case xlEdgeTop      : return "xlEdgeTop";
            case xlEdgeLeft     : return "xlEdgeLeft";
            case xlEdgeRight    : return "xlEdgeRight";
            case xlEdgeBottom   : return "xlEdgeBottom";
            case xlDiagonalDown : return "xlDiagonalDown";
            case xlDiagonalUp   : return "xlDiagonalUp";
            default             : return "";
        }
    }

public:
    static void uniteRange(QAxObject* sheet, int row0, int column0, int row1, int column1);
    static void setValue(QAxObject* sheet, int row, int column, QString text, int hAligment = 1, int vAligment = 1);
    static void setBorder(QAxObject* sheet, int row0, int column0, int row1, int column1, int Weight = 2, Border border = Border::all);
    static void setColumnAutoFit(QAxObject *sheet, int column);

    static void setRowAutoFit(QAxObject *sheet, int row);
    static void setRowHeight(QAxObject *sheet, int row, int height);

    static void setColumnWidth(QAxObject *sheet, int column, int width);

    static void setPageOrientation(QAxObject* sheet, int orientation);
    static void setWrapText(QAxObject* sheet, int row, int column);
    static void generateDocumentation(QAxObject* p, const QString& name);

    static void setFontBold(QAxObject* sheet, int row, int column, bool isBold);
    static void setFitToPagesWide(QAxObject* sheet, int countPageDown = 100);

    static void saveAsFile(QAxObject* workbook, QString path, QString fileName);
    static void setCenterHorizontally(QAxObject* workbook, bool flag);

    static void setTournamentName(QAxObject* sheet, QString text, int row0, int column0, int row1, int column1);

    static QString getValue(QAxObject* sheet, int row, int column);

    static void setFooter(QAxObject* sheet, int row, int column0, int column1, int height, QVector<std::pair<int, QString>> what, QVector<QString> namsses);

    static QAxObject* addNewSheet(QAxObject* sheets);
};

#endif // EXCELUTILS_H

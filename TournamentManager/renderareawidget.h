#ifndef RENDERAREAWIDGET_H
#define RENDERAREAWIDGET_H

#include "db_utils.h"
#include "dialogchosedata.h"
#include "excel_utils.h"
#include "utils.h"
#include "renderarearesultdialog.h"

#include <QAxBase>
#include <QAxObject>
#include <QAxWidget>
#include <QDebug>
#include <QFileDialog>
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QRect>
#include <QSet>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtAlgorithms>
#include <QTime>
#include <QVector>
#include <QWidget>

class RenderAreaWidget : public QWidget
{
    Q_OBJECT


private:
    long long tournamentCategories;
    int fontSize;
    int countRows, countColumns;
    int widthCell, heightCell;
    const DBUtils::NodeOfTournirGrid noNode = DBUtils::NodeOfTournirGrid();
    DBUtils::NodeOfTournirGrid selectedNode = noNode;

    QVector<DBUtils::NodeOfTournirGrid> nodes;
    //QVector<std::pair<DBUtils::TypeField, QString>> locationData;
    QMap<int, QString> locationPlayer;

public:
    explicit RenderAreaWidget(QWidget *parent = 0, int widthCell = 300, int heightCell = 30);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

private:
    void paintNodeOfGrid(int i, int j, QPainter& painter, const DBUtils::NodeOfTournirGrid& node);
    void paintLine(const QPoint& , const QPoint& , QPainter& painter);
    void setNormalSize();
    QPoint getCell(int v);

signals:
    void iChangeToutGrid();

public slots:
    void tournamentCategoryIsChanged(int tournamentCategory);
    void widthChanged(int);
    void heightChanged(int);
    void onLocationDataIsChanged(const QVector<std::pair<DBUtils::TypeField, QString>>& locationData);
    void onFontSizeChanged(const int fontSize);
    void onSaveInExcel();
    void clearSelection();


private:
    static QPoint getCell(int v, int countColumns);

public:
    static int log2(int x);
    static void printTableGridInExcel(QAxObject* workbook, DialogChoseData& dlg, int tournamentCategory, bool likePointFighing, QString path, QVector<int> fightNumber, QString text = "", QString prefFileName = "");
    static QString getNameOfLevel(int vertex);
};
#endif // RENDERAREAWIDGET_H

#ifndef RENDERAREAWIDGET_H
#define RENDERAREAWIDGET_H

#include "db_utils.h"
#include "dialogchosedata.h"
#include "excel_utils.h"
#include "renderarearesultdialog.h"

#include <QAxWidget>
#include <QPainter>
#include <QPoint>
#include <QRect>
#include <QSet>
#include <QVector>
#include <QSqlDatabase>
#include <QWidget>

class RenderAreaWidget : public QWidget
{
    Q_OBJECT

public:


private:
    long long tournamentCategories;
    int countRows, countColumns;
    int widthCell, heightCell;
    const DBUtils::NodeOfTournirGrid noNode = DBUtils::NodeOfTournirGrid();
    DBUtils::NodeOfTournirGrid selectedNode = noNode;

public:
    explicit RenderAreaWidget(QWidget *parent, int widthCell, int heightCell);
    static void getAppropriateFontSize(QPainter& painter, const QRect& rect, const QString& text, int flags);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

private:
    void paintRect(int i, int j, QPainter& painter, const DBUtils::NodeOfTournirGrid& node);
    void paintLine(QPoint , QPoint , QPainter& painter);
    void setNormalSize();
    //QVector<NodeOfTournirGrid> getNodes();

    QPoint getCell(int v);

    long long getTournamentUID() const;
    QString getCategoryName() const;

signals:
    void iChangeToutGrid();

public slots:
    void slotSetTournamentCategories(int tournamentCategories);
    void widthChanged(int);
    void heightChanged(int);
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

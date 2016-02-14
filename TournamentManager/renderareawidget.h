#ifndef RENDERAREAWIDGET_H
#define RENDERAREAWIDGET_H

#include <QWidget>

#include <QWidget>
#include <QVector>
#include <QRect>
#include <QPainter>
#include <QSet>
#include <QPoint>
#include <QSqlDatabase>

class RenderAreaWidget : public QWidget
{
    Q_OBJECT

public:
    struct NodeOfTournirGrid
    {
        int v; // id вершины; вершины нумируются как в дереве отрезков
        QString name; //
        NodeOfTournirGrid()
        {
            v = -1;
            name = "error";
        }
        NodeOfTournirGrid(int v, QString name)
        {
            this->v = v;
            this->name = name;
        }
        bool operator < (const NodeOfTournirGrid& other) const
        {
            return v < other.v;
        }
    };

private:
    const QSqlDatabase & database;
    long long tournamentUID;
    long long tournamentCategories;
    int cntNodes = 1; // TEMP FOR DEBUG
    int countRows, countColumns;
    int widthCell, heightCell;
    QVector<QPoint> setOfSelectedCells;

public:
    explicit RenderAreaWidget(QWidget *parent, int widthCell, int heightCell, const QSqlDatabase &_database, long long _tournamentUID);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

private:
    void paintRect(int i, int j, QPainter& painter, const NodeOfTournirGrid& node);
    void paintLine(QPoint , QPoint , QPainter& painter);
    void setNormalSize();
    QVector<NodeOfTournirGrid> getNodes();
    void getNodes_ForDebuging(int v, QVector<RenderAreaWidget::NodeOfTournirGrid>& arr);
    int log2(int x);
    QPoint getCell(int v);

signals:

public slots:
    void slotSetTournamentCategories(int tournamentCategories);
    void widthChanged(int);
    void heightChanged(int);
};

#endif // RENDERAREAWIDGET_H

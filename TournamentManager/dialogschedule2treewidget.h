#ifndef DIALOGSCHEDULE2TREEWIDGET_H
#define DIALOGSCHEDULE2TREEWIDGET_H

#include <QDebug>
#include <QTreeWidget>
#include <QWidget>
#include <QMimeData>
#include <QDrag>

class Dialogschedule2TreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit Dialogschedule2TreeWidget(QWidget *parent = 0);
    static QString getMimiType(){ return "application/x-qwerty"; }

private:
    int tournamentUID;
    QStringList list;

protected:
    void startDrag(Qt::DropActions supportedActions) Q_DECL_OVERRIDE;

signals:
    //dataIsDroped(QStringList list);

public slots:
    void setTournamentUID(const int tournamentUID);
    void updateDataInTable();
};

#endif // DIALOGSCHEDULE2TREEWIDGET_H

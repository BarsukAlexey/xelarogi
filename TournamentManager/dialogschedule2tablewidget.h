#ifndef DIALOGSCHEDULE2TABLEWIDGET_H
#define DIALOGSCHEDULE2TABLEWIDGET_H

#include <QDebug>
#include <QObject>
#include <QTableWidget>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QMimeData>

class Dialogschedule2TableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit Dialogschedule2TableWidget(QWidget *parent = 0);


protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;

signals:
    ohDrop(QStringList strs, int row, int column);

public slots:

};

#endif // DIALOGSCHEDULE2TABLEWIDGET_H

#ifndef DIALOGSCHEDULE2_H
#define DIALOGSCHEDULE2_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSettings>
#include <QMenu>
#include <QAction>
#include <QFileDialog>


#include "db_utils.h"
#include "fighting_pairs.h"
#include "utils.h"
#include "dialogschedule2inputtype.h"
#include "dialogchosedata.h"
#include "excel_utils.h"
#include "renderareawidget.h"
#include "errormessagesdialog.h"

namespace Ui {
class Dialogschedule2;
}

class Dialogschedule2 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogschedule2(int tournamentUID, QWidget *parent = 0);
    ~Dialogschedule2();

private:
    Ui::Dialogschedule2 *ui;
    const int tournamentUID;
    static const int durationOfRow = 5 * 60;

private:
    static QVector<std::tuple<int, QString, QColor>> getInfoForRing(
            const int tournamentUID, const int day, const int ring, const int delay);

private slots:
    void onCountOfRingsChanged();
    void onDateChanged();
    void onDataIsDropped(QStringList str, const int row, const int ring);
    void onCustomContextMenuRequested(const QPoint& pos);


    void updateRowsInTable();
    void updateTree();

    void onPushButtonListOfPairs();
    void onPushButtonSaveSchelderClicked();

    void onPushButtonUP();
    void onPushButtonDown();
};

#endif // DIALOGSCHEDULE2_H

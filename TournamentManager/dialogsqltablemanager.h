#ifndef DIALOGSQLTABLEMANAGER_H
#define DIALOGSQLTABLEMANAGER_H

#include <QDialog>
#include <QMap>

#include "sqltablemanager.h"
#include "db_utils.h"

namespace Ui {
class DialogSqlTableManager;
}

class DialogSqlTableManager : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSqlTableManager(QWidget *parent,
                                   const QString& table,
                                   const QString& whereStatement = "",
                                   QMap<QString, QVariant> columnValue = QMap<QString, QVariant>());
    ~DialogSqlTableManager();
    void setVisibleShit(const QString& text, const QString& newName);
    int getUID();

private:
    Ui::DialogSqlTableManager *ui;
    QModelIndex index;
    QString newName;
};

#endif // DIALOGSQLTABLEMANAGER_H

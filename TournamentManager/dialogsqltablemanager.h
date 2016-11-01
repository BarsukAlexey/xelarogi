#ifndef DIALOGSQLTABLEMANAGER_H
#define DIALOGSQLTABLEMANAGER_H

#include <QDialog>

namespace Ui {
class DialogSqlTableManager;
}

class DialogSqlTableManager : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSqlTableManager(QWidget *parent, const QString& table, const QString& whereStatement = "", const QStringList& hidenColumns = QStringList());
    ~DialogSqlTableManager();

private:
    Ui::DialogSqlTableManager *ui;
};

#endif // DIALOGSQLTABLEMANAGER_H

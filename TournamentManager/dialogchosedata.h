#ifndef DIALOGCHOSEDATA_H
#define DIALOGCHOSEDATA_H

#include "db_utils.h"
#include "dialogselectfieldsfordimloma.h"

#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QPlainTextEdit>


namespace Ui {
class DialogChoseData;
}

class DialogChoseData : public QDialog
{
    Q_OBJECT

private:
    Ui::DialogChoseData *ui;
    QVector<QVector<std::pair<DBUtils::TypeField, QString> > > fields;
    QVector<QPlainTextEdit*> headers;
    const QString dirPath;

public:
    explicit DialogChoseData(QString path, bool enableRows, QWidget *parent = 0);
    ~DialogChoseData();
    QString getTitle();
    QVector<std::pair<QString, QVector<std::pair<DBUtils::TypeField, QString> >>> getData();
    QVector<std::pair<int, QString>> getJudges();

private:
    void loadTemplate();

    void onSave();
    void onAddNew();
    void onDelete();

    void onAddRow();
    void onDeleteRow();
    void onTableClicked(const QModelIndex &);
};

#endif // DIALOGCHOSEDATA_H

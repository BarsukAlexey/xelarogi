#ifndef DIALOGCHOSEDATA_H
#define DIALOGCHOSEDATA_H

#include "db_utils.h"
#include "dialogselectfieldsfordimloma.h"

#include <QCloseEvent>
#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMapIterator>
#include <QMessageBox>
#include <QPlainTextEdit>



namespace Ui {
class DialogChoseData;
}

class DialogChoseData : public QDialog
{
    Q_OBJECT

public:
    enum Type {
        grids,
        fiting_distribution,
        weight_report,
        WinnerReport,
        makeGridsForPointFighting,
        fighting_pair,
        lol
    };

private:
    Ui::DialogChoseData *ui;
    QVector<QVector<std::pair<DBUtils::TypeField, QString> > > fields;
    QVector<QPlainTextEdit*> headers;
    DialogChoseData::Type type;
    QVector<std::pair<QLabel*, QPlainTextEdit*>> translation;

public:
    explicit DialogChoseData(DialogChoseData::Type type, QWidget *parent = 0);
    ~DialogChoseData();
    QString getTitle();
    QVector<std::pair<QString, QVector<std::pair<DBUtils::TypeField, QString> >>> getData();
    QVector<std::pair<int, QString>> getJudges();
    QMap<QString, QString> getTranslations();
    int getMaxPlace();

private:
    QString getDirPath();
    bool enableTitle();
    bool enableRows();
    bool enableMaxPlace();

    void loadTemplate();

    void onSave();
    void onAddNew();
    void onDelete();

    void onAddRow();
    void onDeleteRow();
    void onTableClicked(const QModelIndex &);



    void accept();

};

#endif // DIALOGCHOSEDATA_H

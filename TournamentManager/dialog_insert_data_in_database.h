#ifndef DIALOG_INSERT_DATA_IN_DATABASE
#define DIALOG_INSERT_DATA_IN_DATABASE

#include <QDialog>

namespace Ui {
class DialogInsertDataInDatabase;
}

class DialogInsertDataInDatabase : public QDialog
{
    Q_OBJECT

private:
    QStringList mList;

public:
    explicit DialogInsertDataInDatabase(QWidget *parent, QString str, QStringList list, QString message =  "");
    ~DialogInsertDataInDatabase();

private slots:
    void on_pushButtonAddNew_clicked();
    void on_pushButtonSelectOld_clicked();

public:
    QString getText();

private:
    QString result;
    Ui::DialogInsertDataInDatabase *ui;
};

#endif // DIALOG_INSERT_DATA_IN_DATABASE

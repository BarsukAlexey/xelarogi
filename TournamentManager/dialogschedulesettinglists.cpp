#include "dialogschedulesettinglists.h"
#include "ui_dialogschedulesettinglists.h"

DialogScheduleSettingLists::DialogScheduleSettingLists(QWidget *parent, const long long tournamentUID) :
    QDialog(parent),
    tournamentUID(tournamentUID),
    ui(new Ui::DialogScheduleSettingLists)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);

    modelList = new QSqlRelationalTableModel(this);
    modelList->setTable("RING_TATAMI_LISTS");
    modelList->setFilter("TOURNAMENT_FK = " + QString::number(tournamentUID));
    modelList->setHeaderData(modelList->fieldIndex("NAME"), Qt::Horizontal, tr("Название списка"));
    modelList->select();

    ui->tableView->setModel(modelList);
    ui->tableView->setColumnHidden(modelList->fieldIndex("UID")          , true);
    ui->tableView->setColumnHidden(modelList->fieldIndex("TOURNAMENT_FK"), true);
    ui->tableView->resizeColumnsToContents();

    connect(ui->pushButtonAddList, &QPushButton::clicked, this, &DialogScheduleSettingLists::onPushButtonAddList);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DialogScheduleSettingLists::onbuttonBoxAccepted);


    QSqlQuery query;
query.prepare(
                "SELECT * "
                "FROM AGE_TYPES  "
                "WHERE TOURNAMENT_FK = ?"
                );
    query.addBindValue(tournamentUID);
    query.exec();
    while (query.next())
    {
        int TYPE_FK  = query.value("TYPE_FK").toInt();
        int AGE_FROM = query.value("AGE_FROM").toInt();
        int AGE_TILL = query.value("AGE_TILL").toInt();

        QComboBox *comboBox = new QComboBox();
        comboBox->setModel(modelList);
        comboBox->setModelColumn(modelList->fieldIndex("NAME"));
        {
            QSqlQuery query;
            if(!query.prepare(
                        "SELECT NAME, A.UID AS RTLS_UID "
                        "FROM RING_TATAMI_LISTS_DATA A"
                        "   LEFT JOIN RING_TATAMI_LISTS B ON A.RING_TATAMI_LIST_FK = B.UID "
                        "WHERE TOURNAMENT_FK = ? AND TYPE_FK = ? AND AGE_FROM = ? AND AGE_TILL = ? "
                        ))
            {
                qDebug() << query.lastError();
                qDebug() << query.lastQuery();
                return ;
            }
            query.addBindValue(tournamentUID);
            query.addBindValue(TYPE_FK);
            query.addBindValue(AGE_FROM);
            query.addBindValue(AGE_TILL);
            query.exec();
            if (query.next())
            {
                QString name = query.value("NAME").toString();
                int index = comboBox->findText(name);
                comboBox->setCurrentIndex(index);
                //qDebug() << index << query.value("NAME");


                long RTLS_UID = query.value("RTLS_UID").toLongLong();
                RING_TATAMI_LISTS_DATA_UID << RTLS_UID;
            }
            else
            {
                RING_TATAMI_LISTS_DATA_UID << -1;
            }
        }
        comboBoxLists << comboBox;



        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        const int row = ui->tableWidget->rowCount() - 1;
        QTableWidgetItem *it;
        it = new QTableWidgetItem(query.value("TYPE_NAME").toString());
        it->setData(Qt::UserRole, TYPE_FK);
        ui->tableWidget->setItem(row, 0,  it);
        ui->tableWidget->setItem(row, 1,  new QTableWidgetItem(QString::number(AGE_FROM)));
        ui->tableWidget->setItem(row, 2,  new QTableWidgetItem(QString::number(AGE_TILL)));
        ui->tableWidget->setCellWidget(row, 3,  comboBox);
    }
    ui->tableWidget->resizeColumnsToContents();

}

DialogScheduleSettingLists::~DialogScheduleSettingLists()
{
    delete ui;
}

void DialogScheduleSettingLists::onPushButtonAddList()
{
    bool ok;
    QString name = QInputDialog::getText(this,
                                         "",
                                         "Введите назание списка:",
                                         QLineEdit::Normal,
                                         "", &ok
                                         );
    if (!ok || name.isEmpty())
        return;

    QSqlRecord record = modelList->record();
    record.setValue("NAME", name);
    record.setValue("TOURNAMENT_FK", tournamentUID);
    //qDebug() << record;
    if (!modelList->insertRecord(-1, record)){
        qDebug() << "Fuck:insertRecord: " << modelList->lastError();
    }
    if (!modelList->submitAll()){
        qDebug() << "Fuck:submitAll:: " << modelList->lastError();
    }
    modelList->select();
}

void DialogScheduleSettingLists::onbuttonBoxAccepted()
{
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        QComboBox *comboBox = comboBoxLists[row];
        QModelIndex modelIndex = modelList->index(comboBox->currentIndex(), modelList->fieldIndex("UID"));
        long long RING_TATAMI_LIST_FK = modelList->data(modelIndex).toLongLong();
        //qDebug() << comboBox->currentData(Qt::DisplayRole) << RING_TATAMI_LIST_UID;


        long long TYPE_FK  = ui->tableWidget->item(row, 0)->data(Qt::UserRole).toLongLong();
        long long AGE_FROM = ui->tableWidget->item(row, 1)->data(Qt::DisplayRole).toLongLong();
        long long AGE_TILL = ui->tableWidget->item(row, 2)->data(Qt::DisplayRole).toLongLong();
        if (0 < RING_TATAMI_LISTS_DATA_UID[row])
        {
            QSqlQuery query;
            if (!query.prepare(
                        "UPDATE "
                        "RING_TATAMI_LISTS_DATA "
                        "SET  "
                        "   RING_TATAMI_LIST_FK = ?"
                        "WHERE UID = ?"
                        ))
            {
                qDebug() << query.lastError() << query.lastError();
                return;
            }
            query.addBindValue(RING_TATAMI_LIST_FK);
            query.addBindValue(RING_TATAMI_LISTS_DATA_UID[row]);
            if (!query.exec()){
                qDebug() << "No update";
            }
        }
        else
        {
            QSqlQuery query;
            if (!query.prepare(
                        "INSERT "
                        "INTO RING_TATAMI_LISTS_DATA "
                        "(RING_TATAMI_LIST_FK, TYPE_FK, AGE_FROM, AGE_TILL) "
                        "VALUES "
                        "(?, ?, ?, ?)"
                        ))
            {
                qDebug() << query.lastError() << query.lastError();
                return;
            }
            query.addBindValue(RING_TATAMI_LIST_FK);
            query.addBindValue(TYPE_FK);
            query.addBindValue(AGE_FROM);
            query.addBindValue(AGE_TILL);
            query.exec();
        }
    }
}

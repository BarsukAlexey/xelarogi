#include "dialogschedule2.h"
#include "ui_dialogschedule2.h"

Dialogschedule2::Dialogschedule2(int tournamentUID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogschedule2),
    tournamentUID(tournamentUID)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window);

    ui->labelContest->setText(DBUtils::getField("NAME", "TOURNAMENTS", tournamentUID));
    ui->comboBoxDay->addItems(DBUtils::get_DAYS_FROM_TOURNAMENTS(tournamentUID));

    for (const int tournamentCategoryUID : DBUtils::get_UIDs_of_TOURNAMENT_CATEGORIES(tournamentUID))
    {
        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", tournamentCategoryUID));


        QVector<QVector<DBUtils::NodeOfTournirGrid> > nodes = DBUtils::getNodesAsLevelListOfList(tournamentCategoryUID);
        for (int level = nodes.size() - 1; 0 <= level; --level)
        {
            int countOfNotPlayedFights = 0;
            int countOfFights = 0;
            for (const DBUtils::NodeOfTournirGrid& node : nodes[level])
            {
                if (node.isFight)
                {
                    if(node.UID <= 0)
                        ++countOfNotPlayedFights;
                    ++countOfFights;
                }
            }
            if (0 < countOfFights && 0 < countOfNotPlayedFights)
            {
                QTreeWidgetItem* child = new QTreeWidgetItem();

                child->setData(0, Qt::UserRole, QStringList()
                               << QString::number(tournamentCategoryUID)
                               << QString::number(level));
                QString str = "";
                if (level == 0) str = "Финал";
                else if (level == 1) str = "Полуфинал";
                else str = "1 / " + QString::number(1 << level);
                child->setText(0, str);
                item->addChild(child);

                //qDebug() << item->text(0) << str;
            }
        }


        if (item->childCount())
        {
            item->setData(0, Qt::UserRole, QStringList()
                           << QString::number(tournamentCategoryUID)
                           << "-1");
            ui->treeWidget->addTopLevelItem(item);
            item->setExpanded(true);
        }
    }


    onCountOfRingsChanged();

    connect(ui->spinBoxRing, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &Dialogschedule2::onCountOfRingsChanged);
}

Dialogschedule2::~Dialogschedule2()
{
    delete ui;
}

void Dialogschedule2::onCountOfRingsChanged()
{
    int countOfRing = ui->spinBoxRing->value();

//    QSqlQuery query;
//    if (!query.prepare("INSERT INTO TOURNAMENTS("
//                           "NAME, "
//                           "DATE_BEGIN, DATE_END, DATE_WEIGHTING, "
//                           "TEXT_DAT_RANGE, HOST, "
//                           "MAIN_JUDGE, MAIN_SECRETARY, ASSOCIATE_MAIN_JUDGE "
//                       ") "
//                       "VALUES(?,   ?,?,?,   ?,?,   ?,?,?)"))
//    {
//        qDebug() << query.lastError();
//        return;
//    }
//    query.addBindValue(ui->nameLE->text());

    if (countOfRing != ui->spinBoxRing->value())
    {
        ui->spinBoxRing->setValue(countOfRing);
        return;
    }

    ui->tableWidget->setColumnCount(countOfRing);

    ui->tableWidget->setRowCount(0);
    for (int time = 0, row = 0; time < 24 * 60; time += 5, ++row)
    {
        ui->tableWidget->setRowCount(row + 1);

        QString text = QString("%1").arg(time / 60, 2, 10, QChar('0')) +
                       ":" +
                       QString("%1").arg(time % 60, 2, 10, QChar('0'));
        QTableWidgetItem* item = new QTableWidgetItem(text);
        ui->tableWidget->setVerticalHeaderItem(row, item);
    }

    ui->tableWidget->resizeRowsToContents();
}

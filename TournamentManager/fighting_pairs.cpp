#include "fighting_pairs.h"
#include "db_utils.h"
#include "excel_utils.h"
#include "renderareawidget.h"

#include <QLabel>
#include <QGridLayout>
#include <QListWidget>
#include <QDebug>
#include <algorithm>
#include <QAxWidget>
#include <QAxObject>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonValuePtr>
#include <QJsonValueRef>
#include <QJsonValueRefPtr>
#include <QVariantMap>
#include <QFileDialog>

#include <QSqlQuery>
#include <QSqlError>

#include <algorithm>



FightingPairs::FightingPairs(const QSqlDatabase &_database, long long _tournamentUID, QWidget* parent) :
    QDialog(parent),
    database(_database),
    tournamentUID(_tournamentUID)
{
    qTableWidget = new QTableWidget();
    qTableWidget->setColumnCount(4);
    qTableWidget->setHorizontalHeaderLabels(QStringList({"Категория", "Кол-во пар", "Уровень", "Бои"}));

    globalListsOfPairs = DBUtils::getListsOfPairs(database, tournamentUID);
    for(const QVector<DBUtils::Fighing>& x : globalListsOfPairs)
    {
        QSqlQuery queryCOUNT("SELECT count() AS COUNT FROM ORDERS WHERE TOURNAMENT_CATEGORY_FK = ? GROUP BY TOURNAMENT_CATEGORY_FK", database);
        queryCOUNT.bindValue(0, x[0].TOURNAMENT_CATEGORIES_FK);
        if (!queryCOUNT.exec())
        {
            qDebug() << __LINE__ << __PRETTY_FUNCTION__ << queryCOUNT.lastError().text() << " " << queryCOUNT.lastQuery();
            continue;
        }
        int count = 0;
        if (queryCOUNT.next())
            count = queryCOUNT.value("COUNT").toInt();
        QVector<int> fights;
        for (int fight = 1; ; fight *= 2)
        {
            if (count < 2 * fight)
            {
                if (0 < count - fight) fights.push_back(count - fight);
                break;
            }
            else
                fights.push_back(fight);
        }
        std::reverse(fights.begin(), fights.end());
        QString fightingDistib;
        for (int x : fights)
            fightingDistib = fightingDistib + " " + QString::number(x);


        qTableWidget->setRowCount(qTableWidget->rowCount() + 1);
        QTableWidgetItem *item;

        item = new QTableWidgetItem(DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", x[0].TOURNAMENT_CATEGORIES_FK));
        item->setData(Qt::UserRole, x[0].TOURNAMENT_CATEGORIES_FK);
        qTableWidget->setItem(qTableWidget->rowCount() - 1, 0, item);

        qTableWidget->setItem(qTableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::number(x.size())));
        qTableWidget->setItem(qTableWidget->rowCount() - 1, 2, new QTableWidgetItem(RenderAreaWidget::getNameOfLevel(x[0].VERTEX)));
        qTableWidget->setItem(qTableWidget->rowCount() - 1, 3, new QTableWidgetItem(fightingDistib));
    }

    qTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qTableWidget->setSelectionMode(QAbstractItemView::SelectionMode::MultiSelection);
    qTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    qTableWidget->resizeColumnsToContents();





    ringSpinBox = new QSpinBox;
    ringSpinBox->setMaximum(100);
    ringSpinBox->setMinimum(1);
    ringSpinBox->setValue(1);


    qPushButton = new QPushButton("GO!");

    QGridLayout *qGridLayout = new QGridLayout;
    qGridLayout->addWidget(qTableWidget, 0, 0, 1, 2);

    qGridLayout->addWidget(new QLabel(QString("Кол-во рингов:")), 1, 0, Qt::AlignRight);
    qGridLayout->addWidget(ringSpinBox, 1, 1);

    qGridLayout->addWidget(new QLabel(QString("Дата + {утро, день, вечер}:")), 2, 0, Qt::AlignRight);
    qGridLayout->addWidget(qLineEdit = new QLineEdit(), 2, 1);

    qGridLayout->addWidget(checkBox = new QCheckBox("Сетка для поинтфайтинга:"), 3, 0, 1, 2, Qt::AlignCenter);

    qGridLayout->addWidget(qPushButton, 4, 0, 1, 2);

    setLayout(qGridLayout);

    resize(800, 600);
    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);


    connect(qPushButton, SIGNAL(clicked()), SLOT(onGoPress()));
}

FightingPairs::~FightingPairs()
{

}

void FightingPairs::printInExcel(QAxObject *sheet, const QVector<DBUtils::Fighing>& fighting, int ring)
{


    int currentRow = 2;


    ExcelUtils::setValue(sheet, currentRow, 1, "Состав пар");
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    ExcelUtils::setValue(sheet, currentRow, 1, qLineEdit->text());
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    ExcelUtils::setValue(sheet, currentRow, 1, "Ринг #" + QString::number(ring));
    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
    ++currentRow;

    for (int i = 0, pair = 1; i < fighting.size(); ++i, ++pair)
    {
        DBUtils::Fighing f = fighting[i];
        if (i == 0 || f.TOURNAMENT_CATEGORIES_FK != fighting[i - 1].TOURNAMENT_CATEGORIES_FK)
        {
            ++currentRow;

            ExcelUtils::setValue(sheet, currentRow, 1, RenderAreaWidget::getNameOfLevel(f.VERTEX));
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
            ExcelUtils::setFontBold(sheet, currentRow, 1, true);
            ++currentRow;

            ExcelUtils::setValue(sheet, currentRow, 1, DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK)
                                 // + " " + DBUtils::getField("AGE_FROM", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK) + "-" + DBUtils::getField("AGE_TILL", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK)
            );
            ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 3);
            ++currentRow;
        }

        ExcelUtils::setValue(sheet, currentRow, 1, QString::number(pair));
        ExcelUtils::setValue(sheet, currentRow, 2, DBUtils::getField("SECOND_NAME", "ORDERS", f.UID0) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.UID0) + " (" +
                             DBUtils::getField("NAME", "REGIONS", DBUtils::getField("REGION_FK", "ORDERS", f.UID0)) +
                             ")");
        ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::getField( "SECOND_NAME", "ORDERS", f.UID1) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.UID1) + " (" +
                             DBUtils::getField("NAME", "REGIONS", DBUtils::getField("REGION_FK", "ORDERS", f.UID1)) +
                             ")");
        ExcelUtils::setBorder(sheet, currentRow, 1, currentRow, 3);
        ++currentRow;
    }

    for (int column = 1; column <= 3; ++column)
        ExcelUtils::setColumnAutoFit(sheet, column);



    ExcelUtils::setTournamentName(sheet, DBUtils::getTournamentNameAsHeadOfDocument(database, tournamentUID), 1, 1, 1, 3);

    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2);
    ExcelUtils::setRowHeight(sheet, currentRow, 25);
    ExcelUtils::setValue(sheet, currentRow, 1, "Главный судья: ", 0);
    ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::get_MAIN_JUDGE(database, tournamentUID), 0);
    ++currentRow;

    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2);
    ExcelUtils::setRowHeight(sheet, currentRow, 25);
    ExcelUtils::setValue(sheet, currentRow, 1, "Главный секретарь: ", 0);
    ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::get_MAIN_SECRETARY(database, tournamentUID), 0);
    ++currentRow;

    ExcelUtils::uniteRange(sheet, currentRow, 1, currentRow, 2);
    ExcelUtils::setRowHeight(sheet, currentRow, 25);
    ExcelUtils::setValue(sheet, currentRow, 1, "Зам. главного судьи: ", 0);
    ExcelUtils::setValue(sheet, currentRow, 3, DBUtils::get_ASSOCIATE_MAIN_JUDGE(database, tournamentUID), 0);
    ++currentRow;
}

void FightingPairs::printInJSON(const QVector<DBUtils::Fighing>& fighting, int ring, const QString& existingDirectory)
{
    QJsonArray arr;
    int fightingId = 1;
    for (const DBUtils::Fighing& f : fighting)
    {
        QJsonObject a;
        a["nameOfLeftFighter" ] = DBUtils::getField("SECOND_NAME", "ORDERS", f.UID0) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.UID0);
        a["nameOfRightFighter"] = DBUtils::getField("SECOND_NAME", "ORDERS", f.UID1) + " " + DBUtils::getField("FIRST_NAME", "ORDERS", f.UID1);

        a["fightId"] = fightingId;
        a["categoryOfFighting"] = DBUtils::getField( "WEIGHT_TILL", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);

        a["countOfRounds"  ] = DBUtils::getField("ROUND_COUNT"     , "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);
        a["durationOfRound"] = DBUtils::getField("DURATION_FIGHING", "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);
        a["durationOfBreak"] = DBUtils::getField("DURATION_BREAK"  , "TOURNAMENT_CATEGORIES", f.TOURNAMENT_CATEGORIES_FK);

        a["countryOfLeftFighter" ] = DBUtils::getField("NAME", "REGIONS", DBUtils::getField("REGION_FK", "ORDERS", f.UID0));
        a["countryOfRightFighter"] = DBUtils::getField("NAME", "REGIONS", DBUtils::getField("REGION_FK", "ORDERS", f.UID1));

        a["TOURNAMENT_CATEGORIES_FK"] = f.TOURNAMENT_CATEGORIES_FK;
        a["VERTEX"] = f.VERTEX;
        a["orderUID_left"] = f.UID0;
        a["orderUID_right"] = f.UID1;

        arr.push_back(a);
        //
        ++fightingId;
    }

    const QString path = existingDirectory + QDir::separator() + "ring " + QString::number(ring) + ".json";
    QFile saveFile(path);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        qDebug() << saveFile.errorString();
        //qDebug() << path;
        return;
    }
    qDebug() << "writing: " << saveFile.write(QJsonDocument(arr).toJson()) << "БайТ";
    qDebug() << "writing in: " << path;
}




void FightingPairs::makeGridsForPointFighting(QString existingDirectory, QVector<QVector<DBUtils::Fighing> > listsOfPairs)
{
    QVector<int> durationOfGrid;
    for (const auto fighing : listsOfPairs){
        int time = 0;
        for (const DBUtils::NodeOfTournirGrid f : DBUtils::getNodes(fighing[0].TOURNAMENT_CATEGORIES_FK))
        {

            if (!f.isFighing) continue;
            time += DBUtils::get__DURATION_FIGHING(database, fighing[0].TOURNAMENT_CATEGORIES_FK) *
                    DBUtils::get__ROUND_COUNT(database, fighing[0].TOURNAMENT_CATEGORIES_FK) +

                    DBUtils::get__DURATION_BREAK(database, fighing[0].TOURNAMENT_CATEGORIES_FK) *
                    (DBUtils::get__ROUND_COUNT(database, fighing[0].TOURNAMENT_CATEGORIES_FK) - 1);
        }
        durationOfGrid.push_back(time);
    }
    for (int ringCount = ringSpinBox->value(), idRing = 1; 1 <= ringCount; --ringCount, ++idRing)
    {
        int time = std::accumulate(durationOfGrid.begin(), durationOfGrid.end(), 0) / ringCount;
        int curTime = 0;
        QVector<QVector<DBUtils::Fighing> > curGrids;
        while (curTime < time && listsOfPairs.size())
        {
            curTime += durationOfGrid.front();
            durationOfGrid.pop_front();

            curGrids.push_back(listsOfPairs.front());
            listsOfPairs.pop_front();
        }

        for (int i = 0, fightingNumber = 1; i < curGrids.size(); ++i)
        {
            RenderAreaWidget::printTableGridInExcel(database, curGrids[i].front().TOURNAMENT_CATEGORIES_FK, true,
                       existingDirectory, i == 0, i + 1 == curGrids.size(), fightingNumber, qLineEdit->text(),
                            "Татами " +  QString("%1 (%2)").arg(idRing, 2, 10, QChar('0')).arg(i + 1, 2, 10, QChar('0'))
                                                    );
            //fightingNumber += curGrids[i].size();
        }
    }

}

void FightingPairs::onGoPress()
{
    QString existingDirectory = QFileDialog::getExistingDirectory(this);

    QVector<QVector<DBUtils::Fighing> > listsOfPairs;
    for(QModelIndex index : qTableWidget->selectionModel()->selectedRows())
    {
        int row = index.row();
        //qDebug() << "row: " << row;
        listsOfPairs.push_back(globalListsOfPairs[row]);
    }

    std::random_shuffle(listsOfPairs.begin(), listsOfPairs.end());
    std::sort(listsOfPairs.begin(), listsOfPairs.end(),
        [this] (const QVector<DBUtils::Fighing>& lhs, const QVector<DBUtils::Fighing>& rhs) {
            for (QString field : {"AGE_FROM", "AGE_TILL", "WEIGHT_FROM", "WEIGHT_TILL"})
            {
                int a = DBUtils::getField(field, "TOURNAMENT_CATEGORIES", lhs[0].TOURNAMENT_CATEGORIES_FK).toDouble();
                int b = DBUtils::getField(field, "TOURNAMENT_CATEGORIES", rhs[0].TOURNAMENT_CATEGORIES_FK).toDouble();
                if (a != b)
                    return a < b;
            }
            return false;
    });

    if (checkBox->isChecked())
    {
        makeGridsForPointFighting(existingDirectory, listsOfPairs);
        return;
    }



    QVector<DBUtils::Fighing> fighing;
    for (QVector<DBUtils::Fighing>& a : listsOfPairs)
    {
        std::random_shuffle(a.begin(), a.end());
        std::sort(std::begin(a), std::end(a), [] (const DBUtils::Fighing& lhs, const DBUtils::Fighing& rhs) {
            return lhs.VERTEX > rhs.VERTEX;
        });
        fighing += a;
    }

    QAxWidget excel("Excel.Application");
    excel.setProperty("Visible", true);
    QAxObject *workbooks = excel.querySubObject("WorkBooks");
    workbooks->dynamicCall("Add");
    QAxObject *workbook = excel.querySubObject("ActiveWorkBook");
    QAxObject *sheets = workbook->querySubObject("WorkSheets");

    for (int ringCount = ringSpinBox->value(), idRing = 1; 1 <= ringCount; --ringCount, ++idRing)
    {
        int time = 0;
        for (const DBUtils::Fighing& f : fighing)
        {
            time += DBUtils::get__DURATION_FIGHING(database, f.TOURNAMENT_CATEGORIES_FK) *
                    DBUtils::get__ROUND_COUNT(database, f.TOURNAMENT_CATEGORIES_FK) +

                    DBUtils::get__DURATION_BREAK(database, f.TOURNAMENT_CATEGORIES_FK) *
                    (DBUtils::get__ROUND_COUNT(database, f.TOURNAMENT_CATEGORIES_FK) - 1);
        }
        time /= ringCount;

        int curTime = 0;
        QVector<DBUtils::Fighing> curFighing;
        while (fighing.size())
        {
            DBUtils::Fighing f = fighing.front();
            curTime += DBUtils::get__DURATION_FIGHING(database, f.TOURNAMENT_CATEGORIES_FK) *
                       DBUtils::get__ROUND_COUNT(database, f.TOURNAMENT_CATEGORIES_FK) +

                       DBUtils::get__DURATION_BREAK(database, f.TOURNAMENT_CATEGORIES_FK) *
                       (DBUtils::get__ROUND_COUNT(database, f.TOURNAMENT_CATEGORIES_FK) - 1);
            curFighing += f;
            fighing.pop_front();
            if (time <= curTime && 2 <= ringCount)
                break;
        }

        sheets->querySubObject("Add");
        QAxObject *sheet = sheets->querySubObject( "Item( int )", 1);
        sheet->setProperty("Name", "Ринг " + QString::number(idRing));
        printInExcel(sheet, curFighing, idRing);
        printInJSON(curFighing, idRing, existingDirectory);

        ExcelUtils::setPageOrientation(sheet, 1);
        ExcelUtils::setFitToPagesWide(sheet);
        ExcelUtils::setCenterHorizontally(sheet, true);
        delete sheet;
    }

    delete sheets;
    delete workbook;
    delete workbooks;
}


#include "createtournamentordersdialog.h"
#include "ui_createtournamentordersdialog.h"

QSqlRecord CreateTournamentOrdersDialog::m_record;

CreateTournamentOrdersDialog::CreateTournamentOrdersDialog(const QSqlDatabase &database,
                                                           long long tournamentUID,
                                                           QWidget *parent
                                                           ):
    m_database(database),
    mTournamentUID(tournamentUID),
    QDialog(parent),
    ui(new Ui::CreateTournamentOrdersDialog)
{
    ui->setupUi(this);
    ui->label->setText(getTournamentName());

    QMap<QString, QString> rusFieldNames = DataBaseExpert::fieldTranslationMap(m_database);
    auto ralTablesForFields = DataBaseExpert::ralationTablesForFields(m_database);
    m_record = m_database.record("ORDERS");

    QSqlRelationalTableModel * model = new QSqlRelationalTableModel();
    model->setTable("ORDERS");
    model->setFilter("TOURNAMENT_CATEGORY_FK IN " + getAllowTournamentCategories() + " AND IS_VALID = 1 ");
    ui->tableView->setModel(model);
    model->select();

    ui->tableView->setColumnHidden(model->fieldIndex("UID"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("COACH_FK"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("CLUB_FK"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("COUNTRY_FK"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("REGION_FK"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("BIRTHDATE"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("SEX_FK"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("SPORT_CATEGORY_FK"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("TOURNAMENT_CATEGORY_FK"), true);
    ui->tableView->setColumnHidden(model->fieldIndex("IS_VALID"), true);

    for (int i = 0; i < m_record.count(); ++i)
    {
        QString fieldName = m_record.fieldName(i);
        if (fieldName.size() > 3 && fieldName.right(3) == "_FK")
        {
            model->setRelation(i, QSqlRelation(ralTablesForFields[fieldName], "UID", "NAME"));
        }
    }

    for (int i = 0; i < m_record.count(); ++i)
    {
        model->setHeaderData(i, Qt::Horizontal, rusFieldNames[m_record.fieldName(i)]);
    }
    model->select();

    connect(ui->btnExit, &QPushButton::clicked, [this]()
    {
        this->accept();
    });

    ui->tableView->resizeColumnsToContents();

    addContextMenu();

    connect(ui->loadBtn, &QPushButton::clicked, this, &CreateTournamentOrdersDialog::loadFromExcel);


    updateFillOrderWidget();
    setComboBoxDependencies();

    connect(ui->tableView, &QTableView::clicked, [this] (const QModelIndex& index)
    {
        if (index != QModelIndex())
        {
            ui->changeOrderBtn->setEnabled(true);

            QModelIndex ind = index.model()->index(index.row(), 0);
            long long uid = ind.data().toLongLong();
            updateFillOrderWidget(uid);
        }
    });

    addSearchFilters();

    connect(ui->addOrderBtn, &QPushButton::clicked, [this, model] ()
    {
        QString firstName = ui->firstNameLE->text();
        QString secondName = ui->secondNameLE->text();
        QString patronymic = ui->patronymicLE->text();
        QDate birthdate = ui->birthdayDE->date();
        double weight = ui->weightDSB->value();

        long long sexUID = ui->gendersCB->currentData(Qt::UserRole).toLongLong();
        long long sportCategoryUID = ui->sportCategoriesCB->currentData(Qt::UserRole).toLongLong();
        long long typeUID = ui->typesCB->currentData(Qt::UserRole).toLongLong();
        long long clubUID = ui->clubsCB->currentData(Qt::UserRole).toLongLong();
        long long coachUID = ui->coachsCB->currentData(Qt::UserRole).toLongLong();
        long long countryUID = ui->countriesCB->currentData(Qt::UserRole).toLongLong();
        long long regionUID = ui->regionsCB->currentData(Qt::UserRole).toLongLong();
        long long regionUnitUID = ui->regionUnitsCB->currentData(Qt::UserRole).toLongLong();
        long long tournamentCategoryUID = ui->tournamentCategoriesCB->currentData(Qt::UserRole).toLongLong();

        QString error = "";
        if (sexUID < 0 || ui->gendersCB->currentData(Qt::DisplayRole).toString().isEmpty())                     error += "пол, ";
        if (sportCategoryUID < 0 || ui->sportCategoriesCB->currentData(Qt::DisplayRole).toString().isEmpty())   error += "разряд, ";
        if (typeUID < 0 || ui->typesCB->currentData(Qt::DisplayRole).toString().isEmpty())                      error += "раздел, ";
        if (clubUID < 0 || ui->clubsCB->currentData(Qt::DisplayRole).toString().isEmpty())                      error += "клуб, ";
        if (coachUID < 0 || ui->coachsCB->currentData(Qt::DisplayRole).toString().isEmpty())                    error += "тренер, ";
        if (countryUID < 0 || ui->countriesCB->currentData(Qt::DisplayRole).toString().isEmpty())               error += "страна, ";
        if (regionUID < 0 || ui->regionsCB->currentData(Qt::DisplayRole).toString().isEmpty())                  error += "регион, ";
        if (regionUnitUID < 0 || ui->regionUnitsCB->currentData(Qt::DisplayRole).toString().isEmpty())          error += "населенный пункт, ";
        if (tournamentCategoryUID < 0 || ui->tournamentCategoriesCB->currentData(Qt::DisplayRole).toString().isEmpty()) error += "категория турнира, ";

        if (error.isEmpty())
        {
            QSqlQuery insertQuery;
            if (!insertQuery.prepare(
                    "INSERT INTO ORDERS("
                    " FIRST_NAME, SECOND_NAME, PATRONYMIC,"
                    " BIRTHDATE, WEIGHT, SEX_FK,"
                    " COUNTRY_FK, REGION_FK, REGION_UNIT_FK,"
                    " TOURNAMENT_CATEGORY_FK, TYPE_FK, "
                    " CLUB_FK, COACH_FK,"
                    " SPORT_CATEGORY_FK, IS_VALID) "
                    "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, 1)"
                    ))
                qDebug() << insertQuery.lastError().text();

            insertQuery.bindValue(0, firstName);
            insertQuery.bindValue(1, secondName);
            insertQuery.bindValue(2, patronymic);
            insertQuery.bindValue(3, birthdate.toString("yyyy-MM-dd"));
            insertQuery.bindValue(4, weight);
            insertQuery.bindValue(5, sexUID);
            insertQuery.bindValue(6, countryUID);
            insertQuery.bindValue(7, regionUID);
            insertQuery.bindValue(8, regionUnitUID);
            insertQuery.bindValue(9, tournamentCategoryUID);
            insertQuery.bindValue(10, typeUID);
            insertQuery.bindValue(11, clubUID);
            insertQuery.bindValue(12, coachUID);
            insertQuery.bindValue(13, sportCategoryUID);

            if (!insertQuery.exec())
                qDebug() << insertQuery.lastError().text();

            model->select();
            qDebug() << "added";
        }
        else
        {
            QMessageBox::warning(this, "Заполнены не все поля", "Вы не указали: " + error + " - заполните эти поля");
        }
    });

    connect(ui->changeOrderBtn, &QPushButton::clicked, [this, model] ()
    {
        QModelIndex index = ui->tableView->selectionModel()->currentIndex();
        if (index != QModelIndex())
        {
            QModelIndex ind = index.model()->index(index.row(), 0);
            long long uid = ind.data().toLongLong();

            QString firstName = ui->firstNameLE->text();
            QString secondName = ui->secondNameLE->text();
            QString patronymic = ui->patronymicLE->text();
            QDate birthdate = ui->birthdayDE->date();
            double weight = ui->weightDSB->value();

            long long sexUID = ui->gendersCB->currentData(Qt::UserRole).toLongLong();
            long long sportCategoryUID = ui->sportCategoriesCB->currentData(Qt::UserRole).toLongLong();
            long long typeUID = ui->typesCB->currentData(Qt::UserRole).toLongLong();
            long long clubUID = ui->clubsCB->currentData(Qt::UserRole).toLongLong();
            long long coachUID = ui->coachsCB->currentData(Qt::UserRole).toLongLong();
            long long countryUID = ui->countriesCB->currentData(Qt::UserRole).toLongLong();
            long long regionUID = ui->regionsCB->currentData(Qt::UserRole).toLongLong();
            long long regionUnitUID = ui->regionUnitsCB->currentData(Qt::UserRole).toLongLong();
            long long tournamentCategoryUID = ui->tournamentCategoriesCB->currentData(Qt::UserRole).toLongLong();

            QString error = "";
            if (sexUID < 0 || ui->gendersCB->currentData(Qt::DisplayRole).toString().isEmpty())                     error += "пол, ";
            if (sportCategoryUID < 0 || ui->sportCategoriesCB->currentData(Qt::DisplayRole).toString().isEmpty())   error += "разряд, ";
            if (typeUID < 0 || ui->typesCB->currentData(Qt::DisplayRole).toString().isEmpty())                      error += "раздел, ";
            if (clubUID < 0 || ui->clubsCB->currentData(Qt::DisplayRole).toString().isEmpty())                      error += "клуб, ";
            if (coachUID < 0 || ui->coachsCB->currentData(Qt::DisplayRole).toString().isEmpty())                    error += "тренер, ";
            if (countryUID < 0 || ui->countriesCB->currentData(Qt::DisplayRole).toString().isEmpty())               error += "страна, ";
            if (regionUID < 0 || ui->regionsCB->currentData(Qt::DisplayRole).toString().isEmpty())                  error += "регион, ";
            if (regionUnitUID < 0 || ui->regionUnitsCB->currentData(Qt::DisplayRole).toString().isEmpty())          error += "населенный пункт, ";
            if (tournamentCategoryUID < 0 || ui->tournamentCategoriesCB->currentData(Qt::DisplayRole).toString().isEmpty()) error += "категория турнира, ";

            if (error.isEmpty())
            {
                QSqlQuery updateQuery;
                if (!updateQuery.prepare(
                        "UPDATE ORDERS "
                        " SET "
                        " FIRST_NAME = ?, SECOND_NAME = ?, PATRONYMIC = ?,"
                        " BIRTHDATE = ?, WEIGHT = ?, SEX_FK = ?,"
                        " COUNTRY_FK = ?, REGION_FK = ?, REGION_UNIT_FK = ?,"
                        " TOURNAMENT_CATEGORY_FK = ?, TYPE_FK = ?, "
                        " CLUB_FK = ?, COACH_FK = ?,"
                        " SPORT_CATEGORY_FK = ? "
                        " WHERE UID = ? "
                        ))
                    qDebug() << updateQuery.lastError().text();

                updateQuery.bindValue(0, firstName);
                updateQuery.bindValue(1, secondName);
                updateQuery.bindValue(2, patronymic);
                updateQuery.bindValue(3, birthdate.toString("yyyy-MM-dd"));
                updateQuery.bindValue(4, weight);
                updateQuery.bindValue(5, sexUID);
                updateQuery.bindValue(6, countryUID);
                updateQuery.bindValue(7, regionUID);
                updateQuery.bindValue(8, regionUnitUID);
                updateQuery.bindValue(9, tournamentCategoryUID);
                updateQuery.bindValue(10, typeUID);
                updateQuery.bindValue(11, clubUID);
                updateQuery.bindValue(12, coachUID);
                updateQuery.bindValue(13, sportCategoryUID);
                updateQuery.bindValue(14, uid);

                if (!updateQuery.exec())
                    qDebug() << updateQuery.lastError().text();

                model->select();
                ui->tableView->setCurrentIndex(ui->tableView->model()->index(index.row(), 0));
                qDebug() << "changed";
            }
            else
            {
                QMessageBox::warning(this, "Заполнены не все поля", "Вы не указали: " + error + " - заполните эти поля");
            }
        }
    });
}

CreateTournamentOrdersDialog::~CreateTournamentOrdersDialog()
{
    delete ui;
}

void CreateTournamentOrdersDialog::loadFromExcel()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выберите файл, в котором содержатся заявки"),
                                                    "./", tr("Excel (*.xlsx);;Excel 97 (*.xls)"));

    if (filePath.isEmpty()) return;


    QAxObject* excel = new QAxObject( "Excel.Application", 0 );
    QAxObject* workbooks = excel->querySubObject( "Workbooks" );
    QAxObject* workbook = workbooks->querySubObject( "Open(const QString&)", filePath );

    QAxObject* sheets = workbook->querySubObject( "Sheets" );
    int sheetCount = sheets->dynamicCall("Count()").toInt();

    int totalOrders = 0;
    int addOrders = 0;
    int duplicateOrders = 0;
    int noUIDsOrders = 0;
    int errorOrders = 0;

    QStringList errors;
    for (int sheetNumber = 1; sheetNumber <= sheetCount; ++sheetNumber)
    {
        QAxObject* sheet = sheets->querySubObject( "Item( int )", sheetNumber );

        QAxObject* usedrange = sheet->querySubObject( "UsedRange");
        QAxObject * rows = usedrange->querySubObject("Rows");
        int intRowStart = usedrange->property("Row").toInt();
        int intRows = rows->property("Count").toInt();

        QAxObject* c = sheet->querySubObject("Cells( int, int )", 7, 2);
        QString countryName = c->dynamicCall("Value()").toString();
        delete c;

        c = sheet->querySubObject("Cells( int, int )", 8, 2);
        QString regionName = c->dynamicCall("Value()").toString();
        delete c;

        long long countryUID = getCountryUID(countryName);
        long long regionUID = getRegionUID(regionName, countryUID);

        for (int row = 15 ; row < intRowStart + intRows ; ++row) {

            QAxObject* cell = sheet->querySubObject( "Cells( int, int )", row, 2 );
            QVariant value = cell->dynamicCall( "Value()" );
            QString firstName = value.toString();
            fillNullString(firstName);
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 1 );
            value = cell->dynamicCall( "Value()" );
            QString secondName = value.toString();
            fillNullString(secondName);
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 3 );
            value = cell->dynamicCall( "Value()" );
            QString patronymic = value.toString();
            fillNullString(patronymic);
            delete cell;

            if (secondName.trimmed().isEmpty()) break;

            cell = sheet->querySubObject( "Cells( int, int )", row, 4 );
            value = cell->dynamicCall( "Value()" );
            QString birthday = value.toString();
            QDate correctBirthDate = QDate::fromString(birthday, "yyyy-MM-dd'T00:00:00'");
            if (correctBirthDate.isValid())
                birthday = correctBirthDate.toString("dd.MM.yyyy");
            qDebug() << "I read from excel birthdate as " << birthday;
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 5 );
            value = cell->dynamicCall( "Value()" );
            QString weight = value.toString();
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 6 );
            value = cell->dynamicCall( "Value()" );
            QString gender = value.toString();
            fillNullString(gender);
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 7 );
            value = cell->dynamicCall( "Value()" );
            QString type = value.toString();
            fillNullString(type);
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 8 );
            value = cell->dynamicCall( "Value()" );
            QString regionUnitName = value.toString();
            fillNullString(regionUnitName);
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 9 );
            value = cell->dynamicCall( "Value()" );
            QString clubName = value.toString();
            fillNullString(clubName);
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 10 );
            value = cell->dynamicCall( "Value()" );
            QString sportKind = value.toString();
            fillNullString(sportKind);
            delete cell;

            cell = sheet->querySubObject( "Cells( int, int )", row, 11 );
            value = cell->dynamicCall( "Value()" );
            QString coachName = value.toString();
            fillNullString(coachName);
            delete cell;

            long long unitUID = getRegionUnitUID(regionUnitName, regionUID, countryUID);
            long long clubUID = getClubUID(clubName, countryUID, regionUID, unitUID);
            QStringList coachNameArgs = coachName.split(" ");
            coachName = "";
            for (const QString& arg: coachNameArgs)
            {
                if (arg.isEmpty()) continue;
                if (coachName.isEmpty() == false)
                {
                    coachName += " ";
                }
                coachName += arg;
            }
            long long coachUID = getCoachUID(coachName, clubUID);

            // TODO check if exist


            double age = QDate::currentDate().year() - QDate::fromString(birthday, "dd.MM.yyyy").year();
            if (QDate::currentDate().month() == QDate::fromString(birthday, "dd.MM.yyyy").month() &&
                QDate::currentDate().day() < QDate::fromString(birthday, "dd.MM.yyyy").day())
            {
                age -= 1.0;
            }
            else if (QDate::currentDate().month() < QDate::fromString(birthday, "dd.MM.yyyy").month())
            {
                age -= 1.0;
            }

            long long genderUID = getGenderUID(gender);
            long long typeUID = getTypeUID(type);
            long long sportCategoryUID = getSportCategoryUID(sportKind);

            totalOrders++;

            mGlobalError = "";
            long long tournamentCategoryUID = getTournamentCategoryUID(genderUID, age, weight.toDouble(), typeUID, gender, type);
            if (mGlobalError != "")
            {
                errors << mGlobalError + " (Спортсмен: " + secondName + " " + firstName + " " + patronymic + ")";
                noUIDsOrders++;
            }
            else
            {
                QSqlQuery findQuery;
                if (!findQuery.prepare("SELECT * FROM ORDERS "
                                     "WHERE "
                                     " FIRST_NAME = ? AND SECOND_NAME = ? AND PATRONYMIC = ? AND "
                                     " COUNTRY_FK = ? AND REGION_FK = ? AND REGION_UNIT_FK = ? AND "
                                     " BIRTHDATE = ? AND WEIGHT = ? AND SEX_FK = ? AND "
                                     " TOURNAMENT_CATEGORY_FK = ? AND TYPE_FK = ? AND "
                                     " CLUB_FK = ? AND COACH_FK = ? AND "
                                     " SPORT_CATEGORY_FK = ? AND "
                                     " IS_VALID = 1"
                                ))
                    qDebug() << findQuery.lastError().text();
                findQuery.bindValue(0, firstName);
                findQuery.bindValue(1, secondName);
                findQuery.bindValue(2, patronymic);
                findQuery.bindValue(3, countryUID);
                findQuery.bindValue(4, regionUID);
                findQuery.bindValue(5, unitUID);
                findQuery.bindValue(6, QDate::fromString(birthday, "dd.MM.yyyy").toString("yyyy-MM-dd"));
                findQuery.bindValue(7, weight.toDouble());
                findQuery.bindValue(8, genderUID);
                findQuery.bindValue(9, tournamentCategoryUID);
                findQuery.bindValue(10, typeUID);
                findQuery.bindValue(11, clubUID);
                findQuery.bindValue(12, coachUID);
                findQuery.bindValue(13, sportCategoryUID);

                if (findQuery.exec() && findQuery.next())
                {
                    duplicateOrders++;
                }
                else
                {
                    QSqlQuery query;
                    if (!query.prepare(  "INSERT INTO ORDERS("
                                         "FIRST_NAME, SECOND_NAME, PATRONYMIC, "
                                         "COUNTRY_FK, REGION_FK, REGION_UNIT_FK, "
                                         "BIRTHDATE, WEIGHT, SEX_FK, "
                                         "TOURNAMENT_CATEGORY_FK, TYPE_FK, "
                                         "CLUB_FK, COACH_FK, "
                                         "SPORT_CATEGORY_FK, "
                                         "IS_VALID) "
                                    "VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, 1)"
                                    ))
                        qDebug() << query.lastError().text();
                    query.bindValue(0, firstName);
                    query.bindValue(1, secondName);
                    query.bindValue(2, patronymic);
                    query.bindValue(3, countryUID);
                    query.bindValue(4, regionUID);
                    query.bindValue(5, unitUID);
                    query.bindValue(6, QDate::fromString(birthday, "dd.MM.yyyy").toString("yyyy-MM-dd"));
                    query.bindValue(7, weight.toDouble());
                    query.bindValue(8, genderUID);
                    query.bindValue(9, tournamentCategoryUID);
                    query.bindValue(10, typeUID);
                    query.bindValue(11, clubUID);
                    query.bindValue(12, coachUID);
                    query.bindValue(13, sportCategoryUID);

                    if (query.exec())
                        addOrders++;
                    else
                    {
                        qDebug() << query.lastError().text();
                        errorOrders++;
                    }
                }
            }
        }
    }


    // clean up and close up
    workbook->dynamicCall("Close()");
    delete workbook;
    excel->dynamicCall("Quit()");
    delete excel;

    if (errors.size() > 0)
    {
        qDebug() << errors.size() << " errors";
        ErrorMessagesDialog dlg(errors, this);
        dlg.exec();
    }

    QMessageBox::information(this, "Добавление заявок выполнено", "Всего распознано заявок: " + QString::number(totalOrders) + "\n"
                                                                  "Добавлено заявок: " + QString::number(addOrders) + "\n"
                                                                  "Не добавлены (нет категории): " + QString::number(noUIDsOrders) + "\n"
                                                                  "Проигнорированы (уже содержатся в базе): " + QString::number(duplicateOrders) + "\n"
                                                                  "Произошла ошибка при добавлении заявок: " + QString::number(errorOrders));

    QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
    model->select();
}

void CreateTournamentOrdersDialog::updateFillOrderWidget(long long orderUID)
{
    long long sexUID = -1;
    long long countryUID = -1, regionUID = -1, regionUnitUID = -1;
    long long sportCategoryUID = -1;
    long long typeUID = -1;
    long long clubUID = -1, coachUID = -1;
    long long tournamentCategoryUID = -1;

    if (orderUID >= 0)
    {
        QSqlQuery query;
        if (!query.prepare("SELECT * FROM ORDERS WHERE UID = ?"))
            qDebug() << query.lastError().text();
        query.bindValue(0, orderUID);

        if (query.exec() && query.next())
        {
            QDate birthdate = QDate::fromString(query.value("BIRTHDATE").toString(), "yyyy-MM-dd");

            sexUID = query.value("SEX_FK").toLongLong();
            countryUID = query.value("COUNTRY_FK").toLongLong();
            regionUID = query.value("REGION_FK").toLongLong();
            regionUnitUID = query.value("REGION_UNIT_FK").toLongLong();
            sportCategoryUID = query.value("SPORT_CATEGORY_FK").toLongLong();
            typeUID = query.value("TYPE_FK").toLongLong();
            clubUID = query.value("CLUB_FK").toLongLong();
            coachUID = query.value("COACH_FK").toLongLong();
            tournamentCategoryUID = query.value("TOURNAMENT_CATEGORY_FK").toLongLong();


            ui->firstNameLE->setText(query.value("FIRST_NAME").toString());
            ui->secondNameLE->setText(query.value("SECOND_NAME").toString());
            ui->patronymicLE->setText(query.value("PATRONYMIC").toString());
            ui->birthdayDE->setDate(birthdate);
            ui->weightDSB->setValue(query.value("WEIGHT").toDouble());
        }
        else
        {
            qDebug() << query.lastError().text();
        }
    }

    updateSexComboBox(sexUID);
    updateCountryComboBox(countryUID);
    updateRegionComboBox(regionUID, countryUID);
    updateRegionUnitComboBox(regionUnitUID, regionUID);
    updateSportCategoryComboBox(sportCategoryUID);
    updateTypeComboBox(typeUID);
    updateClubComboBox(clubUID, regionUID);
    updateCoachComboBox(coachUID, clubUID);
    updateTournamentCategoriesComboBox(tournamentCategoryUID, sexUID, typeUID);
}

void CreateTournamentOrdersDialog::addContextMenu()
{
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tableView, &QTableView::customContextMenuRequested, [this] (const QPoint& pos)
    {
        QMenu * contextMenu = new QMenu();

        QAction* restrictAction = new QAction(tr("Отозвать заявку"), contextMenu);
        contextMenu->addAction(restrictAction);
        connect(restrictAction, &QAction::triggered, [this, &pos] ()
        {
            QModelIndex index = ui->tableView->indexAt(pos);

            if (index != QModelIndex())
            {
                QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());

                QModelIndex ind = index.model()->index(index.row(), 0);
                long long orderUID = ind.data().toLongLong();

                QSqlQuery updateQuery;
                if (!updateQuery.prepare("UPDATE ORDERS SET IS_VALID = 0 WHERE UID = ?"))
                    qDebug() << updateQuery.lastError().text();
                updateQuery.bindValue(0, orderUID);
                if (!updateQuery.exec())
                    qDebug() << updateQuery.lastError().text();

                model->select();
            }
        });

        QAction * delAction = new QAction(tr("Удалить"), contextMenu);
        contextMenu->addAction(delAction);
        connect(delAction, &QAction::triggered, [this, &pos] ()
        {
            QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());

            QModelIndex index = ui->tableView->indexAt(pos);
            model->removeRow(index.row());
            model->submitAll();
        });


        contextMenu->exec(ui->tableView->viewport()->mapToGlobal(pos));
    });
}

void CreateTournamentOrdersDialog::addSearchFilters()
{
    connect(ui->filterSecondNameLE, &QLineEdit::textChanged, [this] (const QString& secondNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.SECOND_NAME LIKE '%%1%' "
                                 "AND ORDERS.UID IN %2 "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 "
                                 "AND IS_VALID = 1 ")
                         .arg(secondNameMask, getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              ui->filterFirstNameLE->text(), getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterFirstNameLE, &QLineEdit::textChanged, [this] (const QString& firstNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.SECOND_NAME LIKE '%%1%' "
                                 "AND ORDERS.UID IN %2 "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 "
                                 "AND IS_VALID = 1 ")
                         .arg(ui->filterSecondNameLE->text(), getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              firstNameMask, getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterCoachLE, &QLineEdit::textChanged, [this] (const QString& coachNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.UID IN %1 "
                                 "AND ORDERS.SECOND_NAME LIKE '%%2%' "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 "
                                 "AND IS_VALID = 1 ")
                         .arg(getAllowOrderUIDsByCoach(coachNameMask), ui->filterSecondNameLE->text(),
                              ui->filterFirstNameLE->text(), getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterRegionLE, &QLineEdit::textChanged, [this] (const QString& regionNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.UID IN %1 "
                                 "AND ORDERS.SECOND_NAME LIKE '%%2%' "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 "
                                 "AND IS_VALID = 1 ")
                         .arg(getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              ui->filterSecondNameLE->text(), ui->filterFirstNameLE->text(),
                              getAllowOrderUIDsByRegion(regionNameMask),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterRegionUintLE, &QLineEdit::textChanged, [this] (const QString& regionUnitNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.UID IN %1 "
                                 "AND ORDERS.SECOND_NAME LIKE '%%2%' "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 "
                                 "AND IS_VALID = 1 ")
                         .arg(getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              ui->filterSecondNameLE->text(), ui->filterFirstNameLE->text(),
                              getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(regionUnitNameMask),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterCountryLE, &QLineEdit::textChanged, [this] (const QString& countryNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.UID IN %1 "
                                 "AND ORDERS.SECOND_NAME LIKE '%%2%' "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 "
                                 "AND IS_VALID = 1 ")
                         .arg(getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              ui->filterSecondNameLE->text(), ui->filterFirstNameLE->text(),
                              getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(countryNameMask),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterSexLE, &QLineEdit::textChanged, [this] (const QString& genderNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.UID IN %1 "
                                 "AND ORDERS.SECOND_NAME LIKE '%%2%' "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 "
                                 "AND IS_VALID = 1 ")
                         .arg(getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              ui->filterSecondNameLE->text(), ui->filterFirstNameLE->text(),
                              getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(genderNameMask),
                              getAllowOrderUIDsbyTournamentCategory(ui->filterTournamentCategoriesLE->text())
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
    connect(ui->filterTournamentCategoriesLE, &QLineEdit::textChanged, [this] (const QString& tournamentCategoryNameMask)
    {
        QSqlRelationalTableModel* model = dynamic_cast<QSqlRelationalTableModel*>(ui->tableView->model());
        model->setFilter(QString("ORDERS.UID IN %1 "
                                 "AND ORDERS.SECOND_NAME LIKE '%%2%' "
                                 "AND ORDERS.FIRST_NAME LIKE '%%3%' "
                                 "AND ORDERS.UID IN %4 "
                                 "AND ORDERS.UID IN %5 "
                                 "AND ORDERS.UID IN %6 "
                                 "AND ORDERS.UID IN %7 "
                                 "AND ORDERS.UID IN %8 "
                                 "AND IS_VALID = 1 ")
                         .arg(getAllowOrderUIDsByCoach(ui->filterCoachLE->text()),
                              ui->filterSecondNameLE->text(), ui->filterFirstNameLE->text(),
                              getAllowOrderUIDsByRegion(ui->filterRegionLE->text()),
                              getAllowOrderUIDsByRegionUnit(ui->filterRegionUintLE->text()),
                              getAllowOrderUIDsByCountry(ui->filterCountryLE->text()),
                              getAllowOrderUIDsByGender(ui->filterSexLE->text()),
                              getAllowOrderUIDsbyTournamentCategory(tournamentCategoryNameMask)
                              )
                         );
        if (!model->select())
            qDebug() << model->lastError().text();
    });
}

void CreateTournamentOrdersDialog::setComboBoxDependencies()
{
    connect(ui->countriesCB, &QComboBox::currentTextChanged, [this] (const QString&)
    {
        long long coutryUID = ui->countriesCB->currentData(Qt::UserRole).toLongLong();
        updateRegionComboBox(-1, coutryUID);
    });
    connect(ui->regionsCB, &QComboBox::currentTextChanged, [this] (const QString&)
    {
        long long regionUID = ui->regionsCB->currentData(Qt::UserRole).toLongLong();
        updateRegionUnitComboBox(-1, regionUID);
        updateClubComboBox(-1, regionUID);
    });
    connect(ui->clubsCB, &QComboBox::currentTextChanged, [this] (const QString&)
    {
        long long clubUID = ui->clubsCB->currentData(Qt::UserRole).toLongLong();
        updateCoachComboBox(-1, clubUID);
    });
    connect(ui->gendersCB, &QComboBox::currentTextChanged, [this] (const QString&)
    {
        long long sexUID = ui->gendersCB->currentData(Qt::UserRole).toLongLong();
        long long typeUID = ui->typesCB->currentData(Qt::UserRole).toLongLong();
        updateTournamentCategoriesComboBox(-1, sexUID, typeUID);
    });
    connect(ui->typesCB, &QComboBox::currentTextChanged, [this] (const QString&)
    {
        long long sexUID = ui->gendersCB->currentData(Qt::UserRole).toLongLong();
        long long typeUID = ui->typesCB->currentData(Qt::UserRole).toLongLong();
        updateTournamentCategoriesComboBox(-1, sexUID, typeUID);
    });
}

QString CreateTournamentOrdersDialog::getAllowTournamentCategories()
{
    QString allowTournamentCategories = "(-100";
    QSqlQuery categoriesQouery("SELECT UID FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = " + QString::number(mTournamentUID));
    if (categoriesQouery.exec())
    {
        while (categoriesQouery.next())
        {
            allowTournamentCategories += ", " + categoriesQouery.value("UID").toString();
        }
    }
    allowTournamentCategories += ")";

    return allowTournamentCategories;
}

QString CreateTournamentOrdersDialog::getAllowOrderUIDsByCoach(const QString &coachNameMask)
{
    QString allowedOrders = "(-100";
    QSqlQuery query;
    if (!query.prepare("SELECT ORDERS.UID "
                       "FROM ORDERS "
                       "    LEFT JOIN COACHS ON COACHS.UID = ORDERS.COACH_FK "
                       "    LEFT JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                       "WHERE"
                       "    TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND "
                       "    COACHS.NAME LIKE '%" + coachNameMask + "%' "))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);

    if (query.exec())
    {
        while (query.next())
        {
            allowedOrders += ", " + query.value(0).toString();
        }
    }
    else
        qDebug() << query.lastError().text();

    allowedOrders += ")";

    return allowedOrders;
}

QString CreateTournamentOrdersDialog::getAllowOrderUIDsByCountry(const QString &countryNameMask)
{
    QString allowedOrders = "(-100";
    QSqlQuery query;
    if (!query.prepare("SELECT ORDERS.UID "
                       "FROM ORDERS "
                       "    LEFT JOIN COUNTRIES ON COUNTRIES.UID = ORDERS.COUNTRY_FK "
                       "    LEFT JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                       "WHERE"
                       "    TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND "
                       "    COUNTRIES.NAME LIKE '%" + countryNameMask + "%' "))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);

    if (query.exec())
    {
        while (query.next())
        {
            allowedOrders += ", " + query.value(0).toString();
        }
    }
    else
        qDebug() << query.lastError().text();

    allowedOrders += ")";

    return allowedOrders;
}

QString CreateTournamentOrdersDialog::getAllowOrderUIDsByRegion(const QString &regionNameMask)
{
    QString allowedOrders = "(-100";
    QSqlQuery query;
    if (!query.prepare("SELECT ORDERS.UID "
                       "FROM ORDERS "
                       "    LEFT JOIN REGIONS ON REGIONS.UID = ORDERS.REGION_FK "
                       "    LEFT JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                       "WHERE"
                       "    TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND "
                       "    REGIONS.NAME LIKE '%" + regionNameMask + "%' "))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);

    if (query.exec())
    {
        while (query.next())
        {
            allowedOrders += ", " + query.value(0).toString();
        }
    }
    else
        qDebug() << query.lastError().text();

    allowedOrders += ")";

    return allowedOrders;
}

QString CreateTournamentOrdersDialog::getAllowOrderUIDsByRegionUnit(const QString &regionUnitNameMask)
{
    QString allowedOrders = "(-100";
    QSqlQuery query;
    if (!query.prepare("SELECT ORDERS.UID "
                       "FROM ORDERS "
                       "    LEFT JOIN REGION_UNITS ON REGION_UNITS.UID = ORDERS.REGION_UNIT_FK "
                       "    LEFT JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                       "WHERE"
                       "    TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND "
                       "    REGION_UNITS.NAME LIKE '%" + regionUnitNameMask + "%' "))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);

    if (query.exec())
    {
        while (query.next())
        {
            allowedOrders += ", " + query.value(0).toString();
        }
    }
    else
        qDebug() << query.lastError().text();

    allowedOrders += ")";

    return allowedOrders;
}

QString CreateTournamentOrdersDialog::getAllowOrderUIDsByGender(const QString &genderMask)
{
    QString allowedOrders = "(-100";
    QSqlQuery query;
    if (!query.prepare("SELECT ORDERS.UID "
                       "FROM ORDERS "
                       "    LEFT JOIN SEXES ON SEXES.UID = ORDERS.SEX_FK "
                       "    LEFT JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                       "WHERE"
                       "    TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND "
                       "    SEXES.NAME LIKE '%" + genderMask + "%' "))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);

    if (query.exec())
    {
        while (query.next())
        {
            allowedOrders += ", " + query.value(0).toString();
        }
    }
    else
        qDebug() << query.lastError().text();

    allowedOrders += ")";

    return allowedOrders;
}

QString CreateTournamentOrdersDialog::getAllowOrderUIDsbyTournamentCategory(const QString &tournamentCategoryMask)
{
    QString allowedOrders = "(-100";
    QSqlQuery query;
    if (!query.prepare("SELECT ORDERS.UID "
                       "FROM ORDERS "
                       "    LEFT JOIN TOURNAMENT_CATEGORIES ON TOURNAMENT_CATEGORIES.UID = ORDERS.TOURNAMENT_CATEGORY_FK "
                       "WHERE"
                       "    TOURNAMENT_CATEGORIES.TOURNAMENT_FK = ? AND "
                       "    TOURNAMENT_CATEGORIES.NAME LIKE '%" + tournamentCategoryMask + "%' "))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);

    if (query.exec())
    {
        while (query.next())
        {
            allowedOrders += ", " + query.value(0).toString();
        }
    }
    else
        qDebug() << query.lastError().text();

    allowedOrders += ")";

    return allowedOrders;
}

QString CreateTournamentOrdersDialog::getTournamentName()
{
    QString tournamentName = "";
    QSqlQuery query("SELECT * FROM TOURNAMENTS WHERE UID = " + QString::number(mTournamentUID));
    if (query.exec() && query.next())
    {
        tournamentName = query.value("NAME").toString();
    }

    return tournamentName;
}

long long CreateTournamentOrdersDialog::getCountryUID(QString countryName)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM COUNTRIES"))
        qDebug() << query.lastError().text();
    if (query.exec())
    {
        while (query.next())
        {
            QString country = query.value("NAME").toString();
            if (country.trimmed().toUpper() == countryName.trimmed().toUpper())
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    query.clear();
    if (!query.prepare("INSERT INTO COUNTRIES(NAME) VALUES(?)"))
        qDebug() << query.lastError().text();
    query.bindValue(0, countryName);

    if (query.exec())
    {
        query.clear();
        return getCountryUID(countryName);
    }
    else
    {
        qDebug() << query.lastError().text();
        return -100;
    }
}

long long CreateTournamentOrdersDialog::getRegionUID(QString regionName, long long countryUID)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM REGIONS WHERE COUNTRY_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, countryUID);

    if (query.exec())
    {
        while (query.next())
        {
            QString region = query.value("NAME").toString();
            if (region.trimmed().toUpper() == regionName.trimmed().toUpper())
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    query.clear();
    if (!query.prepare("INSERT INTO REGIONS(NAME, COUNTRY_FK) VALUES(?, ?)"))
        qDebug() << query.lastError().text();
    query.bindValue(0, regionName);
    query.bindValue(1, countryUID);

    if (query.exec())
    {
        query.clear();
        return getRegionUID(regionName, countryUID);
    }
    else
    {
        qDebug() << query.lastError().text();
        return -100;
    }
}

long long CreateTournamentOrdersDialog::getRegionUnitUID(QString unitName, long long regionUID, long long countryUID)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM REGION_UNITS WHERE REGION_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, regionUID);

    if (query.exec())
    {
        while (query.next())
        {
            QString regionUnit = query.value("NAME").toString();
            if (regionUnit.trimmed().toUpper() == unitName.trimmed().toUpper())
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    query.clear();
    if (!query.prepare("INSERT INTO REGION_UNITS(NAME, REGION_FK, COUNTRY_FK) VALUES(?, ?, ?)"))
        qDebug() << query.lastError().text();
    query.bindValue(0, unitName);
    query.bindValue(1, regionUID);
    query.bindValue(2, countryUID);

    if (query.exec())
    {
        query.clear();
        return getRegionUnitUID(unitName, regionUID, countryUID);
    }
    else
    {
        qDebug() << query.lastError().text();
        return -100;
    }
}

long long CreateTournamentOrdersDialog::getGenderUID(QString genderName)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM SEXES"))
        qDebug() << query.lastError().text();
    if (query.exec())
    {
        while (query.next())
        {
            QString name = query.value("NAME").toString();
            if (name.trimmed().size() > 0 && genderName.trimmed().size() > 0)
            {
                if (name.trimmed().left(1).toUpper() == genderName.trimmed().left(1).toUpper())
                {
                    return query.value("UID").toLongLong();
                }
            }
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    query.clear();
    if (!query.prepare("INSERT INTO SEXES(NAME, SHORTNAME) VALUES(?, ?)"))
        qDebug() << query.lastError().text();
    query.bindValue(0, genderName);
    query.bindValue(1, genderName.left(1).toUpper());

    if (query.exec())
    {
        query.clear();
        return getGenderUID(genderName);
    }
    else
    {
        qDebug() << query.lastError().text();
        return -100;
    }
}

long long CreateTournamentOrdersDialog::getTournamentCategoryUID(long long sexUID, double age, double weight, long long typeUID, const QString &sexName, const QString &typeName)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM TOURNAMENT_CATEGORIES WHERE SEX_FK = ? AND TOURNAMENT_FK = ? AND TYPE_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, sexUID);
    query.bindValue(1, mTournamentUID);
    query.bindValue(2, typeUID);

    bool isFind = false;
    if (query.exec())
    {
        while (query.next())
        {
            double ageFrom = query.value("AGE_FROM").toDouble();
            double ageTill = query.value("AGE_TILL").toDouble();
            double weightFrom = query.value("WEIGHT_FROM").toDouble();
            double weightTill = query.value("WEIGHT_TILL").toDouble();

            double eps = 1e-8;
            if (age > ageFrom - eps && age < ageTill + eps)
            {
                if (weight > weightFrom + eps && weight < weightTill + eps)
                {
                    isFind = true;
                    return query.value("UID").toLongLong();
                }
            }
        }

        if (!isFind)
        {
            mGlobalError = "Не обнаружена необходимая категория турнира для:\n"
                           "   Вес: " + QString::number(weight) + "\n"
                           "   Возраст: " + QString::number(age) + "\n"
                           "   Раздел: " + typeName + "\n"
                           "   Пол: " + sexName + "\n"
                           "   Добавьте соответствующую категорию и повторите попытку ";
        }
    }
    else
    {
        qDebug() << query.lastError().text();
        return -100;
    }

    return -100;
}

long long CreateTournamentOrdersDialog::getSportCategoryUID(QString categoryName)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM SPORT_CATEGORIES"))
        qDebug() << query.lastError().text();

    if (query.exec())
    {
        while (query.next())
        {
            QString sportCategory = query.value("NAME").toString();
            if (sportCategory.trimmed().toUpper() == categoryName.trimmed().toUpper())
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    query.clear();
    if (!query.prepare("INSERT INTO SPORT_CATEGORIES(NAME) VALUES(?)"))
        qDebug() << query.lastError().text();
    query.bindValue(0, categoryName);

    if (query.exec())
    {
        query.clear();
        return getSportCategoryUID(categoryName);
    }
    else
    {
        qDebug() << query.lastError().text();
        return -100;
    }
}

long long CreateTournamentOrdersDialog::getTypeUID(QString typeName)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM TYPES"))
        qDebug() << query.lastError().text();
    if (query.exec())
    {
        while (query.next())
        {
            QString name = query.value("NAME").toString();
            if (name.trimmed().toUpper().contains(typeName.trimmed().toUpper()))
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    query.clear();
    if (!query.prepare("INSERT INTO TYPES(NAME) VALUES(?)"))
        qDebug() << query.lastError().text();
    query.bindValue(0, typeName);

    if (query.exec())
    {
        query.clear();
        return getTypeUID(typeName);
    }
    else
    {
        qDebug() << query.lastError().text();
        return -100;
    }
}

long long CreateTournamentOrdersDialog::getClubUID(QString clubName, long long coutryUID, long long regionUID, long long unitUID)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM CLUBS WHERE COUNTRY_FK = ? AND REGION_FK = ? AND REGION_UNIT_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, coutryUID);
    query.bindValue(1, regionUID);
    query.bindValue(2, unitUID);

    if (query.exec())
    {
        while (query.next())
        {
            QString club = query.value("NAME").toString();
            if (club.trimmed().toUpper() == clubName.trimmed().toUpper())
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    query.clear();
    if (!query.prepare("INSERT INTO CLUBS(NAME, COUNTRY_FK, REGION_FK, REGION_UNIT_FK) VALUES(?, ?, ?, ?)"))
        qDebug() << query.lastError().text();
    query.bindValue(0, clubName);
    query.bindValue(1, coutryUID);
    query.bindValue(2, regionUID);
    query.bindValue(3, unitUID);

    if (query.exec())
    {
        query.clear();
        return getClubUID(clubName, coutryUID, regionUID, unitUID);
    }
    else
    {
        qDebug() << query.lastError().text();
        return -100;
    }
}

long long CreateTournamentOrdersDialog::getCoachUID(QString coachName, long long clubUID)
{
    QSqlQuery query;
    if (!query.prepare("SELECT * FROM COACHS WHERE CLUB_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, clubUID);

    if (query.exec())
    {
        while (query.next())
        {
            QString coach = query.value("NAME").toString();
            if (coach.trimmed().toUpper() == coachName.trimmed().toUpper())
            {
                return query.value("UID").toLongLong();
            }
        }
    }
    else
    {
        qDebug() << query.lastError().text();
    }

    query.clear();
    if (!query.prepare("INSERT INTO COACHS(NAME, CLUB_FK) VALUES(?, ?)"))
        qDebug() << query.lastError().text();
    query.bindValue(0, coachName);
    query.bindValue(1, clubUID);

    if (query.exec())
    {
        query.clear();
        return getCoachUID(coachName, clubUID);
    }
    else
    {
        qDebug() << query.lastError().text();
        return -100;
    }
}

void CreateTournamentOrdersDialog::updateSexComboBox(long long currentUID)
{
    ui->gendersCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM SEXES"))
        qDebug() << query.lastError().text();

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->gendersCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->gendersCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == currentUID)
               ui->gendersCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateCountryComboBox(long long currentUID)
{
    ui->countriesCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM COUNTRIES"))
        qDebug() << query.lastError().text();

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->countriesCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->countriesCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == currentUID)
               ui->countriesCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateRegionComboBox(long long regionUID, long long countryUID)
{
    ui->regionsCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM REGIONS WHERE COUNTRY_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, countryUID);

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->regionsCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->regionsCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == regionUID)
               ui->regionsCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateRegionUnitComboBox(long long regionUnitUID, long long regionUID)
{
    ui->regionUnitsCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM REGION_UNITS WHERE REGION_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, regionUID);

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->regionUnitsCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->regionUnitsCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == regionUnitUID)
               ui->regionUnitsCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateSportCategoryComboBox(long long currentUID)
{
    ui->sportCategoriesCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM SPORT_CATEGORIES"))
        qDebug() << query.lastError().text();

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->sportCategoriesCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->sportCategoriesCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == currentUID)
               ui->sportCategoriesCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateTypeComboBox(long long currentUID)
{
    ui->typesCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM TYPES"))
        qDebug() << query.lastError().text();

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->typesCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->typesCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == currentUID)
               ui->typesCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateClubComboBox(long long clubUID, long long regionUID)
{
    ui->clubsCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM CLUBS WHERE REGION_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, regionUID);

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->clubsCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->clubsCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == clubUID)
               ui->clubsCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateCoachComboBox(long long coachUID, long long clubUID)
{
    ui->coachsCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM COACHS WHERE CLUB_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, clubUID);

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->coachsCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->coachsCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == coachUID)
               ui->coachsCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::updateTournamentCategoriesComboBox(long long currentUID, long long sexUID, long long typeUID)
{
    ui->tournamentCategoriesCB->clear();

    QSqlQuery query;
    if (!query.prepare("SELECT * FROM TOURNAMENT_CATEGORIES WHERE TOURNAMENT_FK = ? AND SEX_FK = ? AND TYPE_FK = ?"))
        qDebug() << query.lastError().text();
    query.bindValue(0, mTournamentUID);
    query.bindValue(1, sexUID);
    query.bindValue(2, typeUID);

    if (query.exec())
    {
       int index = 0;
       while (query.next())
       {
           ui->tournamentCategoriesCB->addItem(query.value("NAME").toString(), Qt::DisplayRole);
           ui->tournamentCategoriesCB->setItemData(index, query.value("UID"), Qt::UserRole);

           if (query.value("UID").toLongLong() == currentUID)
               ui->tournamentCategoriesCB->setCurrentIndex(index);

           ++index;
       }
    }
    else
    {
       qDebug() << query.lastError().text();
    }

    query.clear();
}

void CreateTournamentOrdersDialog::fillNullString(QString& s)
{
    if (s.isEmpty() || s.isNull())
        s = " ";
}

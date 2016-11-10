#include "formdipl.h"
#include "ui_formdipl.h"

FormDipl::FormDipl(long long UID_tournament, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDipl),
    UID_tournament(UID_tournament)
{
    ui->setupUi(this);

    for (int i = 0; i < 16; ++i)
       ui->comboBoxMaxPlace->addItem(QString::number(1 << i));

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setColumnWidth(0,175);
    ui->tableWidget->setColumnWidth(1,120);
    ui->tableWidget->setColumnWidth(2,175);


    connect(ui->pushButtonNew, &QPushButton::clicked, [this](){onNewTemplate();});
    connect(ui->pushButtonSave, &QPushButton::clicked, [this](){onSaveData();});

    connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(ui->pushButtonDelete, SIGNAL(clicked()), this, SLOT(deleteRow()));
    connect(ui->tableWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onTableClicked(const QModelIndex &)));
    connect(ui->pushButtonPrint, &QPushButton::clicked, this, &FormDipl::onPushPrint);
    connect(ui->radioButtonDiplom, &QRadioButton::clicked, [this](){
        ui->groupBoxPlace->setEnabled(true);
    });
    connect(ui->radioButtonBadge, &QRadioButton::clicked, [this](){
        ui->groupBoxPlace->setEnabled(false);
    });
    connect(ui->comboBox, &QComboBox::currentTextChanged, [this](){
        loadData();
    });


    QDir recoredDir(dirPath);
    for (QString file : recoredDir.entryList(QDir::Filter::Files))
    {
        ui->comboBox->addItem(file);
    }
}

FormDipl::~FormDipl()
{
    delete ui;
}

void FormDipl::onSaveData()
{
    QJsonObject obj;

    obj["width"] = ui->spinBoxWidth->value();
    obj["height"] = ui->spinBoxHeight->value();
    obj["badge"] = ui->radioButtonBadge->isChecked();
    obj["maxPlace"] = ui->comboBoxMaxPlace->currentText();
    obj["checkBoxAllGrids"] = ui->checkBoxAllGrids->isChecked();

    QJsonArray arr;
    for (int row = 0; row < fields.size(); ++row)
    {
        QJsonObject a;

        QJsonArray data;
        for (std::pair<DBUtils::TypeField, QString> pair : fields[row])
        {
            QJsonObject obj;
            obj["id"] = pair.first;
            obj["text"] = pair.second;
            data << obj;
        }
        a["data"] = data;
        a["font"] = fonts[row].toString();
        // DOTO CHECK HERE
        a["color"] = colors[row].name();

        int x        = dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 4))->value();
        int y        = dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 5))->value();
        int width    = dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 6))->value();
        int aligment = dynamic_cast<QComboBox*>(ui->tableWidget->cellWidget(row, 1))->currentIndex();
        a["x"] = x;
        a["y"] = y;
        a["width"] = width;
        a["aligment"] = aligment;

        arr.push_back(a);
    }
    obj["arr"] = arr;

    QFile saveFile(QDir(dirPath).filePath(ui->comboBox->currentText()));
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }
    qDebug() << "Записано " << saveFile.write(QJsonDocument(obj).toJson());
}

void FormDipl::loadData()
{
    fields.resize(0);
    fonts.resize(0);
    colors.resize(0);
    ui->tableWidget->setRowCount(0);


    QFile file(QDir(dirPath).filePath(ui->comboBox->currentText()));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument doc = QJsonDocument::fromJson(QString(file.readAll()).toUtf8());
    file.close();

    QJsonObject obj = doc.object();

    ui->spinBoxWidth->setValue(obj["width"].toInt());
    ui->spinBoxHeight->setValue(obj["height"].toInt());
    ui->radioButtonBadge ->setChecked( obj["badge"].toBool());
    ui->radioButtonDiplom->setChecked(!obj["badge"].toBool());
    ui->comboBoxMaxPlace->setCurrentText(obj["maxPlace"].toString());
    ui->checkBoxAllGrids->setChecked(obj["checkBoxAllGrids"].toBool());

    ui->groupBoxPlace->setEnabled(!obj["badge"].toBool());


    QJsonArray arr = obj["arr"].toArray();
    for (int i = 0; i < arr.size(); ++i)
        addRow();


    QVector<DBUtils::TypeField> allTypeFields = DBUtils::getAllTypeFieldl();

    for (int row = 0; row < arr.size(); ++row)
    {
        QJsonObject a = arr.at(row).toObject();

        for (QJsonValue val : a["data"].toArray())
        {
            QJsonObject obj = val.toObject();
            int typeField = obj["id"].toInt();

            for (DBUtils::TypeField field : allTypeFields)
            {
                if (typeField == field)
                {
                    fields[row] << std::make_pair(field, obj["text"].toString());
                    break;
                }
            }
        }
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(DBUtils::toString(fields[row])));

        dynamic_cast<QComboBox*>(ui->tableWidget->cellWidget(row, 1))->setCurrentIndex(a["aligment"].toInt());

        fonts[row].fromString(a["font"].toString());
        //qDebug() << "Load: " << fonts[row].pointSize();
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(fonts[row].toString()));

        colors[row] = QColor(a["color"].toString());
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackgroundColor(colors[row]);
        ui->tableWidget->setItem(row, 3, item);


        dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 4))->setValue(a["x"].toInt());
        dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 5))->setValue(a["y"].toInt());
        dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 6))->setValue(a["width"].toInt());

    }
}



void FormDipl::onTableClicked(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    if (index.column() == 0)
    {
        DialogSelectFieldsForDimloma dlg(this, fields[index.row()]);
        if (dlg.exec() == QDialog::Accepted)
        {

            fields[index.row()] = dlg.getFields();

            QString str;
            for (std::pair<DBUtils::TypeField, QString> pair : fields[index.row()])
            {
                if (!str.isEmpty())
                    str += "; ";
                str += DBUtils::getExplanationOfTypeField()[pair.first];
            }
            ui->tableWidget->setItem(index.row(), index.column(), new QTableWidgetItem(str));
        }
    }
    else if (index.column() == 2)
    {
        QFont font = QFontDialog::getFont(0, fonts[index.row()], this);
        fonts[index.row()] = font;
        ui->tableWidget->setItem(index.row(), index.column(), new QTableWidgetItem(fonts[index.row()].toString()));
    }
    else if (index.column() == 3)
    {
        QColor color = QColorDialog::getColor(colors[index.row()]);
//        qDebug() << color << colors[index.row()];
        if (color.isValid())
        {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setBackgroundColor(color);
            ui->tableWidget->setItem(index.row(), index.column(), item);
            colors[index.row()] = color;
        }
    }

    //ui->tableWidget->resizeColumnsToContents();
}

void FormDipl::addRow()
{
    int row = ui->tableWidget->rowCount();
    int column = 0;
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(row, column++, new QTableWidgetItem("Не выбрано (двойной клик)"));

    QComboBox* comboBox = new QComboBox(this);
    comboBox->addItem("По левому краю");
    comboBox->addItem("По центру");
    comboBox->addItem("По правому краю");
    ui->tableWidget->setCellWidget(row, column++, comboBox);

    ui->tableWidget->setItem(row, column++, new QTableWidgetItem("Не выбрано (двойной клик)"));

    QColor color(Qt::black);
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setBackgroundColor(color);
    ui->tableWidget->setItem(row, column++, item);


    for (int i = 0; i < 3; ++i)
    {
        QSpinBox *box = new QSpinBox(ui->tableWidget);
        box->setMinimum(1);
        box->setMaximum(100500);
        if (i == 2)
            box->setValue(150);
        else
            box->setValue(20);
        ui->tableWidget->setCellWidget(row, column++, box);
    }

//    ui->tableWidget->resizeColumnsToContents();

    fonts << QFont();
    fields << QVector<std::pair<DBUtils::TypeField, QString> >();
    colors << color;
}

void FormDipl::deleteRow()
{
    int row = ui->tableWidget->currentRow();
    if (0 <= row && row < ui->tableWidget->rowCount()){
        ui->tableWidget->removeRow(row);
        fonts.remove(row);
        fields.remove(row);
        colors.remove(row);
    }
}




void FormDipl::onPushPrint()
{
    onSaveData();

    QString dirPath = QFileDialog::getExistingDirectory(this);
    //QString dirPath = "C:\\Trash";
    if (dirPath.isEmpty()) return;

    QVector<long long> localGet_UIDs_of_TOURNAMENT_CATEGORIES = DBUtils::getTournamentCategoryUIDs(UID_tournament);

    //QProgressDialog progress("Working...", "Don't push", 0, localGet_UIDs_of_TOURNAMENT_CATEGORIES.size(), this);
    QProgressDialog progress(this);
    progress.setMaximum(localGet_UIDs_of_TOURNAMENT_CATEGORIES.size());
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(500);

    for (const long long uidTC : localGet_UIDs_of_TOURNAMENT_CATEGORIES)
    {
        //QVector<long long> UIDOrder = DBUtils::get_UIDOrder_for_TC(uidTC);
        //qDebug() << uidTC << UIDOrder.size();

        QVector<std::pair<long long, std::pair<int, int>>> UIDOrder =
                DBUtils::getUIDsAndPlaces(
                    uidTC,
                    ui->radioButtonBadge->isChecked()? (int)1e9 : ui->comboBoxMaxPlace->currentText().toInt(),
                    ui->radioButtonDiplom->isChecked() && !ui->checkBoxAllGrids->isChecked());
        if (UIDOrder.isEmpty())
            continue;
        //qDebug() << uidTC << UIDOrder.size();


        std::sort(UIDOrder.begin(), UIDOrder.end(), [](
                  const std::pair<long long, std::pair<int, int>>& UIDOrder0,
                  const std::pair<long long, std::pair<int, int>>& UIDOrder1)  -> bool {
            std::pair<int, int> place0 = UIDOrder0.second;
            std::pair<int, int> place1 = UIDOrder1.second;
            QString name0 = DBUtils::getSecondNameAndFirstName(UIDOrder0.first);
            QString name1 = DBUtils::getSecondNameAndFirstName(UIDOrder1.first);
            return  place0 <  place1 ||
                   (place0 == place1 && name0 < name1);
        });

        QString fileName = DBUtils::getField("NAME", "TOURNAMENT_CATEGORIES", uidTC, __PRETTY_FUNCTION__) + ".pdf";
        QString fullpath = QDir(dirPath).filePath(fileName);
        {
            QFile file(fullpath);
            if (file.exists())
                file.remove();
        }

        QPrinter printer;
        printer.setPageMargins(0, 0, 0, 0, QPrinter::Unit::Millimeter);
        printer.setPaperSize(QSizeF(ui->spinBoxWidth->value(), ui->spinBoxHeight->value()), QPrinter::Millimeter);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fullpath);

        QPainter painter;
        painter.begin(&printer);

        bool isThisFirstPage = true;
        for (int i = 0; i < UIDOrder.size(); ++i)
        {
            const long long uidOrder = UIDOrder[i].first;

            if (isThisFirstPage)
                isThisFirstPage = false;
            else
                printer.newPage();

            //сетка в 1 см
//            for (int index = 0; index < 20; ++index)
//            {
//                double y = 10.0 * printer.height() / printer.heightMM();
//                painter.drawLine(QPoint(0, index * y), QPoint(printer.width(), index * y));

//                double x = 10.0 * printer.width() / printer.widthMM();
//                painter.drawLine(QPoint(index * x, 0), QPoint(index * x, printer.height()));
//            }


            for (int row = 0; row < fonts.size(); ++row)
            {
                QString text = DBUtils::get(fields[row], uidOrder);

                QFont font = fonts[row];
                int x        = dynamic_cast<QSpinBox*>(ui->tableWidget->cellWidget(row, 4))->value() * printer.width()  / ui->spinBoxWidth ->value();
                int y        = dynamic_cast<QSpinBox*>(ui->tableWidget->cellWidget(row, 5))->value() * printer.height() / ui->spinBoxHeight->value();
                int width    = dynamic_cast<QSpinBox*>(ui->tableWidget->cellWidget(row, 6))->value() * printer.width()  / ui->spinBoxWidth ->value();

//                painter.drawLine(QPoint(x        , 0), QPoint(x        , printer.height()));
//                painter.drawLine(QPoint(x + width, 0), QPoint(x + width, printer.height()));


                if (1 < font.pointSize())
                {
                    qreal l = 1, r = font.pointSizeF();
                    for (int i = 0; i < 150; ++i)
                    {
                        qreal m = (l + r) / 2;
                        font.setPointSizeF(m);
                        if (width <= QFontMetrics(font).boundingRect(text).width())
                            r = m;
                        else
                            l = m;
                    }
                    font.setPointSizeF((l + r) / 2);
                }

                int index = dynamic_cast<QComboBox*>(ui->tableWidget->cellWidget(row, 1))->currentIndex();
                if      (index == 0);
                else if (index == 1) x += (width - QFontMetrics(font).boundingRect(text).width()) / 2;
                else if (index == 2) x +=  width - QFontMetrics(font).boundingRect(text).width();
                else
                    qDebug() << "WTF" << __PRETTY_FUNCTION__;


                painter.setPen(colors[row]);
                painter.setFont(font);
                //qDebug() << "print:" << font.pointSize();
                painter.drawText(x, y, text);
            }
        }
        painter.end();

        progress.setValue(progress.value() + 1);
        if (progress.wasCanceled())
            break;
    }
    qDebug() << "DONE!";
}

void FormDipl::onNewTemplate()
{
    bool ok;
    QString fileName = QInputDialog::getText(this, tr(" "),
                                         tr("Введите назание шаблона:"),
                                         QLineEdit::Normal,
                                         "", &ok);
    if (!ok || fileName.isEmpty())
        return;

    fileName += ".json";


    bool done = false;
    for (int i = 0; i < ui->comboBox->count(); ++i)
    {
        if (ui->comboBox->itemText(i) == fileName)
        {
            ui->comboBox->setCurrentIndex(i);
            done = true;
        }
    }
    if (!done)
    {
        ui->comboBox->addItem(fileName);
        ui->comboBox->setCurrentIndex(ui->comboBox->count() - 1);
    }
}

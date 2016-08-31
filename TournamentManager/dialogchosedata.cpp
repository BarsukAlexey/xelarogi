#include "dialogchosedata.h"
#include "ui_dialogchosedata.h"



DialogChoseData::DialogChoseData(DialogChoseData::Type type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChoseData),
    type(type)
{
    //qDebug() << "DialogChoseData " << this->type << type;


    if (type == DialogChoseData::Type::fiting_distribution)
    {
        translation
                << std::make_pair(new QLabel("Всего:"), new QPlainTextEdit())
                << std::make_pair(new QLabel("Кол-во\nчеловек"), new QPlainTextEdit())
                << std::make_pair(new QLabel("Вес"), new QPlainTextEdit())
                << std::make_pair(new QLabel("Утро"), new QPlainTextEdit())
                << std::make_pair(new QLabel("День"), new QPlainTextEdit())
                << std::make_pair(new QLabel("Вечер"), new QPlainTextEdit());
    }
    else if (type == DialogChoseData::Type::makeGridsForPointFighting)
    {
        translation
                << std::make_pair(new QLabel("Татами"), new QPlainTextEdit());
    }
    else if (type == DialogChoseData::Type::fighting_pair)
    {
        translation
                << std::make_pair(new QLabel("Ринг"), new QPlainTextEdit())
                << std::make_pair(new QLabel("Финал"), new QPlainTextEdit())
                << std::make_pair(new QLabel("Полуфинал"), new QPlainTextEdit());
    }
    else if (type == DialogChoseData::Type::ReportManda)
    {
        translation
                << std::make_pair(new QLabel("#"), new QPlainTextEdit())
                << std::make_pair(new QLabel("Команда"), new QPlainTextEdit())
                << std::make_pair(new QLabel("Всего"), new QPlainTextEdit());
    }



    setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);

    ui->setupUi(this);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setColumnWidth(0,400);
    ui->tableWidget->setColumnWidth(1,200);

    ui->groupBoxTitle->setEnabled(enableTitle());
    ui->groupBox_Rows->setEnabled(enableRows());
    ui->comboBoxMaxPlace->setEnabled(enableMaxPlace());

    //qDebug() << "DialogChoseData " << this->type << type;
    QDir recoredDir(getDirPath());
    for (QString file : recoredDir.entryList(QDir::Filter::Files))
    {
        ui->comboBox->addItem(file);
    }

    QGridLayout* layout = new QGridLayout();
    {
        int i = 0;
        for (std::pair<QLabel*, QPlainTextEdit*>& pair : translation)
        {
            layout->addWidget(pair.first , i, 0);
            layout->addWidget(pair.second, i, 1);
            ++i;
        }
    }
    QWidget* w = new QWidget();
    w->setLayout(layout);
    ui->scrollArea->setWidget(w);

    for (int i = 0; i < 16; ++i)
        ui->comboBoxMaxPlace->addItem(QString::number(1 << i));

    loadTemplate();

    connect(ui->pushButtonSave, &QPushButton::clicked, [this](){onSave();});
    connect(ui->pushButtonSaveAs, &QPushButton::clicked, [this](){onAddNew();});
    connect(ui->pushButtonDelete, &QPushButton::clicked, [this](){onDelete();});

    connect(ui->pushButtonAddRow, &QPushButton::clicked, [this](){onAddRow();} );
    connect(ui->pushButtonDeleteRow, &QPushButton::clicked, [this](){onDeleteRow();});

    connect(ui->tableWidget, &QTableWidget::doubleClicked, [this](const QModelIndex &index){onTableClicked(index);});
    connect(ui->comboBox, &QComboBox::currentTextChanged, [this](){loadTemplate();});

    connect(ui->checkBoxMainJudge, &QCheckBox::toggled, [this](){ ui->lineEditTitleMainJudge->setEnabled(ui->checkBoxMainJudge->isChecked()); });
    connect(ui->checkBoxMainSecretary, &QCheckBox::toggled, [this](){ ui->lineEditTitleMainSecretary->setEnabled(ui->checkBoxMainSecretary->isChecked()); });
    connect(ui->checkBoxAssociateMainJudge, &QCheckBox::toggled, [this](){ ui->lineEditTitleAssociateMainJudge->setEnabled(ui->checkBoxAssociateMainJudge->isChecked()); });

    connect(this, &DialogChoseData::accepted, [this](){
        onSave();
    });
}

DialogChoseData::~DialogChoseData()
{
    delete ui;
}

QString DialogChoseData::getTitle()
{
    return ui->lineEditTitle->text();
}

QVector<std::pair<QString, QVector<std::pair<DBUtils::TypeField, QString> > > > DialogChoseData::getData()
{
    QVector<std::pair<QString, QVector<std::pair<DBUtils::TypeField, QString> >>> res;
    for (int i = 0; i < fields.size(); ++i){
        res << make_pair(headers[i]->toPlainText(), fields[i]);
    }
    return res;
}

QVector<std::pair<int, QString> > DialogChoseData::getJudges()
{
    QVector<std::pair<int, QString> > res;
    if (ui->checkBoxMainJudge->isChecked()         ) res << std::make_pair(0, ui->lineEditTitleMainJudge->text());
    if (ui->checkBoxMainSecretary->isChecked()     ) res << std::make_pair(1, ui->lineEditTitleMainSecretary->text());
    if (ui->checkBoxAssociateMainJudge->isChecked()) res << std::make_pair(2, ui->lineEditTitleAssociateMainJudge->text());
    return res;
}

QMap<QString, QString> DialogChoseData::getTranslations()
{
    QMap<QString, QString> res;
    for (std::pair<QLabel*, QPlainTextEdit*>& pair : translation)
    {
        res[pair.first->text()] = pair.second->toPlainText();
    }
    return res;
}

int DialogChoseData::getMaxPlace()
{
    return ui->comboBoxMaxPlace->currentText().toInt();
}

QString DialogChoseData::getDirPath()
{
    if (type == DialogChoseData::Type::grids                    ) return ".\\template\\grids";
    if (type == DialogChoseData::Type::fiting_distribution      ) return ".\\template\\fiting_distribution";
    if (type == DialogChoseData::Type::weight_report            ) return ".\\template\\weighing_protocol";
    if (type == DialogChoseData::Type::WinnerReport             ) return ".\\template\\WinnerReport";
    if (type == DialogChoseData::Type::makeGridsForPointFighting) return ".\\template\\makeGridsForPointFighting";
    if (type == DialogChoseData::Type::fighting_pair            ) return ".\\template\\fighting_pair";
    if (type == DialogChoseData::Type::lol                      ) return ".\\template\\lol";
    if (type == DialogChoseData::Type::ReportManda              ) return ".\\template\\ReportMandat";
    return ".\\template";
}

bool DialogChoseData::enableTitle()
{
    if (type == DialogChoseData::Type::weight_report      ) return true;
    if (type == DialogChoseData::Type::WinnerReport       ) return true;
    if (type == DialogChoseData::Type::fighting_pair      ) return true;
    if (type == DialogChoseData::Type::lol                ) return true;
    if (type == DialogChoseData::Type::ReportManda        ) return true;
    return false;
}

bool DialogChoseData::enableRows()
{
    if (type == DialogChoseData::Type::weight_report      ) return true;
    if (type == DialogChoseData::Type::WinnerReport       ) return true;
    if (type == DialogChoseData::Type::lol                ) return true;
    return false;
}

bool DialogChoseData::enableMaxPlace()
{
    if (type == DialogChoseData::Type::WinnerReport) return true;
    return false;
}

void DialogChoseData::loadTemplate()
{
    //qDebug() << "loadTemplate";

    fields.resize(0);
    headers.resize(0);
    ui->tableWidget->setRowCount(0);
    for (std::pair<QLabel*, QPlainTextEdit*>& pair : translation)
    {
        pair.second->setPlainText("");
    }
    ui->lineEditTitle->setText("");

    if (ui->comboBox->currentIndex() == -1)
        return;

    QString openFileName = QDir(getDirPath()).filePath(ui->comboBox->currentText());

    QFile jSonFile(openFileName);
    if (!jSonFile.open(QIODevice::ReadOnly))
    {
        //QMessageBox::information(this, ". . .", "Не возможно откыть файл", QMessageBox::Yes);
        return;
    }

    QFile file;
    file.setFileName(openFileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument doc = QJsonDocument::fromJson(QString(file.readAll()).toUtf8());
    file.close();

    QJsonObject obj = doc.object();

    ui->lineEditTitle->setText(obj["title"].toString());

    QJsonArray arr = obj["Rows"].toArray();
    fields.resize(arr.size());
    headers.resize(arr.size());
    ui->tableWidget->setRowCount(arr.size());


    QVector<DBUtils::TypeField> allTypeFields = DBUtils::getAllTypeFieldl();

    for (int row = 0; row < arr.size(); ++row)
    {
        QJsonObject object = arr.at(row).toObject();

        headers[row] = new QPlainTextEdit(object["header"].toString());
        ui->tableWidget->setCellWidget(row, 1, headers[row]);

        for (QJsonValue val : object["data"].toArray())
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
    }

    QString string;

    string = obj["MainJudge"].toString();
    ui->checkBoxMainJudge->setChecked(!string.isEmpty());
    ui->lineEditTitleMainJudge->setText(string);

    string = obj["MainSecretary"].toString();
    ui->checkBoxMainSecretary->setChecked(!string.isEmpty());
    ui->lineEditTitleMainSecretary->setText(string);

    string = obj["AssociateMainJudge"].toString();
    ui->checkBoxAssociateMainJudge->setChecked(!string.isEmpty());
    ui->lineEditTitleAssociateMainJudge->setText(string);


    QJsonObject object = obj["translation"].toObject();
    for (QJsonObject::const_iterator it = object.begin(); it != object.end(); ++it)
    {
        QString key = it.key();
        QString value = it.value().toString();
        for (std::pair<QLabel*, QPlainTextEdit*>& pair : translation)
        {
            if (pair.first->text() == key)
            {
                pair.second->setPlainText(value);
            }
        }
    }


    ui->comboBoxMaxPlace->setCurrentText(QString::number(obj["maxPlace"].toInt()));
}

void DialogChoseData::onSave()
{

    QJsonObject obj;

    obj["title"] = ui->lineEditTitle->text();

    QJsonArray arr;
    for (int row = 0; row < fields.size(); ++row)
    {
        QJsonObject a;
        a["header"] = headers[row]->toPlainText();

        QJsonArray data;
        for (std::pair<DBUtils::TypeField, QString> pair : fields[row])
        {
            QJsonObject obj;
            obj["id"] = pair.first;
            obj["text"] = pair.second;
            data << obj;
        }
        a["data"] = data;

        arr.push_back(a);
    }
    obj["Rows"] = arr;

    obj["MainJudge"]          = ui->checkBoxMainJudge->isChecked()         ? ui->lineEditTitleMainJudge->text()          : "";
    obj["MainSecretary"]      = ui->checkBoxMainSecretary->isChecked()     ? ui->lineEditTitleMainSecretary->text()      : "";
    obj["AssociateMainJudge"] = ui->checkBoxAssociateMainJudge->isChecked()? ui->lineEditTitleAssociateMainJudge->text() : "";

    QJsonObject trans;
    for (std::pair<QLabel*, QPlainTextEdit*>& pair : translation)
    {
      trans[pair.first->text()] = pair.second->toPlainText();
    }

    obj["translation"] = trans;

    obj["maxPlace"] = ui->comboBoxMaxPlace->currentText().toInt();


    QString fullPath = QDir(getDirPath()).filePath(ui->comboBox->currentText());
    QFile saveFile(fullPath);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }
    saveFile.write(QJsonDocument(obj).toJson());
}

void DialogChoseData::onAddNew()
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

void DialogChoseData::onDelete()
{
    if (ui->comboBox->currentIndex() == -1)
        return;
    QMessageBox::StandardButton localQuestion = QMessageBox::question(0, "", "Удалить шаблон?");
    if (localQuestion == QMessageBox::StandardButton::Yes)
    {
        QDir(getDirPath()).remove(ui->comboBox->currentText());
        ui->comboBox->removeItem(ui->comboBox->currentIndex());
    }
}

void DialogChoseData::onAddRow()
{
    if (ui->comboBox->currentIndex() == -1)
        return;

    const int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row + 1);

    headers << new QPlainTextEdit();
    ui->tableWidget->setCellWidget(row, 1, headers[row]);

    fields << QVector<std::pair<DBUtils::TypeField, QString>>();
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem("Не выбрано"));
}

void DialogChoseData::onDeleteRow()
{
    int row = ui->tableWidget->currentRow();
    if (row == -1) return;

    fields.remove(row);
    headers.remove(row);
}

void DialogChoseData::onTableClicked(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    if (index.column() == 0)
    {
        DialogSelectFieldsForDimloma dlg(this, fields[index.row()]);
        if (dlg.exec() == QDialog::Accepted)
        {
            fields[index.row()] = dlg.getFields();
            ui->tableWidget->setItem(index.row(), index.column(), new QTableWidgetItem(DBUtils::toString(fields[index.row()])));
        }
    }
}

void DialogChoseData::accept()
{
    if (ui->comboBox->currentIndex() != -1)
        QDialog::accept();
}

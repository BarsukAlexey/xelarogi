#include "formdipl.h"
#include "ui_formdipl.h"

FormDipl::FormDipl(long long UID_tournament, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDipl),
    UID_tournament(UID_tournament)
{
    ui->setupUi(this);

    ui->tableWidget->resizeColumnsToContents();

    connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(ui->pushButtonDelete, SIGNAL(clicked()), this, SLOT(deleteRow()));
    connect(ui->tableWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onTableClicked(const QModelIndex &)));
    connect(ui->pushButtonPrint, &QPushButton::clicked, this, &FormDipl::onPushPrint);

    addRow();
    addRow();
    fields[0] = QVector<QString>({"Молодец", "01. Фамилия", "02. Имя"});
    fields[1] = QVector<QString>({"05. Диапозон дней рождений (1997-1999)", "г.р."});
    dynamic_cast<QSpinBox*>(ui->tableWidget->cellWidget(0, 3))->setValue(20);
    dynamic_cast<QSpinBox*>(ui->tableWidget->cellWidget(0, 4))->setValue(30);
    dynamic_cast<QSpinBox*>(ui->tableWidget->cellWidget(0, 5))->setValue(40);
    dynamic_cast<QSpinBox*>(ui->tableWidget->cellWidget(0, 6))->setValue(100);

    dynamic_cast<QSpinBox*>(ui->tableWidget->cellWidget(1, 3))->setValue(20);
    dynamic_cast<QSpinBox*>(ui->tableWidget->cellWidget(1, 4))->setValue(100);
    dynamic_cast<QSpinBox*>(ui->tableWidget->cellWidget(1, 5))->setValue(250);
    dynamic_cast<QSpinBox*>(ui->tableWidget->cellWidget(1, 6))->setValue(100);

    onPushPrint();


    resize(1500, 500);


}

FormDipl::~FormDipl()
{
    delete ui;
}

QString FormDipl::convertToRoman(int val) {
    QString res;

    QStringList huns({"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"});
    QStringList tens({"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"});
    QStringList ones({"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"});

    while (val >= 1000) {
        res += "M";
        val -= 1000;
    }

    res += huns[val / 100];
    val %= 100;

    res += tens[val / 10];
    val %= 10;

    res += ones[val];

    return res;
}

void FormDipl::onTableClicked(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    if (index.column() == 0)
    {
        DialogSelectFieldsForDimloma dlg(this);
        if (dlg.exec() == QDialog::Accepted)
        {

            fields[index.row()] = dlg.getFields();

            QString str;
            for (QString s : fields[index.row()])
            {
                if (!str.isEmpty())
                    str += "; ";
                str += s;
            }
            ui->tableWidget->setItem(index.row(), index.column(), new QTableWidgetItem(str));
        }
    }
    else if (index.column() == 2)
    {
        QFontDialog dlg(this);

        if (dlg.exec() == QDialog::Accepted)
        {
            QFont font = dlg.selectedFont();

            QTableWidgetItem *newItem = new QTableWidgetItem(font.toString());
            ui->tableWidget->setItem(index.row(), index.column(), newItem);

            fonts[index.row()] = font;
        }
    }

    ui->tableWidget->resizeColumnsToContents();
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

    for (int i = 0; i < 4; ++i)
    {
        QSpinBox *box = new QSpinBox(ui->tableWidget);
        box->setMinimum(1);
        box->setMaximum(100500);
        ui->tableWidget->setCellWidget(row, column++, box);
    }

    ui->tableWidget->resizeColumnsToContents();

    fonts << QFont();
    fields << QVector<QString>();
}

void FormDipl::deleteRow()
{
    qDebug() << "deleteRow";
    for(QModelIndex index : ui->tableWidget->selectionModel()->selectedRows())
    {
        ui->tableWidget->removeRow(index.row());
        qDebug() << "deleteRow" << index.row();
        fonts.remove(index.row());
        fields.remove(index.row());
        break;
    }

    ui->tableWidget->resizeColumnsToContents();
}

void FormDipl::onPushPrint()
{
    QString path = "trash";
    QDir dir(path);
    dir.setNameFilters(QStringList() << "*.*");
    dir.setFilter(QDir::Files);
    foreach(QString dirFile, dir.entryList())
    {
        dir.remove(dirFile);
    }

    QMap<QString, DialogSelectFieldsForDimloma::TypeField> map = DialogSelectFieldsForDimloma().getMap();

    for (long long uidTC : DBUtils::get_UIDs_of_TOURNAMENT_CATEGORIES(UID_tournament))
    {
        QVector<long long> uidOfWinner = DBUtils::getUidOfWinner(uidTC, 4);
        for (int i = 0; i < uidOfWinner.size(); ++i)
        {
            long long uidOrder = uidOfWinner[i];
            const int place = i + 1;

            int coef = qMin(900 / ui->spinBoxWidth->value(), 900 / ui->spinBoxHeight->value());
            QPixmap pm(coef * ui->spinBoxWidth->value(), coef * ui->spinBoxHeight->value());
            pm.fill(Qt::yellow);
            QPainter painter(&pm);

            for (int index = 0; index < 1000; ++index)
            {
                int y = pm.height() * 10 / ui->spinBoxHeight->value();
                painter.drawLine(QPoint(0, index * y), QPoint(pm.width(), index * y));

                int x = pm.width() * 10 / ui->spinBoxWidth->value();
                painter.drawLine(QPoint(index * x, 0), QPoint(index * x, pm.height()));
            }
            //     ui->spinBoxHeight->value() / pm.height = 10 / ??

            for (int row = 0; row < fonts.size(); ++row)
            {
                QString text;
                for (QString field : fields[row])
                {
                    if (!text.isEmpty())
                        text += " ";

                    if (!map.contains(field))
                    {
                        text += field;
                    }
                    else
                    {
                        DialogSelectFieldsForDimloma::TypeField typeField = map[field];
                        if (typeField == DialogSelectFieldsForDimloma::TypeField::secondName)
                        {
                            text += DBUtils::getField("SECOND_NAME", "ORDERS", uidOrder, __PRETTY_FUNCTION__);
                        }
                        else if (typeField == DialogSelectFieldsForDimloma::TypeField::firstName)
                        {
                            text += DBUtils::getField("FIRST_NAME", "ORDERS", uidOrder, __PRETTY_FUNCTION__);
                        }
                        else if (typeField == DialogSelectFieldsForDimloma::TypeField::patromicName)
                        {
                            text += DBUtils::getField("PATRONYMIC", "ORDERS", uidOrder, __PRETTY_FUNCTION__);
                        }
                        else if (typeField == DialogSelectFieldsForDimloma::TypeField::ageRange)
                        {
                            text += DBUtils::getNormanAgeRangeFromTOURNAMENT_CATEGORIES(uidTC);

                        }
                        else if (typeField == DialogSelectFieldsForDimloma::TypeField::weightRange)
                        {
                            text += DBUtils::getNormanWeightRangeFromTOURNAMENT_CATEGORIES(uidTC);
                        }
                        else if (typeField == DialogSelectFieldsForDimloma::TypeField::weight)
                        {
                            text += DBUtils::getWeightAsOneNumberPlusMinus(uidTC);
                        }
                        else if (typeField == DialogSelectFieldsForDimloma::TypeField::place)
                        {
                            text += QString::number(place);
                        }
                        else if (typeField == DialogSelectFieldsForDimloma::TypeField::placeRome)
                        {
                            text += convertToRoman(place);
                        }

                        else if (typeField == DialogSelectFieldsForDimloma::TypeField::placeRome)
                        {
                            text += DBUtils::getField("NAME", "AGE_CATEGORIES", DBUtils::getField("AGE_CATEGORY_FK", "TOURNAMENT_CATEGORIES", uidTC, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
                        }
                        else
                        {
                            qDebug() << "WTF" << __PRETTY_FUNCTION__;
                        }
                    }
                }

                int fontSize = dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 3))->value();
                int x        = dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 4))->value();
                int y        = dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 5))->value();
                int width    = dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 6))->value();
                int index    = dynamic_cast<QComboBox*>(ui->tableWidget->cellWidget(row, 1))->currentIndex();
                QRectF rect(x     * pm.width()  / ui->spinBoxWidth ->value(),
                            0,
                            width * pm.width()  / ui->spinBoxWidth ->value(),
                            y     * pm.height() / ui->spinBoxHeight->value());

                int align = Qt::AlignBottom;
                if      (index == 0) align |= Qt::AlignLeft;
                else if (index == 1) align |= Qt::AlignHCenter;
                else if (index == 2) align |= Qt::AlignRight;
                else
                    qDebug() << "WTF" << __PRETTY_FUNCTION__;

                QFont font = fonts[row];

                font.setPixelSize(fontSize * pm.height() / ui->spinBoxHeight->value()); //  ui->spinBoxHeight->value() / pm.height() = fontSize / ???
                qDebug() << uidOrder << fontSize << fontSize * pm.height() / ui->spinBoxHeight->value();

                //painter.setFont(font);
                painter.drawText(rect, align, text);
                //TODO рисовать по базовой линиии =)
            }

            pm.save("trash\\file" + QString::number(uidOrder) + ".png", "png");
        }
    }
}

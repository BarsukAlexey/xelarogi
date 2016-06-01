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
        QFont font = QFontDialog::getFont(0, fonts[index.row()], this);
        fonts[index.row()] = font;
        ui->tableWidget->setItem(index.row(), index.column(), new QTableWidgetItem(font.toString()));
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

    ui->tableWidget->resizeColumnsToContents();

    fonts << QFont();
    fields << QVector<QString>();
}

void FormDipl::deleteRow()
{
    for(QModelIndex index : ui->tableWidget->selectionModel()->selectedRows())
    {
        ui->tableWidget->removeRow(index.row());
        fonts.remove(index.row());
        fields.remove(index.row());
        break;
    }

    ui->tableWidget->resizeColumnsToContents();
}




void FormDipl::onPushPrint()
{
    QString dirPath = QFileDialog::getExistingDirectory(this);
    if (dirPath.isEmpty()) return;

    QMap<QString, DialogSelectFieldsForDimloma::TypeField> map = DialogSelectFieldsForDimloma().getMap();

    for (long long uidTC : DBUtils::get_UIDs_of_TOURNAMENT_CATEGORIES(UID_tournament))
    {
        QVector<long long> uidOfWinner = DBUtils::getUidOfWinner(uidTC);
        if (uidOfWinner.isEmpty())
            continue;

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



        for (int i = 0; i < uidOfWinner.size(); ++i)
        {
            long long uidOrder = uidOfWinner[i];
            const int place = qMin(i + 1, 3); //




//            сетка в 1 см
//            for (int index = 0; index < 3; ++index)
//            {
//                double y = 10.0 * printer.height() / printer.heightMM();
//                painter.drawLine(QPoint(0, index * y), QPoint(printer.width(), index * y));

//                double x = 10.0 * printer.width() / printer.widthMM();
//                painter.drawLine(QPoint(index * x, 0), QPoint(index * x, printer.height()));
//            }

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
                        else if (typeField == DialogSelectFieldsForDimloma::TypeField::sexAgeType)
                        {
                            text += DBUtils::getField("NAME", "AGE_CATEGORIES", DBUtils::getField("AGE_CATEGORY_FK", "TOURNAMENT_CATEGORIES", uidTC, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
                        }
                        else if (typeField == DialogSelectFieldsForDimloma::TypeField::TYPES)
                        {
                            text += DBUtils::getField("NAME", "TYPES", DBUtils::getField("TYPE_FK", "TOURNAMENT_CATEGORIES", uidTC, __PRETTY_FUNCTION__), __PRETTY_FUNCTION__);
                        }
                        else
                        {
                            qDebug() << "WTF" << __PRETTY_FUNCTION__;
                        }
                    }
                }

                QFont font = fonts[row];
                int x        = dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 3))->value() * printer.width()  / ui->spinBoxWidth ->value();
                int y        = dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 4))->value() * printer.height() / ui->spinBoxHeight->value();
                int width    = dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 5))->value() * printer.width()  / ui->spinBoxWidth ->value();

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
                }

                int index = dynamic_cast<QComboBox*>(ui->tableWidget->cellWidget(row, 1))->currentIndex();
                if      (index == 0);
                else if (index == 1) x += (width - QFontMetrics(font).boundingRect(text).width()) / 2;
                else if (index == 2) x +=  width - QFontMetrics(font).boundingRect(text).width();
                else
                    qDebug() << "WTF" << __PRETTY_FUNCTION__;

                painter.setFont(font);
                painter.drawText(x, y, text);


            }
            if (i + 1 != uidOfWinner.size())
                qDebug() << printer.newPage();
        }
        painter.end();
    }
}

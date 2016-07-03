#include "formdipl.h"
#include "ui_formdipl.h"

FormDipl::FormDipl(long long UID_tournament, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDipl),
    UID_tournament(UID_tournament)
{
    ui->setupUi(this);

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setColumnWidth(0,175);
    ui->tableWidget->setColumnWidth(1,120);
    ui->tableWidget->setColumnWidth(2,175);

    connect(ui->pushButtonAdd, SIGNAL(clicked()), this, SLOT(addRow()));
    connect(ui->pushButtonDelete, SIGNAL(clicked()), this, SLOT(deleteRow()));
    connect(ui->tableWidget, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onTableClicked(const QModelIndex &)));
    connect(ui->pushButtonPrint, &QPushButton::clicked, this, &FormDipl::onPushPrint);
    connect(ui->radioButtonDiplom, &QRadioButton::clicked, [this](){
        ui->spinBoxMaxPlace->setEnabled(ui->radioButtonDiplom->isChecked());
        ui->label_5->setEnabled(ui->radioButtonDiplom->isChecked());
    });
    connect(ui->radioButtonBadge, &QRadioButton::clicked, [this](){
        ui->spinBoxMaxPlace->setEnabled(ui->radioButtonDiplom->isChecked());
        ui->label_5->setEnabled(ui->radioButtonDiplom->isChecked());
    });
}

FormDipl::~FormDipl()
{
    delete ui;
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
        ui->tableWidget->setItem(index.row(), index.column(), new QTableWidgetItem(font.toString()));
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

    QString dirPath = QFileDialog::getExistingDirectory(this);
    //QString dirPath = "C:\\Trash";
    if (dirPath.isEmpty()) return;


    for (long long uidTC : DBUtils::get_UIDs_of_TOURNAMENT_CATEGORIES(UID_tournament))
    {
        QVector<long long> UIDOrder = DBUtils::get_UIDOrder_for_TC(uidTC);
        std::sort(UIDOrder.begin(), UIDOrder.end(), [](const long long& UIDOrder0, const long long& UIDOrder1)  -> bool {
            std::pair<int, int> place0 = DBUtils::getPlace(UIDOrder0);
            std::pair<int, int> place1 = DBUtils::getPlace(UIDOrder1);
            QString name0 = UIDOrder0 <= 0? "" : DBUtils::getSecondNameAndFirstName(UIDOrder0);
            QString name1 = UIDOrder1 <= 0? "" : DBUtils::getSecondNameAndFirstName(UIDOrder1);
            return  place0 < place1 || (place0 == place1 && name0 < name1);
        });
        if (UIDOrder.isEmpty() || (ui->radioButtonDiplom->isChecked() && DBUtils::getPlace(UIDOrder[0]).first == -1))
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

        bool isThisFirstPage = true;
        for (int i = 0; i < UIDOrder.size(); ++i)
        {
            const long long uidOrder = UIDOrder[i];
            std::pair<int, int> place = DBUtils::getPlace(uidOrder);
            if (ui->radioButtonDiplom->isChecked() && ui->spinBoxMaxPlace->value() < place.first)
                continue;

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
                QString text;
                for (std::pair<DBUtils::TypeField, QString> field : fields[row])
                {
                    if (!text.isEmpty())
                        text += " ";
                    if (field.first == DBUtils::TypeField::PlainText)
                        text += field.second;
                    else
                        text += DBUtils::get(field, uidOrder);
                }

                QFont font = fonts[row];
                int x        = dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 4))->value() * printer.width()  / ui->spinBoxWidth ->value();
                int y        = dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 5))->value() * printer.height() / ui->spinBoxHeight->value();
                int width    = dynamic_cast<QSpinBox* >(ui->tableWidget->cellWidget(row, 6))->value() * printer.width()  / ui->spinBoxWidth ->value();

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
                painter.drawText(x, y, text);
            }
        }
        painter.end();

    }
    /**/
}

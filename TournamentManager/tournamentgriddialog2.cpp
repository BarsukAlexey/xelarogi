#include "tournamentgriddialog2.h"
#include "renderareawidget.h"
#include <QScrollArea>
#include <QGridLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QSplitter>
#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>

TournamentGridDialog2::TournamentGridDialog2(const QSqlDatabase &database, long long tournamentUID, QWidget *parent)
    : database(database),
      tournamentUID(tournamentUID),
      QDialog(parent)
{

    QWidget *leftPane = new QWidget;
    leftPane->setBackgroundRole(QPalette::Dark);
    QComboBox *qComboBoxSelectCategory = new QComboBox;
    QTableWidget *qTableWidget = new QTableWidget(2, 3);
    QPushButton *buttonGenerate = new QPushButton("Сгенерировать сетку");
    {
        QGridLayout *mainLayout = new QGridLayout;
        mainLayout->addWidget(qComboBoxSelectCategory, 0, 0);
        mainLayout->addWidget(qTableWidget, 1, 0);
        mainLayout->addWidget(buttonGenerate, 2, 0);
        leftPane->setLayout(mainLayout);
    }



    QWidget *rightPane = new QWidget;
    QPushButton *buttonSave = new QPushButton("Сохранить в Excel");
    QSpinBox *widthSpinBox = new QSpinBox;
    QSpinBox *heightSpinBox = new QSpinBox;
    widthSpinBox->setValue(100);
    heightSpinBox->setValue(20);
    widthSpinBox->setMaximum(1000);

    QScrollArea *pQScrollArea = new QScrollArea;
    RenderAreaWidget *pRenderArea = new RenderAreaWidget(pQScrollArea, widthSpinBox->value(), heightSpinBox->value());
    pQScrollArea->setWidget(pRenderArea);

    QLabel *widthQLabel = new QLabel("Ширина:");
    widthQLabel->setAlignment(Qt::AlignRight | Qt::AlignCenter);
    QLabel *heightQLabel = new QLabel("Высота:");
    heightQLabel->setAlignment(Qt::AlignRight | Qt::AlignCenter);
    {
        QGridLayout *mainLayout = new QGridLayout;

        mainLayout->addWidget(buttonSave, 0, 0);
        mainLayout->addWidget(widthQLabel, 0, 1);
        mainLayout->addWidget(widthSpinBox, 0, 2);
        mainLayout->addWidget(heightQLabel, 0, 3);
        mainLayout->addWidget(heightSpinBox, 0, 4);

        mainLayout->addWidget(pQScrollArea, 1, 0, 1, 5);

        rightPane->setLayout(mainLayout);
    }


    QSplitter *splitter = new QSplitter;
    splitter->addWidget(leftPane);
    splitter->addWidget(rightPane);
    splitter->setHandleWidth(10);
    splitter->setStyleSheet("QSplitter::handle{background-color: black;}");


    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(splitter, 0, 0);
    setLayout(mainLayout);
    resize(800, 800);

    connect(buttonGenerate, SIGNAL(clicked(bool)), pRenderArea, SLOT(setPlayers()));
    connect(widthSpinBox, SIGNAL(valueChanged(int)), pRenderArea, SLOT(widthChanged(int)));
    connect(heightSpinBox, SIGNAL(valueChanged(int)), pRenderArea, SLOT(heightChanged(int)));


    //setWindowFlags(Qt::Window);
    showMaximized();
}

void TournamentGridDialog2::playerChanged()
{

}

TournamentGridDialog2::~TournamentGridDialog2()
{

}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QVector>
#include <QLoggingCategory>
#include <string>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int numFloors = 5;
    int numElevators = 2;
    int floorUISize = 20;

    building = new Building(numFloors, numElevators);

    connect(ui->pushButton, SIGNAL(released()), this, SLOT(doSomething()));
    connect(ui->fireButton, SIGNAL(released()), building, SLOT(simFire()));
    connect(ui->powerButton, SIGNAL(released()), building, SLOT(simPowerOut()));


    ui->gridLayout->setSpacing(0);
    ui->gridLayout->setHorizontalSpacing(10);

    //selEle = building->elevators.at(0);
    connectToEle(building->elevators.at(0), ui);






    for(int floorNumber = 0; floorNumber < numFloors; floorNumber++) {
        QPushButton* upButton = new QPushButton("▲");
        upButton->setFixedSize(floorUISize,floorUISize);

        QPushButton* downButton = new QPushButton("▼");
        downButton->setFixedSize(floorUISize,floorUISize);

        QVBoxLayout *qVlayout = new QVBoxLayout();




        qVlayout->addWidget(upButton);
        qVlayout->addWidget(downButton);
        qVlayout->setSpacing(0);

        QWidget* containerWidget = new QWidget();
        containerWidget->setLayout(qVlayout);

        ui->gridLayout->addWidget(containerWidget, numFloors - floorNumber - 1, 0);

        Floor* floor = building->floors.at(floorNumber);
        connect(upButton, SIGNAL(released()), floor, SLOT(pressUp()));
        connect(downButton, SIGNAL(released()), floor, SLOT(pressDown()));

        QString highlightOn = "QPushButton {color: cyan;}";


        connect(floor, &Floor::eleRequested, this, [upButton, highlightOn](Floor* floor){
            upButton->setStyleSheet(floor->upButton ? highlightOn : "");
        });


        connect(floor, &Floor::eleRequested, this, [downButton, highlightOn](Floor* floor){
            downButton->setStyleSheet(floor->downButton ? highlightOn : "");
        });


        QString floorNumStr = QString("%1").arg(floorNumber);

        QPushButton* eleFloorButton = new QPushButton(QString(floorNumStr));
        ui->eleButtonLayout->addWidget(eleFloorButton, floorNumber / 2, floorNumber % 2);


        for(int eleNum = 0; eleNum < numElevators; eleNum++) {
            //QLabel *doorLabel = new QLabel("∥");


            QLabel* doorLabel = new QLabel("||");
            doorLabel->setFixedSize(floorUISize*2,floorUISize*2);
            doorLabel->setFrameStyle(QFrame::Box |QFrame::Plain);
            doorLabel->setLineWidth(1);
            doorLabel->setAlignment(Qt::AlignCenter);
            QFont font = doorLabel->font();
            font.setPointSize(36);
            doorLabel->setFont(font);
            ui->gridLayout->addWidget(doorLabel, numFloors - floorNumber - 1, eleNum + 1);

            connect(floor, &Floor::doorsChanged, this, [doorLabel, highlightOn, eleNum](Floor* floor){
                doorLabel->setText(floor->doors[eleNum] ? "| |" : "||");
            });

            if (floorNumber == numFloors - 1) {
                QPushButton *eleButton = new QPushButton("");
                //upButton->setFixedSize(floorUISize,floorUISize);
                ui->gridLayout->addWidget(eleButton, numFloors, eleNum + 1);
                connect(eleButton, &QPushButton::released, this, [=](){
                    this->connectToEle(building->elevators.at(eleNum), ui);
                });
            }

        }



    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doSomething()
{
    qInfo("Hello World!");
}

void MainWindow::connectToEle(Elevator* ele, Ui::MainWindow* ui)
{
    if(selEle != nullptr) {
        disconnect(selEle, &Elevator::floorSensed, this, nullptr);
    }

    selEle = ele;

    QLabel* floorLabel = ui->floorNumLabel;

    auto floorUpdateLambda = [=](){
        QString floorNumStr = QString("Floor: %1").arg(selEle->getFloorNum());
        floorLabel->setText(floorNumStr);
    };

    connect(selEle, &Elevator::floorSensed, this, floorUpdateLambda);


    QString floorNumStr = QString("Floor: %1").arg(selEle->getFloorNum());
    ui->floorNumLabel->setText(floorNumStr);

    QLabel* eleLabel = ui->eleNumLabel;
    QString eleNumStr = QString("Elevator: %1").arg(ele->eleNum);
    eleLabel->setText(eleNumStr);
}



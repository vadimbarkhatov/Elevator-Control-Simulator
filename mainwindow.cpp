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
    int numFloors = 12;
    int numElevators = 3;
    int floorUISize = 20;

    building = new Building(numFloors, numElevators);

    connect(ui->pushButton, SIGNAL(released()), this, SLOT(doSomething()));
    connect(ui->fireButton, SIGNAL(released()), building, SLOT(simFire()));
    connect(ui->powerButton, SIGNAL(released()), building, SLOT(simPowerOut()));


    ui->gridLayout->setSpacing(0);
    ui->gridLayout->setHorizontalSpacing(10);

    for(int floorNumber = 0; floorNumber < numFloors; floorNumber++) {
        QPushButton *upButton = new QPushButton("▲");
        upButton->setFixedSize(floorUISize,floorUISize);

        QPushButton *downButton = new QPushButton("▼");
        downButton->setFixedSize(floorUISize,floorUISize);

        QVBoxLayout *qVlayout = new QVBoxLayout();


        qVlayout->addWidget(upButton);
        qVlayout->addWidget(downButton);
        qVlayout->setSpacing(0);

        QWidget *containerWidget = new QWidget();
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

        QPushButton *eleFloorButton = new QPushButton(QString(floorNumStr));
        ui->eleButtonLayout->addWidget(eleFloorButton, floorNumber / 2, floorNumber % 2);
        //upButton->setFixedSize(floorUISize,floorUISize);





        for(int elevator = 0; elevator < numElevators; elevator++) {
            //QLabel *doorLabel = new QLabel("∥");
            QLabel *doorLabel = new QLabel("||");
            doorLabel->setFixedSize(floorUISize*2,floorUISize*2);
            doorLabel->setFrameStyle(QFrame::Box |QFrame::Plain);
            doorLabel->setLineWidth(1);
            doorLabel->setAlignment(Qt::AlignCenter);
            QFont font = doorLabel->font();
            font.setPointSize(36);
            doorLabel->setFont(font);
            ui->gridLayout->addWidget(doorLabel, numFloors - floorNumber - 1, elevator + 1);

            connect(floor, &Floor::doorsChanged, this, [doorLabel, highlightOn, elevator](Floor* floor){
                doorLabel->setText(floor->doors[elevator] ? "| |" : "||");
            });

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

void MainWindow::connectToEle(Elevator* ele)
{

}

//void MainWindow::onEleRequest(Floor* floor)
//{
//    //qInfo("Elevator requested");
//    int floorNumber = floor->floorNumber;

//    qInfo() << QString("Ele requested on floor %1").arg(floorNumber);

//    QString highlightOn = "QPushButton {background-color: yellow;}";
//    QString highlightOff = "QPushButton {background-color: gray;}";

//    qInfo() << QString("Up button: %1").arg(floor->upButton);
//    qInfo() << QString("Down button: %1").arg(floor->downButton);

//    if(floor->upButton) upButtons.at(floorNumber)->setStyleSheet(highlightOn);
//    else upButtons.at(floorNumber)->setStyleSheet("");

//    if(floor->downButton) downButtons.at(floor->floorNumber)->setStyleSheet(highlightOn);
//    else downButtons.at(floor->floorNumber)->setStyleSheet("");

//}

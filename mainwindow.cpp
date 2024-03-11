#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "floor.h"
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
    int numElevators = 5;
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
        //upButtons.append(upButton);

        QPushButton *downButton = new QPushButton("▼");
        downButton->setFixedSize(floorUISize,floorUISize);
        //downButtons.append(downButton);

        QVBoxLayout *qVlayout = new QVBoxLayout();


        qVlayout->addWidget(upButton);
        qVlayout->addWidget(downButton);
        qVlayout->setSpacing(0);

        QWidget *containerWidget = new QWidget();
        containerWidget->setLayout(qVlayout);

        ui->gridLayout->addWidget(containerWidget, numFloors - floorNumber - 1, 0);

        Floor* floor = new Floor(floorNumber);
        connect(upButton, SIGNAL(released()), floor, SLOT(pressUp()));
        connect(downButton, SIGNAL(released()), floor, SLOT(pressDown()));
        building->floors.append(floor);

        connect(upButton, &QPushButton::released, [upButton, floor](){
            upButton->setStyleSheet(floor->upButton ? "QPushButton {background-color: yellow;}" : "");
        });

        connect(downButton, &QPushButton::released, [downButton, floor](){
            downButton->setStyleSheet(floor->downButton ? "QPushButton {background-color: yellow;}" : "");
        });




        for(int elevator = 0; elevator < numElevators; elevator++) {
            QLabel *shaftLabel = new QLabel("∥");
            shaftLabel->setFixedSize(floorUISize*2,floorUISize*2);
            shaftLabel->setFrameStyle(QFrame::Box |QFrame::Plain);
            shaftLabel->setLineWidth(1);
            shaftLabel->setAlignment(Qt::AlignCenter);
            QFont font = shaftLabel->font();
            font.setPointSize(36);
            shaftLabel->setFont(font);
            ui->gridLayout->addWidget(shaftLabel, floorNumber, elevator + 1);
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

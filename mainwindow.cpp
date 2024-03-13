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



    int numFloors = 7;
    int numElevators = 3;

    building = new Building(numFloors, numElevators);

    connect(ui->fireButton, SIGNAL(released()), building, SLOT(simFire()));
    connect(ui->powerButton, SIGNAL(released()), building, SLOT(simPowerOut()));



    ui->gridLayout->setSpacing(0);
    ui->gridLayout->setHorizontalSpacing(10);
    int floorUISize = 50;

    for(int floorNum = 0; floorNum < numFloors; floorNum++) {
        QPushButton* upButton = new QPushButton("▲");
        upButton->setFixedSize(floorUISize/2,floorUISize/2);

        QPushButton* downButton = new QPushButton("▼");
        downButton->setFixedSize(floorUISize/2,floorUISize/2);

        QVBoxLayout* qVlayout = new QVBoxLayout();
        qVlayout->addWidget(upButton);
        qVlayout->addWidget(downButton);
        qVlayout->setSpacing(0);

        QWidget* containerWidget = new QWidget();
        containerWidget->setLayout(qVlayout);
        ui->gridLayout->addWidget(containerWidget, numFloors - floorNum - 1, 0);

        Floor* floor = building->floors.at(floorNum);
        connect(upButton, SIGNAL(released()), floor, SLOT(pressUp()));
        connect(downButton, SIGNAL(released()), floor, SLOT(pressDown()));

        QString highlightOn = "QPushButton {color: cyan;}";
        connect(floor, &Floor::eleRequested, this, [upButton, highlightOn](Floor* floor){
            upButton->setStyleSheet(floor->upButton ? highlightOn : "");
        });
        connect(floor, &Floor::eleRequested, this, [downButton, highlightOn](Floor* floor){
            downButton->setStyleSheet(floor->downButton ? highlightOn : "");
        });

        QString floorNumStr = QString("%1").arg(floorNum);

        QPushButton* eleFloorButton = new QPushButton(QString(floorNumStr));
        ui->eleButtonLayout->addWidget(eleFloorButton, floorNum / 2, floorNum % 2);
        connect(eleFloorButton, &QPushButton::released, this, [this, floorNum]() {
            this->onFloorSelected(floorNum);
        });



        for(int eleNum = 0; eleNum < numElevators; eleNum++) {
            QLabel* doorLabel = new QLabel("|");
            doorLabel->setFixedSize(floorUISize,floorUISize);
            doorLabel->setFrameStyle(QFrame::Box |QFrame::Plain);
            doorLabel->setLineWidth(1);
            doorLabel->setAlignment(Qt::AlignCenter);
            QFont font = doorLabel->font();
            font.setPointSize(46);
            doorLabel->setFont(font);
            ui->gridLayout->addWidget(doorLabel, numFloors - floorNum - 1, eleNum + 1);

            connect(floor, &Floor::doorsChanged, this, [doorLabel, highlightOn, eleNum](Floor* floor){
                doorLabel->setText(floor->doors[eleNum] ? "| |" : "|");
            });

        }

    }



    connectToEle(building->elevators.at(0), ui);

    for(Elevator* ele : building->elevators) {
        //TODO: fix, why is is it floorSensed?
        connect(ele, &Elevator::floorSensed, this, [this]() {
            this->onFloorSelected(-1);
        });


        QPushButton *eleButton = new QPushButton("");


        eleButton->setStyleSheet("QPushButton {"
                                 "border: 3px solid yellow;"
                                 "background-color: transparent; }"
                                 "QPushButton:hover {"
                                 "background-color: rgba(255,255, 0, 64); }");

        ui->gridLayout->addWidget(eleButton, ui->gridLayout->rowCount() - ele->getFloorNum() -1, ele->eleNum + 1);

        connect(eleButton, &QPushButton::released, this, [this, ele](){
            this->connectToEle(ele, ui);
        });

        connect(ele, &Elevator::floorSensed, eleButton, [ele, eleButton, this](){
            ui->gridLayout->removeWidget(eleButton);
            ui->gridLayout->addWidget(eleButton, ui->gridLayout->rowCount() - ele->getFloorNum() -1, ele->eleNum + 1);
        });

        eleButton->setFixedSize(floorUISize,floorUISize);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doSomething()
{
    qInfo("Doing something!");
}

void MainWindow::onFloorSelected(int floorNum)
{
    if(floorNum >= 0)
        selEle->selectFloor(floorNum);

    for(int i = 0; i < ui->eleButtonLayout->count(); i++) {
        QString highlightOn = "QPushButton {color: cyan;}";
        QLayoutItem* item = ui->eleButtonLayout->itemAt(i);
        if(item->widget()) {
           if(selEle->floorButtons.at(i))
               item->widget()->setStyleSheet(highlightOn);
           else
               item->widget()->setStyleSheet("");
        }

    }
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

    onFloorSelected(-1);
}



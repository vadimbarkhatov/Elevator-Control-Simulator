#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QVector>
#include <QLoggingCategory>
#include <string>
#include <QIntValidator>
#include <QtDebug>
#include <QFile>
#include <QTextStream>
#include <logger.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //could be changed for a different number of elevators and floors but it might not be pretty
    int numFloors = 7;
    int numElevators = 3;

    building = new Building(numFloors, numElevators);

    connect(ui->fireButton, SIGNAL(released()), building, SLOT(simFire()));
    connect(ui->powerButton, SIGNAL(released()), building, SLOT(simPowerOut()));

    setupFloorDisplay();
    setupElevatorDisplay();

    //qInfo is redirected to a global message handler and hooked up to a text edit
    setRedirect(ui->consoleTextEdit);
    qInstallMessageHandler(msgHandler);
}


//sets up the display of the floor up/down buttons and elevator display buttons
void MainWindow::setupFloorDisplay()
{
    ui->gridLayout->setSpacing(0);
    ui->gridLayout->setHorizontalSpacing(10);

    int numFloors = building->floors.count();
    int numElevators = building->elevators.count();

    for(int floorNum = 0; floorNum < numFloors; floorNum++) {
        QPushButton* upButton = new QPushButton("▲");
        upButton->setFixedSize(floorUISize/2,floorUISize/2);

        QPushButton* downButton = new QPushButton("▼");
        downButton->setFixedSize(floorUISize/2,floorUISize/2);

        QVBoxLayout* qVlayout = new QVBoxLayout();
        if(floorNum < numFloors - 1)
            qVlayout->addWidget(upButton);
        if(floorNum > 0)
            qVlayout->addWidget(downButton);
        qVlayout->setSpacing(0);

        QWidget* containerWidget = new QWidget();
        containerWidget->setLayout(qVlayout);
        ui->gridLayout->addWidget(containerWidget, numFloors - floorNum - 1, 0);

        //hooks the up/down display buttons to the floor class
        Floor* floor = building->floors.at(floorNum);
        connect(upButton, SIGNAL(released()), floor, SLOT(pressUp()));
        connect(downButton, SIGNAL(released()), floor, SLOT(pressDown()));

        //makes it so that the up/down arrows are highlited when true
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

        setupFloorDoorDisplay(numElevators, numFloors, floorNum, floor);

    }
}

//sets up the doors visuals
void MainWindow::setupFloorDoorDisplay(int numElevators, int numFloors, int floorNum, Floor* floor)
{
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

        //hook to the floor event when doors are opened
        connect(floor, &Floor::doorsChanged, this, [doorLabel, eleNum](Floor* floor){
            doorLabel->setText(floor->doors[eleNum] ? "| |" : "|");
        });

    }
}

//sets up the elevator icons
void MainWindow::setupElevatorDisplay()
{
    connectEleToPanel(building->elevators.at(0), ui);

    for(Elevator* ele : building->elevators) {
        connect(ele, &Elevator::floorSensed, this, [this]() {
            this->onFloorSelected(-1);
        });


        QPushButton *eleButton = new QPushButton("");
        eleButton->setFixedSize(floorUISize,floorUISize);

        eleButton->setStyleSheet("QPushButton {"
                                 "border: 3px solid yellow;"
                                 "background-color: transparent; }"
                                 "QPushButton:hover {"
                                 "border: 3px solid orange;"
                                 "background-color: rgba(255,255, 0, 64); }");

        ui->gridLayout->addWidget(eleButton, ui->gridLayout->rowCount() - ele->getFloorNum() -1, ele->eleNum + 1);

        //makes is so that when the elevator is selected it's hooked up to to the elevator display
        connect(eleButton, &QPushButton::released, this, [this, ele](){
            this->connectEleToPanel(ele, ui);
        });

        connect(ele, &Elevator::floorSensed, eleButton, [ele, eleButton, this](){
            ui->gridLayout->removeWidget(eleButton);
            ui->gridLayout->addWidget(eleButton, ui->gridLayout->rowCount() - ele->getFloorNum() -1, ele->eleNum + 1);
        });


    }
}

//highlights the elevator floor buttons when pressed
void MainWindow::onFloorSelected(int floorNum)
{
    if(floorNum >= 0)
        selEle->selectFloor(floorNum);

    for(int i = 0; i < ui->eleButtonLayout->count(); i++) {
        QString highlightOn = "QPushButton {color: cyan;}";
        QLayoutItem* item = ui->eleButtonLayout->itemAt(i);
        if(item->widget()) {
           if(selEle->floorButtons[i])
               item->widget()->setStyleSheet(highlightOn);
           else
               item->widget()->setStyleSheet("");
        }

    }
}

//this could've been a lambda probably to update the LCD floor display
void MainWindow::onFloorSensed()
{
    ui->eleNumLCD->display(selEle->getFloorNum());
}

//connects the selected elevator to the elevator display
void MainWindow::connectEleToPanel(Elevator* ele, Ui::MainWindow* ui)
{
    selEle = ele;

    connect(selEle, &Elevator::floorSensed, this, &MainWindow::onFloorSensed);

    ui->eleNumLCD->display(selEle->getFloorNum());

    QLabel* eleLabel = ui->eleNumLabel;
    QString eleNumStr = QString("Elevator: %1").arg(ele->eleNum);
    eleLabel->setText(eleNumStr);

    //need to cleanup from the previous elevator
    ui->openDoorButton->disconnect();
    ui->closeDoorButton->disconnect();
    ui->doorObstacleCheck->disconnect();
    ui->eleLoadBox->disconnect();
    ui->helpButton->disconnect();


    connect(ui->openDoorButton, &QPushButton::released, selEle, &Elevator::holdOpenDoor);
    connect(ui->closeDoorButton, &QPushButton::released, selEle, &Elevator::holdCloseDoor);
    connect(ui->doorObstacleCheck, &QCheckBox::stateChanged, selEle, &Elevator::setDoorObstacle);
    connect(ui->helpButton, &QPushButton::released, selEle, &Elevator::helpRequest);


    ui->doorObstacleCheck->setChecked(selEle->doorBlocked);
    connect(ui->eleLoadBox, &QLineEdit::textChanged, selEle, &Elevator::setLoadWeight);
    ui->eleLoadBox->setValidator(new QIntValidator(0, INT_MAX, ui->eleLoadBox));
    ui->eleLoadBox->setText(QString::number(selEle->loadWeight));

    //make sure the floor buttons are synced to selected elevator
    onFloorSelected(-1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

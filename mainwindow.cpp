#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int numFloors = 2;
    int numElevators = 5;
    int floorUISize = 20;

    building = new Building(7, 3);

    connect(ui->pushButton, SIGNAL(released()), this, SLOT(doSomething()));
    connect(ui->fireButton, SIGNAL(released()), building, SLOT(simFire()));
    connect(ui->powerButton, SIGNAL(released()), building, SLOT(simPowerOut()));


    ui->gridLayout->setSpacing(0);
    ui->gridLayout->setHorizontalSpacing(10);

    for(int floor = 0; floor < numFloors; floor++) {
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

        ui->gridLayout->addWidget(containerWidget, floor, 0);


        for(int elevator = 0; elevator < numElevators; elevator++) {
            QLabel *shaftLabel = new QLabel("∥");
            shaftLabel->setFixedSize(floorUISize*2,floorUISize*2);
            shaftLabel->setFrameStyle(QFrame::Box |QFrame::Plain);
            shaftLabel->setLineWidth(1);
            shaftLabel->setAlignment(Qt::AlignCenter);
            QFont font = shaftLabel->font();
            font.setPointSize(36);
            shaftLabel->setFont(font);
            ui->gridLayout->addWidget(shaftLabel, floor, elevator + 1);
        }

    }


//    ui->floorButtons->addWidget(button1);
//    ui->floorButtons->addWidget(button2);
//    ui->floorButtons->addWidget(button3);
//    ui->floorButtons->addWidget(button4);
//    ui->floorButtons->addWidget(button5);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doSomething()
{
    qInfo("Hello World!");
}

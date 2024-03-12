#include "building.h"
#include <QTimer>

Building::Building(int numFloors, int numElevators, QObject *parent)
    : QObject{parent}
{
    initFloors(numFloors);

    for(int i = 0; i < numElevators; i++) {
        elevators.append(new Elevator());
    }

    QTimer *timer = new QTimer(this);
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, this, &Building::update);

    timer->start();

    elevators[2]->moveToFloor(2);

}

void Building::simFire()
{
    qInfo("Fire!");
}


void Building::simPowerOut()
{
    qInfo("Power is out.");
}

void Building::initFloors(int numFloors)
{
//    for(int i = 0; i < numFloors; i++) {
//        Floor* floor = new Floor();
//        floors.append(floor);


//        qInfo("Created floor!");

//    }
}

void Building::update()
{
    qInfo("lol");

    for(Elevator* ele : elevators)
    {
        ele->update();
    }
}

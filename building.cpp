#include "building.h"
#include <QTimer>

Building::Building(int numFloors, int numElevators, QObject *parent)
    : QObject{parent}
{
    //initFloors(numFloors);

    for(int i = 0; i < numElevators; i++) {
        Elevator* ele = new Elevator();
        elevators.append(ele);
        connect(ele, &Elevator::floorSensed, this, &Building::eleArrived);
    }

    QTimer *timer = new QTimer(this);
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, this, &Building::update);

    timer->start();

    elevators[2]->moveToFloor(1);

}

void Building::simFire()
{
    qInfo("Fire!");
}

void Building::eleArrived(Elevator*,int floorNum)
{
    qInfo("Ele arrived");
    floors[floorNum]->setDoor(true, 2);
}


void Building::simPowerOut()
{
    qInfo("Power is out.");
}

//void Building::initFloors(int numFloors)
//{
//    for(int i = 0; i < numFloors; i++) {
//        Floor* floor = new Floor();
//        floors.append(floor);


//        qInfo("Created floor!");

//    }
//}

void Building::update()
{
    for(Elevator* ele : elevators)
    {
        ele->update();
    }
}

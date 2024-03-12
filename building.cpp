#include "building.h"
#include <QTimer>

Building::Building(int numFloors, int numElevators, QObject *parent)
    : QObject{parent}
{
    ecs = new ECS();
    initFloors(numFloors, numElevators);


    for(int i = 0; i < numElevators; i++) {
        Elevator* ele = new Elevator(i);
        elevators.append(ele);
        //connect(ele, &Elevator::floorSensed, this, &Building::eleArrived);
        connect(ele, &Elevator::floorSensed, ecs, &ECS::onFloorSensed);
    }

    ecs->elevators = elevators;
    ecs->floors = floors;

    QTimer *timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer, &QTimer::timeout, this, &Building::update);

    timer->start();

//    elevators[2]->moveToFloor(2);
//    elevators[1]->moveToFloor(4);
//    elevators[0]->moveToFloor(6);
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

void Building::initFloors(int numFloors, int numElevators)
{
    for(int i = 0; i < numFloors; i++) {
        Floor* floor = new Floor(i, numElevators);
        floors.append(floor);

        connect(floor, &Floor::eleRequested, ecs, &ECS::onEleRequest);
        qInfo("Created floor!");

    }
}

void Building::update()
{
    for(Elevator* ele : elevators)
    {
        ele->update();
    }
}

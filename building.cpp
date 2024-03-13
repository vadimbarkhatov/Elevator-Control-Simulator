#include "building.h"
#include <QTimer>

Building::Building(int numFloors, int numElevators, QObject *parent)
    : QObject{parent}
{
    ecs = new ECS();
    initFloors(numFloors, numElevators);


    for(int i = 0; i < numElevators; i++) {
        Elevator* ele = new Elevator(i, numFloors);
        elevators.append(ele);
        connect(ele, &Elevator::floorSensed, ecs, &ECS::onFloorSensed);
        connect(ele, &Elevator::doorsClosed, ecs, &ECS::onCloseDoors);
        connect(ele, &Elevator::floorSelected, ecs, &ECS::onFloorSelected);
    }

    ecs->elevators = elevators;
    ecs->floors = floors;

    QTimer *timer = new QTimer(this);
    timer->setInterval(500);
    connect(timer, &QTimer::timeout, this, &Building::update);

    timer->start();
}

void Building::simFire()
{
    qInfo("Fire!");
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

#include "building.h"
#include <QTimer>
#include <constants.h>

Building::Building(int numFloors, int numElevators, QObject *parent)
    : QObject{parent}
{
    ecs = new ECS();
    safetySystem = new SafetySystem();
    initFloors(numFloors, numElevators);

    //sets up the elevators and hooks them to the ECS/Safety system
    for(int i = 0; i < numElevators; i++) {
        Elevator* ele = new Elevator(i, numFloors);
        elevators.append(ele);
        connect(ele, &Elevator::floorSensed, ecs, &ECS::onFloorSensed);
        connect(ele, &Elevator::doorsClosed, ecs, &ECS::onCloseDoors);
        connect(ele, &Elevator::floorSelected, ecs, &ECS::onFloorSelected);
        connect(ele, &Elevator::helpRequested, safetySystem, &SafetySystem::helpRequest);
    }

    //ecs needs to reference the elevators/floors
    ecs->elevators = elevators;
    ecs->floors = floors;

    //runs the update method periodically to simulate pass of time
    QTimer *timer = new QTimer(this);
    timer->setInterval(Constants::refreshInterval);
    connect(timer, &QTimer::timeout, this, &Building::update);

    timer->start();
}

void Building::simFire()
{
    ecs->buildingFire();
    qInfo("Fire!");
}


void Building::simPowerOut()
{
    ecs->powerOut();
    qInfo("Power is out.");
}

//sets up the floors and hooks them to the ECS
void Building::initFloors(int numFloors, int numElevators)
{
    for(int i = 0; i < numFloors; i++) {
        Floor* floor = new Floor(i, numElevators);
        floors.append(floor);

        connect(floor, &Floor::eleRequested, ecs, &ECS::onEleRequest);
    }
}


//simulates time for the elevators
void Building::update()
{
    for(Elevator* ele : elevators)
    {
        ele->update();
    }

}

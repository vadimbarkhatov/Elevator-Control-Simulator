#include "building.h"

Building::Building(int numFloors, int elevators, QObject *parent)
    : QObject{parent}
{
    initFloors(numFloors);
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

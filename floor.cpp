#include "floor.h"
#include <QLoggingCategory>

Floor::Floor(int floorNumber, int numDoors, QObject *parent)
    : QObject{parent}, doors(numDoors)
{
    this->floorNumber = floorNumber;
    this->upButton = false;
    this->downButton = false;

    for(int i = 0; i < numDoors; i++) {
        doors[i] = false;
    }
}


void Floor::pressUp()
{
    //qInfo("Up Press! on floor ");
    qInfo() << QString("Up Press on floor %1").arg(floorNumber);

    upButton = !upButton;
    emit eleRequested(this, "up");

    //doors[1] = !doors[1];
    //emit doorsChanged(this);
}

void Floor::pressDown()
{
    //qInfo("Up Press! on floor ");
    qInfo() << QString("Down Press on floor %1").arg(floorNumber);
    downButton = !downButton;
    emit eleRequested(this, "down");
}

void Floor::setDoor(bool state, int doorNum)
{
    doors[doorNum] = state;
    emit doorsChanged(this);
}



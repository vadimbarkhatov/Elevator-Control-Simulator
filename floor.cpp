#include "floor.h"
#include <QLoggingCategory>

Floor::Floor(int floorNum, int numDoors, QObject *parent)
    : QObject{parent}, doors(numDoors)
{
    this->floorNum = floorNum;
    this->upButton = false;
    this->downButton = false;

    for(int i = 0; i < numDoors; i++) {
        doors[i] = false;
    }
}


void Floor::pressUp()
{
    if(!upButton) {
        upButton = true;
        qInfo().noquote() << QString("Up press on floor %1.").arg(floorNum);
        emit eleRequested(this, "up");
    }

}


void Floor::pressDown()
{
    if(!downButton) {
        downButton = true;
        qInfo().noquote() << QString("Down press on floor %1.").arg(floorNum);
        emit eleRequested(this, "down");
    }
}

void Floor::unselectUp()
{
    upButton = false;
    emit eleRequested(this, "none");
}

void Floor::unselectDown()
{
    downButton = false;
    emit eleRequested(this, "none");
}


void Floor::setDoor(bool state, int doorNum)
{
    doors[doorNum] = state;
    emit doorsChanged(this);
}



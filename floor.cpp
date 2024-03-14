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



//press up/down will only select the button and fire an ele request if it isn't already selected
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

//the unselect buttons fire a none requested signal so that the highlight display can be cleared
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

//when doors are changed, lets the display know when they have opened
void Floor::setDoor(bool state, int doorNum)
{
    doors[doorNum] = state;
    emit doorsChanged(this);
}



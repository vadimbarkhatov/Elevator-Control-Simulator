#include "elevator.h"
#include <cmath>
#include <QDebug>


Elevator::Elevator(int eleNum, int numFloors, QObject *parent)
    : QObject{parent}, eleNum(eleNum)
{
    state = Idle;

    for(int i = 0; i < numFloors; i++) {
        floorButtons.append(false);
    }
}


void Elevator::update()
{
    if(state == MovingUp) {
        position += speed;
        //qInfo() << QString("Elevator at %1").arg(position);
        //qInfo() << QString("Difference to lower floor at %1").arg(position - std::floor(position));

        if(position - std::floor(position) < speed) {
            emit floorSensed(this, static_cast<int>(std::round(position)));
        }
    }
    else if(state == MovingDown) {
        position -= speed;

        if(position - std::ceil(position) < speed) {
            emit floorSensed(this, static_cast<int>(std::round(position)));
        }
    }


    if(state == MovingUp || state == MovingDown) {
        qInfo() << QString("Elevator %1 at %2").arg(eleNum, position);
    }

    if(state == WaitDoorOpen) {
        doorOpenTime -= 0.5;
        if(doorOpenTime <= 0) {
            closeDoors();
        }
    }

}

void Elevator::openDoors(float time)
{
    state = WaitDoorOpen;

    doorOpenTime = time;
}

void Elevator::closeDoors()
{
    state = WaitDoorClosed;
    emit doorsClosed(this, getFloorNum());
}

void Elevator::selectFloor(int floorNum)
{
    floorButtons.replace(floorNum, true);
    emit floorSelect(this);
}

bool Elevator::moveToFloor(int floorNum)
{
    targetFloor = floorNum;

    if(position < floorNum) {
        state = MovingUp;
    }
    else if(position > floorNum) {
        state = MovingDown;
    }

    return true;
}

int Elevator::getFloorNum()
{
    return static_cast<int>(std::round(position));
}


int Elevator::stop()
{
    //state = Idle;

    position = std::round(position);

    return static_cast<int>(position);
}


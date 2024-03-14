#include "elevator.h"
#include <cmath>
#include <QDebug>
#include "constants.h"
#include <safetysystem.h>


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

        if(position - std::floor(position) < speed) {
            emit floorSensed(this, static_cast<int>(std::round(position)));
        }
    }
    else if(state == MovingDown) {
        position -= speed;
         //qInfo() << QString("Ele at %1").arg(position);

         //qInfo() << QString("Diff at %1").arg(std::ceil(position) - position);

        if(std::ceil(position) - position < speed) {
            emit floorSensed(this, static_cast<int>(std::round(position)));
        }
    }


    if(state == WaitDoorOpen) {
        doorOpenTime -= 1;
        if(doorOpenTime <= 0) {

            if(loadWeight > Constants::maxWeight) {
                qInfo("Elevator over weight limit. *WARNING! Over max load weight!");
                doorOpenTime = Constants::doorOpenTiming / 2;
            }
            else if(doorBlocked) {
                qInfo("Could not close door due to obstacle!");
                doorOpenTime = Constants::doorOpenTiming / 3;
                doorBlockedCounter++;
                if(doorBlockedCounter == Constants::doorBlockMax) {
                    qInfo("Elevator could not close doors after multiple attempts. *WARNING! Please clear the doors!*");
                    doorBlockedCounter = 0;
                }
            }
            else {
                doorBlockedCounter = 0;
                closeDoors();
            }

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
    if(floorNum != getFloorNum()) {
        floorButtons.replace(floorNum, true);
        emit floorSelected(this, floorNum);
    }

}

bool Elevator::moveToFloor(int floorNum)
{
    if(targetFloor == -1)
        targetFloor = floorNum;

    if(position < floorNum) {
        state = MovingUp;
    }
    else if(position > floorNum) {
        state = MovingDown;
    }

    return true;
}

void Elevator::holdCloseDoor()
{
    if(state == WaitDoorOpen) {
        doorOpenTime = 0;
    }

}

void Elevator::holdOpenDoor()
{
    if(state == WaitDoorOpen) {
        doorOpenTime = 5;
    }
}

int Elevator::getFloorNum()
{
    return static_cast<int>(std::round(position));
}

void Elevator::setDoorObstacle(int blockedState)
{
    if(blockedState == Qt::Checked) {
        qInfo("Elevator door blocked.");
        doorBlocked = true;
    }
    else if(blockedState != Qt::Checked && doorBlocked) {
         qInfo("Elevator door unblocked.");
        doorBlocked = false;
    }
}

void Elevator::setLoadWeight(const QString &weight)
{
    loadWeight = weight.toInt();
}


int Elevator::stop()
{
    position = std::round(position);

    return static_cast<int>(position);
}


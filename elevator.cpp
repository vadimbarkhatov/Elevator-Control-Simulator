#include "elevator.h"
#include <cmath>
#include <QDebug>
#include "constants.h"
#include <cstdlib>
#include <ctime>


Elevator::Elevator(int eleNum, int numFloors, QObject *parent)
    : QObject{parent}, eleNum(eleNum)
{
    state = Idle;

    for(int i = 0; i < numFloors; i++) {
        floorButtons.append(false);
    }

    srand(42); //fixed seed for testing
}

//how the elevator percieves time
void Elevator::update()
{

    //moves the elevator up/down and fires it's floor sensor if it has passed a floor positon
    if(state == MovingUp) {
        position += speed;

        if(position - std::floor(position) < speed) {
            emit floorSensed(this, static_cast<int>(std::round(position)));
        }
    }
    else if(state == MovingDown) {
        position -= speed;

        if(std::ceil(position) - position < speed) {
            emit floorSensed(this, static_cast<int>(std::round(position)));
        }
    }

    //counts down door open timer and does a few checks before it actually closes such as weight limit and door obstruction
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

    qInfo().noquote() << QString("Elevator %1 opened it's doors.").arg(eleNum);
    qInfo("*Bell ring*");
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

//sets the target floor if it doesn't already have an original and changes move state
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

//zeroes the door open countdown so door closes immediately on next update
void Elevator::holdCloseDoor()
{
    if(state == WaitDoorOpen) {
        doorOpenTime = 0;
    }
}


//resets the door open countdown
void Elevator::holdOpenDoor()
{
    if(state == WaitDoorOpen) {
        doorOpenTime = Constants::doorOpenTiming;
    }
}

//as position continous assume the current floor number is the nearest integer
int Elevator::getFloorNum()
{
    return static_cast<int>(std::round(position));
}

//blocks/unblocks the door
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

//fires when the help button is pressed is hooked up to safetystem by default
void Elevator::helpRequest()
{
    emit helpRequested(this);
}


//when safety system ask for a response, will simulate a response 50% of the time
bool Elevator::respondToSafety()
{
    if(rand() % 2 == 0) {
        return true; qInfo("true");
    }
    else {
        return false; qInfo("false");
    }
}

void Elevator::setLoadWeight(const QString &weight)
{
    loadWeight = weight.toInt();
}


//when elevator is ordered to stap, snaps it's position to the nearest floor
int Elevator::stop()
{
    position = std::round(position);

    return static_cast<int>(position);
}


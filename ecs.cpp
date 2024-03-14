#include "ecs.h"
#include <QDebug>
#include "constants.h"
#include <cfloat>

ECS::ECS(QObject *parent)
    : QObject{parent}
{

}

void ECS::buildingFire()
{
    state = Fire;
    emergencyProtocol();
}

void ECS::powerOut()
{
    state = PowerOut;
    emergencyProtocol();
}

void ECS::emergencyProtocol()
{
    for(Elevator* ele : elevators) {
        if(ele->getFloorNum() == Constants::safeFloor)
            stopElevator(ele);
        else
            ele->moveToFloor(Constants::safeFloor);

        qInfo().noquote() << QString("Elevator %1 displays message: *There is an emergency in the building. Please disembark upon reaching the safe floor*").arg(ele->eleNum);
    }

    for(Floor* floor : floors) {
        floor->unselectDown();
        floor->unselectUp();
    }
}

void ECS::stopElevator(Elevator *ele)
{
    ele->stop();

    if(ele->getFloorNum() == Constants::safeFloor && (state == Fire || state == PowerOut)) {
        ele->openDoors(FLT_MAX);
        ele->targetFloor = -1;
        floors[ele->getFloorNum()]->setDoor(true, ele->eleNum);

        return;
    }

    ele->openDoors(Constants::doorOpenTiming);
    floors[ele->getFloorNum()]->setDoor(true, ele->eleNum);
    if(ele->targetFloor == ele->getFloorNum()) ele->targetFloor = -1;


}

void ECS::onEleRequest(Floor* floor, std::string direction)
{
    //qInfo().noquote() << QString("Elevator request at %1").arg(floor->floorNum);

    if(direction == "down" || direction == "up"){
        for(Elevator* ele : elevators) {

            if(ele->state == ele->Idle) {
                if(ele->getFloorNum() == floor->floorNum) {
                    stopElevator(ele);

                    if(direction == "down")
                        floor->unselectDown();
                    else
                        floor->unselectUp();
                }
                else
                    ele->moveToFloor(floor->floorNum);

                break;
            }
        }
     }

}

void ECS::onCloseDoors(Elevator* ele, int floorNum)
{
    floors[floorNum]->setDoor(false, ele->eleNum);

    for(int i = 0; i < ele->floorButtons.count(); i++) {

        if(ele->floorButtons[i]) {
            ele->moveToFloor(i);
            break;
        }

        if(i == ele->floorButtons.count() - 1) {
            if(ele->targetFloor > -1)
                ele->moveToFloor(ele->targetFloor);
            else
                ele->state = ele->Idle;
        }
    }
}


void ECS::onFloorSensed(Elevator* ele, int floorNum)
{
    //qInfo().noquote() << QString("Got signal that elevator %1 arrived at floor %2.").arg(ele->eleNum).arg(floorNum);

    if(ele->getFloorNum() == Constants::safeFloor && (state == Fire || state == PowerOut)) {
        stopElevator(ele);
    }

    if(floors[floorNum]->upButton && ele->state == ele->MovingUp) {
        floors[floorNum]->unselectUp();
        stopElevator(ele);

    }
    else if(floors[floorNum]->downButton && ele->state == ele->MovingDown) {
        floors[floorNum]->unselectDown();
        stopElevator(ele);
    }
    else if(ele->targetFloor == floorNum) {
        if(ele->state == ele->MovingDown)
            floors[floorNum]->unselectUp();
        else if(ele->state == ele->MovingUp)
            floors[floorNum]->unselectDown();

        stopElevator(ele);
    }

    if(ele->floorButtons[floorNum]) {
        ele->floorButtons[floorNum] = false;
        stopElevator(ele);
    }
}

void ECS::onFloorSelected(Elevator *ele, int floorNum)
{
    if(ele->state == ele->Idle) {
        ele->moveToFloor(floorNum);
    }
}



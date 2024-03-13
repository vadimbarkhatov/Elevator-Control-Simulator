#include "ecs.h"
#include <QDebug>

ECS::ECS(QObject *parent)
    : QObject{parent}
{

}

void ECS::stopElevator(Elevator *ele)
{
    ele->stop();
    ele->openDoors(5);
    floors[ele->getFloorNum()]->setDoor(true, ele->eleNum);
    if(ele->targetFloor == ele->getFloorNum()) ele->targetFloor = -1;
}

void ECS::onEleRequest(Floor* floor, std::string direction)
{
    qInfo() << QString("Elevator request at %1").arg(floor->floorNum);

    if(direction == "down" || direction == "up"){
        for(Elevator* ele : elevators) {

            if(ele->state == ele->Idle) {
                //if(ele->floorNumber)
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
    qInfo() << QString("Got signal that ele arrived at %1").arg(floorNum);


    if(ele->floorButtons[floorNum]) {
        ele->floorButtons[floorNum] = false;
        emit ele->floorSelect(ele);
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
}

void ECS::onFloorSelected(Elevator *ele)
{

}

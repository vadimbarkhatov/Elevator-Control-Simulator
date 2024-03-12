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
}

void ECS::onEleRequest(Floor* floor, std::string direction)
{
    qInfo() << QString("Elevator request at %1").arg(floor->floorNumber);

    //elevators[1]->moveToFloor(floor->floorNumber);
    if(direction == "down" || direction == "up"){
        for(Elevator* ele : elevators) {
            //ele->update();

//            if(direction == "up" && ele->MovingUp && ele->getFloorNum() < floor->floorNumber) {

//            }
            if(ele->state == ele->Idle) {
                ele->moveToFloor(floor->floorNumber);
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
            ele->state = ele->Idle;
        }
    }
}

void ECS::onFloorSensed(Elevator* ele, int floorNum)
{
    qInfo() << QString("Got signal that ele arrived at %1").arg(floorNum);


    if(ele->floorButtons[floorNum]) {
        stopElevator(ele);
    }

    if(floors[floorNum]->upButton && ele->MovingUp) {
        floors[floorNum]->unselectUp();

        stopElevator(ele);
    }
    else if(floors[floorNum]->downButton && ele->MovingDown) {
        floors[floorNum]->unselectDown();

        stopElevator(ele);
    }
//    else if() {

//    }
}

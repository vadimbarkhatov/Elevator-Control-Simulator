#include "ecs.h"
#include <QDebug>

ECS::ECS(QObject *parent)
    : QObject{parent}
{

}

void ECS::onEleRequest(Floor* floor, std::string direction)
{
    qInfo() << QString("Elevator request at %1").arg(floor->floorNumber);

    //elevators[1]->moveToFloor(floor->floorNumber);
    if(direction == "down" || direction == "up"){
        for(Elevator* ele : elevators) {
            //ele->update();
            if(ele->state == ele->Idle) {
                ele->moveToFloor(floor->floorNumber);
                break;
            }
        }
     }
}



void ECS::onFloorSensed(Elevator* ele, int floorNum)
{
    qInfo() << QString("Got signal that ele arrived at %1").arg(floorNum);

    if(ele->targetFloor == floorNum) {

        if(ele->state == ele->MovingUp) {
            floors[floorNum]->unselectUp();
        }
        else if(ele->state == ele->MovingDown) {
            floors[floorNum]->unselectDown();
        }

        ele->stop();

        floors[floorNum]->setDoor(true, ele->eleNum);
    }

}

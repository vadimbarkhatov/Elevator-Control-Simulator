#include "ecs.h"
#include <QDebug>

ECS::ECS(QObject *parent)
    : QObject{parent}
{

}

void ECS::onEleRequest(Floor *)
{

}

void ECS::onFloorSensed(Elevator * ele, int floorNum)
{
    qInfo() << QString("Got signal that ele arrived at %1").arg(floorNum);

    if(ele->targetFloor == floorNum) {
        ele->stop();
        floors[floorNum]->setDoor(true, ele->eleNum);
    }

}

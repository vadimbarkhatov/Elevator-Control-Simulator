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

//both the Fire and PowerOut states behave the same way so one emergency function is used for both
void ECS::emergencyProtocol()
{
    //every elevator is sent to a predefined safe floor unless they are already there
    for(Elevator* ele : elevators) {
        if(ele->getFloorNum() == Constants::safeFloor)
            stopElevator(ele);
        else
            ele->moveToFloor(Constants::safeFloor);

        qInfo().noquote() << QString("Elevator %1 displays message: *There is an emergency in the building. Please disembark upon reaching the safe floor*").arg(ele->eleNum);
    }

    //resets any selected requests for all floors
    for(Floor* floor : floors) {
        floor->unselectDown();
        floor->unselectUp();
    }
}

//stops the elevator and opens the door and unselects the floor panel
void ECS::stopElevator(Elevator *ele)
{
    ele->stop();

    //overrides behavior so elevator do not move around during emergency
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

//when floor panel button is pressed ECS sends the first available Idle elevator
void ECS::onEleRequest(Floor* floor, std::string direction)
{
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

//onces the elevator closes it's doors the ecs decides what do with it
void ECS::onCloseDoors(Elevator* ele, int floorNum)
{
    floors[floorNum]->setDoor(false, ele->eleNum);

    for(int i = 0; i < ele->floorButtons.count(); i++) {

        //sends elevator to the first available selected floor
        if(ele->floorButtons[i]) {
            ele->moveToFloor(i);
            break;
        }

        //if none of the floor buttons are selected moves the elevator to it's target floor
        if(i == ele->floorButtons.count() - 1) {
            if(ele->targetFloor > -1)
                ele->moveToFloor(ele->targetFloor);
            else
                ele->state = ele->Idle;
        }
    }
}

//fires every time the elevator arrives at a floor letting the ecs decide on how to route it
void ECS::onFloorSensed(Elevator* ele, int floorNum)
{
    //stops if it reaches safe floor in an emergency
    if(ele->getFloorNum() == Constants::safeFloor && (state == Fire || state == PowerOut)) {
        stopElevator(ele);
    }

    //stops the elevator if it's moving up/down and if the floor it's passing by has the up/down buttons selected
    if(floors[floorNum]->upButton && ele->state == ele->MovingUp) {
        floors[floorNum]->unselectUp();
        stopElevator(ele);

    }
    else if(floors[floorNum]->downButton && ele->state == ele->MovingDown) {
        floors[floorNum]->unselectDown();
        stopElevator(ele);
    } //stops the elevator if it reaches it's target floor
    else if(ele->targetFloor == floorNum) {
        if(ele->state == ele->MovingDown)
            floors[floorNum]->unselectUp();
        else if(ele->state == ele->MovingUp)
            floors[floorNum]->unselectDown();

        stopElevator(ele);
    }

    //stops the elevator if it reaches a floor that is one of it's selected floor buttons
    if(ele->floorButtons[floorNum]) {
        ele->floorButtons[floorNum] = false;
        stopElevator(ele);
    }
}

void ECS::onFloorSelected(Elevator *ele, int floorNum)
{
    //if the elevator is idle send it to the floor that had it's floor button selected
    if(ele->state == ele->Idle) {
        ele->moveToFloor(floorNum);
    }
}



#include "elevator.h"
#include <cmath>
#include <QDebug>


Elevator::Elevator(QObject *parent)
    : QObject{parent}
{
    state = Idle;
}

void Elevator::update()
{


    if(state == MovingUp) {
        position += speed;
        qInfo() << QString("Elevator at %1").arg(position);

        if(static_cast<int>(std::floor(position)) == targetFloor) {
            qInfo() << QString("ele arrived");
        }
    }



    //if(state == MovingUp || state == MovingDown) {
        //if(position targetFloor)
    //}

    //if(targetFloor )
}

bool Elevator::moveToFloor(int floorNum)
{
    targetFloor = floorNum;

    if(position < floorNum) {
        state = MovingUp;
    }




    return true;
}


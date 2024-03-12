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
        qInfo() << QString("Difference to lower floor at %1").arg(position - std::floor(position));

        if(position - std::floor(position) < speed) {
            //qInfo() << QString("ele arrived");
            emit floorSensed(this, static_cast<int>(std::round(position)));
            //emit floorSensed(this);
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


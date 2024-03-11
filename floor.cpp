#include "floor.h"
#include <QLoggingCategory>

Floor::Floor(int floorNumber, QObject *parent)
    : QObject{parent}
{
    this->floorNumber = floorNumber;
    this->upButton = false;
    this->downButton = false;
}


void Floor::pressUp()
{
    //qInfo("Up Press! on floor ");
    qInfo() << QString("Up Press on floor %1").arg(floorNumber);

    upButton = !upButton;
    emit eleRequested(this);
}

void Floor::pressDown()
{
    //qInfo("Up Press! on floor ");
    qInfo() << QString("Down Press on floor %1").arg(floorNumber);
    downButton = !downButton;
    emit eleRequested(this);
}

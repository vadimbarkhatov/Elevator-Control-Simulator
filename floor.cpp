#include "floor.h"

Floor::Floor(int floorNumber, QObject *parent)
    : QObject{parent}
{
    this->floorNumber = floorNumber;
}


void Floor::pressUp()
{
    qInfo("Up Press!");
}

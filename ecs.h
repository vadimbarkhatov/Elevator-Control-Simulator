#ifndef ECS_H
#define ECS_H

#include <QObject>
#include <floor.h>

class ECS : public QObject
{
    Q_OBJECT
public:
    explicit ECS(QObject *parent = nullptr);


private:
//    - buildingFire: bool
//    - powerOutage: bool

public:
//    + buildingFire(): void
//    + powerOut(): void
//    + onEleRequest(Floor*, string): void
//    + onFloorSensed(Elevator*, int): void
//    + onOpenDoors(Elevator*): void
//    + onCloseDoors(Elevator*): void
//    + onEleFire(Elevator*): void
//    + onEleOverload(Elevator*): void
//    + onHelpRequest(Elevator*): void

public slots:
    void onEleRequest(Floor*);
    void onFloorSensed(Elevator*, int);

signals:

};

#endif // ECS_H

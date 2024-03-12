#ifndef ECS_H
#define ECS_H

#include <QObject>
#include <floor.h>

class ECS : public QObject
{
    Q_OBJECT
public:
    explicit ECS(QObject *parent = nullptr);


public:
//    - buildingFire: bool
//    - powerOutage: bool
    QVector<Elevator*> elevators;
    QVector<Floor*> floors;

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

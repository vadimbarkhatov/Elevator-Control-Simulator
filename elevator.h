#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
//#include <floor.h>

class Elevator : public QObject
{
    Q_OBJECT
public:
    explicit Elevator(int eleNum, QObject *parent = nullptr);
    enum EleState {Idle, Waiting, MovingUp, MovingDown};
    EleState state = Idle;
//    + floorButtons: bool []
    float position = 0.0f;
    int targetFloor = 0;
    int eleNum = 0;
//    + targetFloor: int
//    + display: string
//    + floorSensed: signal<void (Elevator*, int)>
//    + internalFire: signal<void (Elevator*)>
//    + floorSelect: signal<void (Elevator*)>
//    + ready: signal<void (Elevator*)>
//    + helpRequest: signal<void (Elevator*)>
//    + overload: signal<void (Elevator*)>
//    + displayUpdate: signal<void (Elevator*)>
//    + speakerSound: signal<void (string)>
//    + bellRing: signal<void ()>
//    + doorObstacle: bool
//    - doorBlockedCounter: int
//    - doorOpenTime: float
//    - speed: const float
//    - openDoorsTimer: float
//    - loadWeight: float

private:
    float speed = 0.1f;

signals:
    void floorSensed(Elevator*, int);
    //void floorSensed(Elevator*);


public:
    void update();
//    + selectFloor(int): void
    bool moveToFloor(int);
//    + openDoors(float): void
//    + closeDoors(): void
//    + holdCloseDoor():void
//    + holdOpenDoor(): void
//    + requestResponse(): void
//    + callHelp(): void
//    + simOverload(): void
//    + simEleFire(): void
//    + addDoorObstacle():void
//    + removeDoorObstacle():void
//    + buildingFire():void
//    + powerOut():void
//    + onEleRequest(Floor*, string):void
//    - emitSound(string):void



    int stop();
signals:

};

#endif // ELEVATOR_H

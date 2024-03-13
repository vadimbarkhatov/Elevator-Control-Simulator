#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
//#include <floor.h>

class Elevator : public QObject
{
    Q_OBJECT
public:
    explicit Elevator(int eleNum, int numFloors, QObject *parent = nullptr);
    enum EleState {Idle, WaitDoorOpen, WaitDoorClosed, MovingUp, MovingDown};
    EleState state = Idle;

    float position = 0.0f;
    int targetFloor = -1;
    int eleNum = 0;
    QVector<bool> floorButtons;
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
    float speed = 0.2f;
    float doorOpenTime = 0.0f;

signals:
    void floorSensed(Elevator*, int);
    void doorsClosed(Elevator*, int);
    void floorSelected(Elevator*, int);
    void eleMoved(Elevator*);


public slots:
    void holdCloseDoor();
    void holdOpenDoor();

public:
    void update();
    bool moveToFloor(int);

//    + requestResponse(): void
//    + callHelp(): void
//    + simOverload(): void
//    + simEleFire(): void
//    + addDoorObstacle():void
//    + removeDoorObstacle():void
//    + buildingFire():void
//    + powerOut():void
//    - emitSound(string):void



    int stop();
    void openDoors(float time);
    void closeDoors();
    void selectFloor(int floorNum);
    int getFloorNum();
signals:

};

#endif // ELEVATOR_H

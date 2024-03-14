#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>


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
    bool doorBlocked = false;
    int loadWeight = 0;

private:
    float speed = 0.2f; //this is the fraction of the distance between floors the elevator will move in one update interval
    float doorOpenTime = 0.0f;
    int doorBlockedCounter = 0;


signals:
    void floorSensed(Elevator*, int);
    void doorsClosed(Elevator*, int);
    void floorSelected(Elevator*, int);
    void helpRequested(Elevator*);


public slots:
    void holdCloseDoor();
    void holdOpenDoor();
    void setDoorObstacle(int);
    void helpRequest();
    void setLoadWeight(const QString&);

public:
    void update();
    bool moveToFloor(int);
    int stop();
    void openDoors(float);
    void closeDoors();
    void selectFloor(int);
    int getFloorNum();
    bool respondToSafety();
signals:

};

#endif // ELEVATOR_H

#ifndef FLOOR_H
#define FLOOR_H

#include <QObject>
#include <elevator.h>


class Floor : public QObject
{
    Q_OBJECT


public:
    explicit Floor(int floorNumber, int numDoors, QObject *parent = nullptr);

signals:
    void upButtonChanged();
    void eleRequested(Floor* self, std::string direction);
    //void eleRequested(Floor* self);
    void doorsChanged(Floor* self);

public slots:
    void pressUp();
    void pressDown();

public:
    int floorNumber;
    bool upButton;
    bool downButton;
    QVector<bool> doors;
    void eleArrived(Elevator*, int floorNum);


    void setDoor(bool state, int doorNum);

};

#endif // FLOOR_H

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
    void eleRequested(Floor*, std::string);
    void doorsChanged(Floor*);

public slots:
    void pressUp();
    void pressDown();

public:
    int floorNum;
    bool upButton;
    bool downButton;
    QVector<bool> doors;

    void eleArrived(Elevator*, int);
    void setDoor(bool, int);
    void unselectUp();
    void unselectDown();
};

#endif // FLOOR_H

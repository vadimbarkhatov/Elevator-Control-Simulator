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
    enum ECSState {Clear, Fire, PowerOut};
    ECSState state = Clear;
    QVector<Elevator*> elevators;
    QVector<Floor*> floors;

public:
      void buildingFire();
      void powerOut();

private:
    void stopElevator(Elevator *ele);
    void emergencyProtocol();

public slots:
    void onEleRequest(Floor* floor, std::string direction);
    void onFloorSensed(Elevator*, int);
    void onFloorSelected(Elevator* ele, int);
    void onCloseDoors(Elevator*ele, int floorNum);


signals:

private slots:

};

#endif // ECS_H

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
    QVector<Elevator*> elevators;
    QVector<Floor*> floors;

public:
      void buildingFire();
      void powerOut();

private:
    void stopElevator(Elevator*);
    void emergencyProtocol();
    enum ECSState {Clear, Fire, PowerOut};
    ECSState state = Clear;

public slots:
    void onEleRequest(Floor*, std::string direction);
    void onFloorSensed(Elevator*, int);
    void onFloorSelected(Elevator*, int);
    void onCloseDoors(Elevator*, int);


signals:

private slots:

};

#endif // ECS_H

#ifndef BUILDING_H
#define BUILDING_H

#include <QObject>
#include <QVector>
#include <floor.h>
#include <elevator.h>
#include <ecs.h>
#include <safetysystem.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Building : public QObject
{
    Q_OBJECT
public:
    explicit Building(int floors, int elevators, QObject *parent = nullptr);
    QVector<Floor*> floors;
    QVector<Elevator*> elevators;
    SafetySystem* safetySystem;

signals:

public slots:
    void simFire();
    void simPowerOut();

private slots:
    void update();

private:
    ECS* ecs;
    void initFloors(int numFloors, int numElevators);


};

#endif // BUILDING_H

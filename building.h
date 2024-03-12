#ifndef BUILDING_H
#define BUILDING_H

#include <QObject>
#include <QVector>
#include <floor.h>
#include <elevator.h>
#include <ecs.h>

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

signals:

public slots:
    void simFire();
    void simPowerOut();
    void eleArrived(Elevator*, int floorNum);

private slots:
    void update();

private:
    //Ui::MainWindow *ui;

    void initFloors(int numFloors);


};

#endif // BUILDING_H

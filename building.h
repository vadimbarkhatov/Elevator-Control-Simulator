#ifndef BUILDING_H
#define BUILDING_H

#include <QObject>
#include <QVector>
#include <floor.h>

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

signals:

public slots:
    void simFire();
    void simPowerOut();

private:
    Ui::MainWindow *ui;

    void initFloors(int numFloors);

};

#endif // BUILDING_H

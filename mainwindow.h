#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "building.h"
#include "elevator.h"
#include "floor.h"
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    Building* building;
    QVector<QPushButton*> upButtons;
    QVector<QPushButton*> downButtons;
    Elevator* selEle = nullptr;
    int floorUISize = 50;

    void connectEleToPanel(Elevator*, Ui::MainWindow*);
    void setupFloorDisplay();
    void setupFloorDoorDisplay(int, int, int, Floor*);
private slots:
    void setupElevatorDisplay();
    void onFloorSelected(int);
    void onFloorSensed();
};
#endif // MAINWINDOW_H

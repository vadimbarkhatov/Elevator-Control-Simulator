#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>

class Elevator : public QObject
{
    Q_OBJECT
public:
    explicit Elevator(QObject *parent = nullptr);

signals:

};

#endif // ELEVATOR_H

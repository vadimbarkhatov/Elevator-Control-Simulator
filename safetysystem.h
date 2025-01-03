#ifndef SAFETYSYSTEM_H
#define SAFETYSYSTEM_H

#include <QObject>
#include <elevator.h>
#include <QDebug>

class SafetySystem : public QObject
{
    Q_OBJECT
public:
    explicit SafetySystem(QObject *parent = nullptr);

public slots:
    void helpRequest(Elevator*);

private:
    void call911();
    bool callSecurity();

signals:

};

#endif // SAFETYSYSTEM_H

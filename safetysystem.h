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
    void update();

public slots:
    void helpRequest(Elevator*);


private:
    float responseTimer = 0.0f;
    void call911();

signals:

};

#endif // SAFETYSYSTEM_H

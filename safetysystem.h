#ifndef SAFETYSYSTEM_H
#define SAFETYSYSTEM_H

#include <QObject>
#include <elevator.h>

class SafetySystem : public QObject
{
    Q_OBJECT
public:
    explicit SafetySystem(QObject *parent = nullptr);



private:
    float responseTimer = 0.0f;

signals:

};

#endif // SAFETYSYSTEM_H

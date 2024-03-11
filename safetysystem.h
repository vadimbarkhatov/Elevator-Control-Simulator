#ifndef SAFETYSYSTEM_H
#define SAFETYSYSTEM_H

#include <QObject>

class SafetySystem : public QObject
{
    Q_OBJECT
public:
    explicit SafetySystem(QObject *parent = nullptr);

signals:

};

#endif // SAFETYSYSTEM_H

#ifndef FLOOR_H
#define FLOOR_H

#include <QObject>

class Floor : public QObject
{
    Q_OBJECT


public:
    explicit Floor(int floorNumber, QObject *parent = nullptr);

signals:
    void upButtonChanged();
    void eleRequested(Floor* self);

public slots:
    void pressUp();
    void pressDown();

public:
    int floorNumber;
    bool upButton;
    bool downButton;


};

#endif // FLOOR_H

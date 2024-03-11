#ifndef FLOOR_H
#define FLOOR_H

#include <QObject>

class Floor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool upButton READ upButton WRITE setUpButton NOTIFY upButtonChanged)


public:
    explicit Floor(QObject *parent = nullptr);

signals:
    void upButtonChanged();

public:
    int floorNumber;
    bool upButton() const { return m_upButton; };
    void setUpButton(bool value) {
        if (m_upButton == value) return;
        m_upButton = value;
        emit upButtonChanged();
    }

    bool downButton;

    void pressUp();
    void pressDown();

private:
    bool m_upButton;

};

#endif // FLOOR_H

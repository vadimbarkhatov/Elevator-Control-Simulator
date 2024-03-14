#include "safetysystem.h"
#include <constants.h>
#include <cstdlib>
#include <ctime>
#include <QTimer>

SafetySystem::SafetySystem(QObject *parent)
    : QObject{parent}
{
    srand(42); //fixed seed for testing
}


void SafetySystem::helpRequest(Elevator* ele)
{
    qInfo().noquote() << QString("Safety system recieved help request from elevator %1.").arg(ele->eleNum);

    QTimer::singleShot(Constants::maxResponseTime * 1000, this, [this, ele]() {

        //either of these only have a 50% chance to respond
        bool eleResponded = ele->respondToSafety();
        bool securityResponded = callSecurity();

        if(!eleResponded || !securityResponded) {
            qInfo("Did not recieve a response in time from both the elevator and security!");
            call911();
        }
        else {
            qInfo("Safety system recieved a response from the elevator passengers and security in time!");
        }

    });
}


void SafetySystem::call911()
{
    qInfo().noquote() << QString("Calling 911!");
}

bool SafetySystem::callSecurity()
{
    if(rand() % 2 == 0) {
        return true;
    }
    else {
        return false;
    }
}

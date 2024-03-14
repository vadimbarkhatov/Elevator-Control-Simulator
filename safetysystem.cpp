#include "safetysystem.h"
#include <constants.h>
#include <cstdlib>
#include <ctime>

SafetySystem::SafetySystem(QObject *parent)
    : QObject{parent}
{
    srand(42); //fixed seed for testing
}

void SafetySystem::update()
{
    if(responseTimer > 0) {
        responseTimer -= 1.0f;

        if(responseTimer <= 0) {
            bool eleResponded = rand() % 2 == 0; //simulates elevator not responding half the time
            bool securityResponded = callSecurity();

            if(!eleResponded || !securityResponded) {
                qInfo("Did not recieve a response in time from both the elevator and security!");
                call911();
            }

        }
    }
}

void SafetySystem::helpRequest(Elevator* ele)
{
    responseTimer = Constants::maxResponseTime;
    qInfo().noquote() << QString("Safety system recieved help request from elevator %1.").arg(ele->eleNum);
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

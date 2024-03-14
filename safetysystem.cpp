#include "safetysystem.h"
#include <constants.h>

SafetySystem::SafetySystem(QObject *parent)
    : QObject{parent}
{

}

void SafetySystem::helpRequest(Elevator* ele)
{
    responseTimer = Constants::maxResponseTime;
    qInfo().noquote() << QString("Safety system recieved help request from elevator %1").arg(ele->eleNum);
}

void SafetySystem::call911()
{
    qInfo().noquote() << QString("Safety system did not recieve response in time calling 911!");
}

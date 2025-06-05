#ifndef SURVEILLANCETEMPERATUREIOT_H
#define SURVEILLANCETEMPERATUREIOT_H

#include "../include/Camera.h"
#include "../include/SeuilsIOT.h"
#include "../include/Apprentissage.h"
#include "../include/MQTT.h"

class SurveillanceTemperatureIOT
{

private:
    
public:
Camera *laCamera;
SeuilsIOT *currentSeuils;
Apprentissage *apprentissage;
MQTTClient *laCommunication;

SurveillanceTemperatureIOT(Apprentissage apprentissage, MQTTClient laCommunication);
void surveiller();
thread startSurveillance();
void lireDate();

};

#endif
#include <iostream>
#include "../include/SurveillanceTemperatureIOT.h"
#include "../include/Camera.h"
#include "../include/SeuilsIOT.h"
#include "../include/Apprentissage.h"
#include "../include/MQTT.h"

using namespace std;

SurveillanceTemperatureIOT::SurveillanceTemperatureIOT(Apprentissage apprentissage, MQTTClient laCommunication)
{
    
}

void SurveillanceTemperatureIOT::surveiller(){

    float tempMoy = laCamera->obtenirTempMoy();
    float tempMax = laCamera->obtenirTempMax();

    float seuilTempMoy = currentSeuils->getTempMoy();
    float seuilTempMax = currentSeuils->getTempMax();

    if (tempMoy > seuilTempMoy || tempMax > seuilTempMax) {
        laCamera->capturer_Image();
    }
}

thread SurveillanceTemperatureIOT::startSurveillance(){
    return thread(surveiller);
}

void lireDate(){


}
#include "../include/SeuilsIOT.h"

SeuilsIOT::SeuilsIOT()
{
    this->seuilTempMax=0;
    this->seuilTempMoy=0;
    this->seuilAxeX=0;
    this->seuilAxeY=0; 
    this->seuilAxeZ=0;
}

void SeuilsIOT::setSeuils_temperature(float valMoy, float valMax)
{
    this->seuilTempMax=valMax;
    this->seuilTempMoy=valMoy; 
}

float SeuilsIOT::getTempMax()
{
    return seuilTempMax;
}

float SeuilsIOT::getTempMoy()
{
    return seuilTempMoy;
}









/*
void SeuilsIOT::setSeuils_vibrations(float seuilAxeX, float seuilAxeY, float seuilAxeZ)
{
    seuilAxeX=seuilAxeX;
    seuilAxeY=seuilAxeY; 
    seuilAxeZ=seuilAxeZ; 
}

float SeuilsIOT::getSeuilAlertVibX()()
{
    return seuilAxeX;
}

float SeuilsIOT::getSeuilAlertVibY()()
{
    return seuilAxeY;
}

float SeuilsIOT::getSeuilAlertVibXZ)()
{
    return seuilAxeZ;
}
*/
SeuilsIOT::~SeuilsIOT()
{
    //destructeur
}

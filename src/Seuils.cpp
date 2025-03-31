#include "../include/Seuils.h"

Seuils::Seuils()
{
    this->base=new Base();
    this->seuilTempMax=0;
    this->seuilTempMoy=0;

}

void Seuils::setSeuils_temperature(float valMoy, float valMax, int idMachine)
{
    this->seuilTempMax=valMax;
    this->seuilTempMoy=valMoy; 
    base->ajouterSeuilTemp(seuilTempMax,seuilTempMoy,1); 
}

float Seuils::getTempMax()
{
    return seuilTempMax;
}

float Seuils::getTempMoy()
{
    return seuilTempMoy;
}

Seuils::~Seuils()
{
    //destructeur
}

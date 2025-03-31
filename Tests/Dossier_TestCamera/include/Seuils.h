#ifndef SEUILS_H
#define SEUILS_H

#include "bdd.h"

class Seuils 
{
private:
    Base * base;
    float seuilTempMax, seuilTempMoy;
public:
    Seuils();
    ~Seuils();
    void setSeuils_temperature(float valMoy, float valMax, int idMachine);
    float getTempMax();
    float getTempMoy();
    
    
};
#endif

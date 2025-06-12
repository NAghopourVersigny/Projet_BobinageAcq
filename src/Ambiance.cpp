#include "../include/Ambiance.h"

Ambiance::Ambiance()
{
    this->temp = 23.5;
    this->humidite = 53;
    this->dateheure = "2025-06-10 09:45:33";
}

void Ambiance::acquerirAmbiance()
{
    this->temp = temp;
    this->humidite = humidite;
    this->dateheure = dateheure; 
}

void enregistrerAmbiance(string dateheure)
{
    
}

float Ambiance::getTempAmb()
{
    return temp;
}

float Ambiance::getHumidite()
{
    return humidite;
}


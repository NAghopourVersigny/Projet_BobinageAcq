#include "../include/Contexte.h"

Contexte::Contexte(float tempAmb, float humidite, float tension_reseau, string dateheure)
{
    this->tempAmb = tempAmb;
    this->humidite = humidite;
    this->dateheure = dateheure;
}
Contexte::Contexte()
{
}

float Contexte::getTempAmb()
{
    return tempAmb;
}

float Contexte::getHumidite()
{
    return humidite;
}

string Contexte::getDateHeure()
{
    return dateheure;
}

int Contexte::obtenirContexte()
{
    this->tempAmb = 23.5;
    this->humidite = 53;
    this->dateheure = "";    

    return 0;
}
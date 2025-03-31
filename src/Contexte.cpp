#include "../include/Contexte.h"

Contexte::Contexte(float tempAmb, float humidite, float tension_reseau, string dateheure)
{
    this->tempAmb = tempAmb;
    this->humidite = humidite;
    this->tension_reseau = tension_reseau;
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

float Contexte::getTensionReseau()
{
    return tension_reseau;
}

string Contexte::getDateHeure()
{
    return dateheure;
}

int Contexte::obtenirContexte()
{
    this->tempAmb = 23.5;
    this->humidite = 53;
    this->tension_reseau = 230;
    this->dateheure = "";    

}
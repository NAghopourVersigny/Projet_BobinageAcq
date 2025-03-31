#include "../include/Temperature.h"

Temperature::Temperature(float valeur, string dateheure)
{
    this->valeur = valeur;
    this->dateheure = dateheure;
}

float Temperature::getValeur()
{
    return valeur;
}

string Temperature::getDateHeure()
{
    return dateheure;
}
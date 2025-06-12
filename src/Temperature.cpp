#include "../include/Temperature.h"

Temperature::Temperature()
{
    this->moyenne = 66;
    this->maximale = 98;
    this->dateheure = "2025-06-10 09:27:59";
}

Temperature::Temperature(float moyenne, float maximale, string dateheure)
{
    this->moyenne = moyenne;
    this->maximale = maximale;
    this->dateheure = dateheure;
}

string Temperature::getDateHeure()   
{
    return dateheure;
}

float Temperature::getMoyenne()
{
    return moyenne;
}

float Temperature::getMaximale()
{
    return maximale;
}

void Temperature::setDateHeure(string dateheure)
{
    this->dateheure = dateheure;
}  

void Temperature::setMoyenne(float moyenne)
{
    this->moyenne = moyenne;
}

void Temperature::setMaximale(float maximale)
{
    this->maximale = maximale;
}
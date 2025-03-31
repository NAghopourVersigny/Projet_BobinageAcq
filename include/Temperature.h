#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include <string>
#include <iostream>

using namespace std;

class Temperature
{
private:
    float valeur;
    string dateheure;

public:
    Temperature(float valeur, string dateheure);
    float getValeur();
    string getDateHeure();
};

#endif

#ifndef CONTEXTE_H
#define CONTEXTE_H

#include <string>
#include <iostream>

using namespace std;

class Contexte
{
private:
    float tempAmb;
    float humidite;
    string dateheure;

public:
    Contexte(float tempAmb, float humidite, string dateheure);
    Contexte();
    int obtenirContexte();
    float getTempAmb();
    float getHumidite();
    string getDateHeure();
};

#endif
#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include "../include/Temperature.h"
#include "../include/Vibration.h"
#include <string>
#include <iostream>
#include <list>

using namespace std;

class Historique_Sem
{
    

private:
    list<Temperature> historiqueTemperature;
    list<Vibration> historiqueVibrations;

public:

    string Temperature(float valeur, string dateheure);

    string Vibration(string axe, float asymetrie, float moyenne, float aplatissement, float dispersion, float efficace, float min, float max, string dateheure);

    string obtenirHistorique();
};

#endif
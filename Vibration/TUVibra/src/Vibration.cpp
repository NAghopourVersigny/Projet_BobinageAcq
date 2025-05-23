#include "../include/Vibration.h"
#include "../include/ina219.h"
#include <iostream>
using namespace std;

/**
 * @brief Construct a new Vibration:: Vibration object
 *
 * @param axe : axe sur lequel le capteur de vibration est fixé : "X" ou "Y" ou "Z"
 */
Vibration::Vibration(string axe)
{
    if (axe != "X" && axe != "Y" && axe != "Z")
    {
        throw invalid_argument("Axe incorrect");
    }
    this->axe = axe;
    this->vitesseVibration = 0;
}

int Vibration::lire()
{
    float current_mA;
    float shunt_V;
    INA219 *ina = nullptr;

    if (axe == "X")
        ina = new INA219(0.1, 0.02, 0x40);
    else if (axe == "Y")
        ina = new INA219(0.1, 0.02, 0x41);
    else if (axe == "Z")
        ina = new INA219(0.1, 0.02, 0x42);

    ina->configure(RANGE_16V, GAIN_1_40MV, ADC_12BIT, ADC_12BIT); //"configuration" du capteur INA219
    current_mA = ina->current();
    
    vitesseVibration = Calcul_conv(current_mA);

    return 0;
}

string Vibration::getAxe()
{
    return axe;
}

float Vibration::getVitesseVibration()
{
    return vitesseVibration;
}

double Vibration::Calcul_conv(double courant_mA)
{
    /*je dois faire un code qui fait un calcul pour passer de 4-20mA en vibration,
        sachant que 4mA est 0 vibration[mm/s] et 20mA est 50 vibration [mm/s]*/

    double vibration_mm_s = (courant_mA - 4.0) * (50.0 / 16.0);
    return vibration_mm_s;
}
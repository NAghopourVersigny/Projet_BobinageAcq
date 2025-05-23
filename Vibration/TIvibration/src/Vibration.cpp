#include "../include/Vibration.h"
#include "../include/ina219.h"
#include "../include/Logger.h"
#include <iostream>
/**
 * @brief Construct a new Vibration:: Vibration object
 *
 * @param axe : axe sur lequel le capteur de vibration est fixé : "X" ou "Y" ou "Z"
 */



using namespace std;

Vibration::Vibration(string axe)
{
    if (axe != "X" && axe != "Y" && axe != "Z")
    {
        Logger logger("bobinage.log", true);
        logger.error("Axe incorrect fourni au constructeur Vibration : " + axe);
        throw invalid_argument("Axe incorrect");
    }

    this->axe = axe;
    this->vitesseVibration = 0;
}

int Vibration::lire()
{
    static Logger logger("bobinage.log", true);
    float current_mA;
    INA219 *ina = nullptr;

    if (axe == "X")
        ina = new INA219(0.1, 0.02, 0x40);
    else if (axe == "Y")
        ina = new INA219(0.1, 0.02, 0x41);
    else if (axe == "Z")
        ina = new INA219(0.1, 0.02, 0x42);

    if (!ina)
    {
        logger.error("Échec d'initialisation du capteur INA219 pour l'axe : " + axe);
        exit(1);  // arrêt immédiat
    }

    ina->configure(RANGE_16V, GAIN_1_40MV, ADC_12BIT, ADC_12BIT);
    current_mA = ina->current();

    if (current_mA < 4.0 || current_mA > 20.0)
    {
        logger.warning("Courant en dehors des limites 4-20mA : " + to_string(current_mA) + " mA");
        delete ina;  // nettoyage mémoire
        exit(1);     // arrêt immédiat du programme
    }

    vitesseVibration = Calcul_conv(current_mA);

    delete ina;
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
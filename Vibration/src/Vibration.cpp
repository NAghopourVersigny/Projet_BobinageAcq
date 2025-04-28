#include "../include/Vibration.h"
#include "../include/ina219.h"
using namespace std;

Vibration::Vibration(string axe, string dateheure)
{
    this->axe = axe;
    this->vitesseVibration = vitesseVibration;
    this->dateheure = dateheure;
    this->courant_mA = courant_mA;
}

int Vibration::lire()
{
    INA219 *ina = new INA219(0.1, 0.02);
    ina->configure(RANGE_16V, GAIN_1_40MV, ADC_12BIT, ADC_12BIT); //"configuration" du capteur INA219
    float shunt_V = ina->shunt_voltage(); 
    cout << "la tension de shunt est de " << shunt_V << "mV" << endl;
    float courant_mA = ina->current();
    
    /*je dois faire un code qui fait un calcul pour passer de 4-20mA en vibration, 
    sachant que 4mA est 0 vibration[mm/s] et 20mA est 50 vibration [mm/s]*/
}


string Vibration::getAxe()
{
    return axe;
}

float Vibration::getVitesseVibration()
{
    return vitesseVibration;
}

string Vibration::getDateHeure()
{
    return dateheure;
}

double Vibration::Calcul_conv(double courant_mA) {

    // Calcul de la vibration en mm/s selon la formule
    double vibration_mm_s = (courant_mA - 4.0) * (50.0 / 16.0);
    return vibration_mm_s;
}
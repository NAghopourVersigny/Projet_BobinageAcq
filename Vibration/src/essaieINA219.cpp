#include "../include/ina219.h"
#include <iostream>
#include <stdexcept> // Pour lever une exception si le courant n'est pas dans la plage valide

#define GAIN_AUTO 

using namespace std;

// Fonction pour convertir un courant en mA en vibration en mm/s
double courant_to_vibration(double courant_mA) {
    // Vérifier que le courant est dans la plage valide
    if (courant_mA < 4.0 || courant_mA > 20.0) {
       cout << "Le courant doit être compris entre 4 mA et 20 mA"<< endl;
       return -1;  // Retourner une valeur invalidée si le courant est hors plage
    }

    // Calcul de la vibration en mm/s selon la formule
    double vibration_mm_s = (courant_mA - 4.0) * (50.0 / 16.0);
    return vibration_mm_s;
}


int main()
{
    INA219 *ina = new INA219(0.1, 0.02);
    ina->configure(RANGE_16V, GAIN_1_40MV, ADC_12BIT, ADC_12BIT); //"configuration" du capteur INA219
    float shunt_V = ina->shunt_voltage(); 
    cout << "la tension de shunt est de " << shunt_V << "mV" << endl;
    float current_mA = ina->current();

    
    /* je doit faire un code qui fait un calcule pour passer de 4-20mA en vibration, 
    sachant que 4mA est 0 vibration[mm/s] et 20mA est 50 vibration [mm/s]*/
    
    // Appeler la fonction pour convertir le courant en vibration
    double vibration = courant_to_vibration(current_mA);
        
    // Afficher le résultat
    cout << "Pour un courant de " << current_mA << " mA, la vibration est de " << vibration << " mm/s." << endl;


    return 0;
}
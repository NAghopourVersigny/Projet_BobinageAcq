#ifndef VIBRATION_H
#define VIBRATION_H
#include <string>
#include <iostream>

using namespace std;

class Vibration
{
private:
    /**
     * @brief nom de l'axe (X, Y ou Z) sur lequel est installé le capteur
     *
     */
    string axe;

    /**
     * @brief vitesse de vibration efficace relevée par le capteur
     *
     */
    float vitesseVibration;

    string dateheure;
    double courant_mA;

public:

    double Calcul_conv(courant_mA);

    Vibration(string axe, string dateheure);

    /**
     * @brief méthode permettant de lire la valeur de la vibration pour
     * la stocker dans vitesseVibration
     *
     * @return int : code d'erreur 0 : success ; -1 : error
     */
    int lire();
    string getAxe();
    /**
     * @brief Get the Vitesse Vibration object
     *
     * @return float
     */
    float getVitesseVibration();

    string getDateHeure();
};

#endif
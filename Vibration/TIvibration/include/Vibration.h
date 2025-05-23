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

    /**
     * @brief méthode de conversion du courant en vitesse de vibration
     *
     * @param courant_mA : courant fourni par le capteur en mA
     * @return double : vitesse de vibration en mm/s
     */
    double Calcul_conv(double courant_mA);

public:
/**
 * @brief Construct a new Vibration object
 * 
 * @param axe : axe sur lequel le capteur de vibration est fixé : "X" ou "Y" ou "Z"
 */
    Vibration(string axe);

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
};

#endif
#include "../include/Temperature.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

// Méthode qui retourne la valeur de température
float Temperature::getTemp()
{
    this->temp = temp;
    return temp; // Retourne la valeur de la température
}


// Méthode pour calculer la température à partir des données lues
void Temperature::calculerTemp(char data[4])
{
    short resultat2 = data[3] & 0xFC; // Masque les 6 derniers bits du dernier octet pour extraire la température
    resultat2 = (data[2] << 8) + resultat2;  // Combine avec l'octet précédent pour obtenir la température complète
    resultat2 = resultat2 >> 2; // Décale les bits pour ajuster à la plage de température
    this->temp = resultat2; // Conversion en flottant
    this->temp = ((this->temp * 165) / 16383) - 40; // Applique la formule de conversion pour obtenir la température en °C
}
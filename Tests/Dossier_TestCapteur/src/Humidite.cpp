#include "../include/Humidite.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

// Méthode qui retourne la valeur d'humidité
float Humidite::getHumidite()
{
    this->humidite = humidite;
    return humidite; // Retourne la valeur de l'humidité
} 


// Méthode pour calculer la température à partir des données lues
void Humidite::calculerHumidite(char data[4])
{
    short resultat1 = data[0] & 0x3F; // Masque les 6 premiers bits du premier octet pour extraire l'humidité
    resultat1 = (resultat1 << 8) + data[1]; // Combine avec le second octet pour obtenir un entier de 16 bits
    this->humidite = (float)resultat1; // Conversion en flottant
    float coefficient = 1.52;  // Coefficient utilisé pour ajuster l'humidité
    this->humidite = this->humidite * coefficient; // Applique le coefficient
    this->humidite = (this->humidite * 100); // Multiplie par 100 pour avoir un pourcentage
    this->humidite = this->humidite / 16383; // Normalisation en fonction de la plage de valeurs possibles
}
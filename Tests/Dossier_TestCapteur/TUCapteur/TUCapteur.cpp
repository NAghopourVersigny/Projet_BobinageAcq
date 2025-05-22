#include "include/Ambiance.h"
#include "include/TempHumi.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

int main()
{
 
    // Création dynamique d'un objet Ambiance avec l'adresse I2C 0x28
    Ambiance *lAmbiance = new Ambiance(0x28);

    // Création d'un objet TempHumi qui utilise l'objet Ambiance créé précédemment
    TempHumi *leTempHumi = new TempHumi(lAmbiance);

    char data[4]; // Tableau pour stocker 4 octets simulés

    // Boucle pour saisir les 4 octets
    cout << "Entrez 4 octets bruts simulés (entre 0 et 255) :" << endl;
    for (int i = 0; i < 4; ++i) {
        int val;
        cout << "Octet " << i << " : ";
        cin >> val;

        // Vérifie que la valeur est bien entre 0 et 255
        while (val < 0 || val > 255) {
            cout << "Valeur invalide. Veuillez entrer un nombre entre 0 et 255 : ";
            cin >> val;
        }
        // Convertit la valeur entière en caractère (octet)
        data[i] = static_cast<char>(val);
    }

    // Calcul de l'humidité à partir des données brutes
    leTempHumi->calculerHumidite(data);

    // Calcul de la température à partir des données brutes
    leTempHumi->calculerTemp(data);

    // Affichage des valeurs de l'humidité et de la température
    cout << "Humidité : " << leTempHumi->humidite << " %" << endl;
    cout << "Température : " << leTempHumi->temp << " °C" << endl;

    return 0;
}
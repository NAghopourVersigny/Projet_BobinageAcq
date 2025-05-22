#include "../include/TempHumi.h"
#include "../include/Logger.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

TempHumi::TempHumi(int addr)
{
    this->addr = addr;
}
// Méthode pour lire les données du capteur via I2C
void TempHumi::lireAmbiance()
{
    Logger logger("Bobinage.log", true);

    logger.info("Début de l'application...");

    int fd = open("/dev/i2c-1", O_RDWR);

    if (fd < 0)
    {
        logger.error("Échec d'ouverture du bus I2C.");
        exit(1);
    }

    if (ioctl(fd, I2C_SLAVE, addr) < 0)
    {
        logger.error("Échec de configuration de l'adresse I2C.");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        exit(1);
    }

    // Lancer une mesure

    write(fd, data, 0);

    usleep(150000); // Pause de 150 ms pour laisser le temps au capteur de traiter la demande

    read(fd, data, 4); // Lit 4 octets de données depuis le capteur via I2C

    if (read(fd, data, 4) != 4)
    {
        logger.error("Erreur lors de la lecture des données du capteur.");
        close(fd);
        exit(1);
    }
    close(fd); // Ferme le fichier du périphérique I2C
}

/**
 * @brief Méthode pour calculer la température à partir des données lues
 * @param data Les données lues depuis le capteur via I2C
 * @return La température calculée
 */
float TempHumi::calculerHumidite(unsigned char data[4])
{
    float humidity = 0;
    short resultat1 = data[0] & 0x3F; // Masque les 6 premiers bits du premier octet pour extraire l'humidité

    resultat1 = (resultat1 << 8) + data[1]; // Combine avec le second octet pour obtenir un entier de 16 bits
    humidity = (float)resultat1;            // Conversion en flottant
    // float coefficient = 1.52;  // Coefficient utilisé pour ajuster l'humidité
    // this->humidite = this->humidite * coefficient; // Applique le coefficient
    humidity = (humidity * 100); // Multiplie par 100 pour avoir un pourcentage
    humidity = humidity / 16383; // Normalisation en fonction de la plage de valeurs possibles
    return humidity;
}

/**
 * @brief Méthode pour calculer la température à partir des données lues
 * @param data Les données lues depuis le capteur via I2C
 * @return La température calculée
 */
float TempHumi::calculerTemp(unsigned char data[4])
{
    float temperature = 0;
    short resultat2 = data[3] & 0xFC;                 // Masque les 6 derniers bits du dernier octet pour extraire la température
    resultat2 = (data[2] << 8) + resultat2;           // Combine avec l'octet précédent pour obtenir la température complète
    resultat2 = resultat2 >> 2;                       // Décale les bits pour ajuster à la plage de température
    temperature = resultat2;                          // Conversion en flottant
    temperature = ((temperature * 165) / 16383) - 40; // Applique la formule de conversion pour obtenir la température en °C
    return temperature;
}

void TempHumi::getData(unsigned char laData[4])
{
    for (int i = 0; i < 4; i++)
    {
        laData[i] = this->data[i];
    }
}
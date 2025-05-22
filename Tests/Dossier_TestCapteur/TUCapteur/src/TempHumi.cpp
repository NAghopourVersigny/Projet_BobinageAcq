#include "../include/Ambiance.h"
#include "../include/TempHumi.h"
#include "../include/Logger.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

TempHumi::TempHumi(Ambiance* lAmbiance){
    this->lAmbiance=lAmbiance;
}
// Méthode pour lire les données du capteur via I2C
void TempHumi::lireAmbiance()
{
    Logger logger("Bobinage.log", true);

        logger.info("Début de l'application...");

    char data[4];

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

    //Lancer une mesure

    write(fd, data, 0);

    usleep(150000);  // Pause de 150 ms pour laisser le temps au capteur de traiter la demande

    read(fd, data, 4); // Lit 4 octets de données depuis le capteur via I2C

    if (read(fd, data, 4) != 4) {
        logger.error("Erreur lors de la lecture des données du capteur.");
        close(fd);
        exit(1);
    }

    close(fd); // Ferme le fichier du périphérique I2C

    calculerHumidite(data);  //Appelle la méthode pour calculer l'humidité avec les données lues précédemment
    calculerTemp(data); //Appelle la méthode pour calculer la température avec les données lues précédement

    if(temp>100){
        logger.warning("Valeur de Température trop élevé ! : " + to_string(temp) + "°C");
        exit(1);
    }

    if(humidite>80){
        logger.warning("Valeur d'Humidité trop élevé ! : " + to_string(humidite) + "%");
        exit(1);
    }

    if(temp<10){
        logger.warning("Valeur de Température trop basse ! : " + to_string(temp) + "°C");
        exit(1);
    }

    if(humidite<40){
        logger.warning("Valeur d'Humidité trop basse ! : " + to_string(humidite) + "%");
        exit(1);
    }

    logger.info("Fin de l'application.");
}

// Méthode pour calculer la température à partir des données lues
void TempHumi::calculerHumidite(char data[4])
{
    short resultat1 = data[0] & 0x3F; // Masque les 6 premiers bits du premier octet pour extraire l'humidité
    resultat1 = (resultat1 << 8) + data[1]; // Combine avec le second octet pour obtenir un entier de 16 bits
    this->humidite = (float)resultat1; // Conversion en flottant
    //float coefficient = 1.52;  // Coefficient utilisé pour ajuster l'humidité
    //this->humidite = this->humidite * coefficient; // Applique le coefficient
    this->humidite = (this->humidite * 100); // Multiplie par 100 pour avoir un pourcentage
    this->humidite = this->humidite / 16383; // Normalisation en fonction de la plage de valeurs possibles
}

// Méthode pour calculer la température à partir des données lues
void TempHumi::calculerTemp(char data[4])
{
    short resultat2 = data[3] & 0xFC; // Masque les 6 derniers bits du dernier octet pour extraire la température
    resultat2 = (data[2] << 8) + resultat2;  // Combine avec l'octet précédent pour obtenir la température complète
    resultat2 = resultat2 >> 2; // Décale les bits pour ajuster à la plage de température
    this->temp = resultat2; // Conversion en flottant
    this->temp = ((this->temp * 165) / 16383) - 40; // Applique la formule de conversion pour obtenir la température en °C
}
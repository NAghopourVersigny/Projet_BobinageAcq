#include "../include/Contexte.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

// Constructeur de la classe Contexte. Il initialise l'I2C du capteur.
Contexte::Contexte(int addr)
{
    this->addr = addr;
}

// Méthode pour lire les données du capteur via I2C
void Contexte::lireContexte()
{
    char data[4];

    int fd = open("/dev/i2c-1", O_RDWR);
    if (ioctl(fd, I2C_SLAVE, addr) < 0)
    {
        /* ERROR HANDLING; you can check errno to see what went wrong */
        exit(1);
    }
    //Lancer une mesure

    write(fd, data, 0);

    usleep(150000);  // Pause de 150 ms pour laisser le temps au capteur de traiter la demande

    read(fd, data, 4); // Lit 4 octets de données depuis le capteur via I2C

    close(fd); // Ferme le fichier du périphérique I2C

    calculerHumidite(data);  // Appelle la méthode pour calculer l'humidité avec les données lues précédemment
    calculerTemp(data); // Appelle la méthode pour calculer la température avec les données lues précédement
}
#include "../include/Ambiance.h"
#include "../include/TempHumi.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

// Constructeur de la classe Ambiance. Il initialise l'I2C du capteur.
Ambiance::Ambiance(int addr)
{
    this->addr = addr;
}

int Ambiance::AcquérirAmbiance() {
    return 0;
}

int Ambiance::EnregistrerAmbiance() {
    return 0;
}

// Méthode qui retourne la valeur de la température
float Ambiance::getTemp()
{
    this->temp = temp;
    return temp; // Retourne la valeur de la température
}

// Méthode qui retourne la valeur d'humidité
float Ambiance::getHumidite()
{
    this->humidite = humidite;
    return humidite; // Retourne la valeur de l'humidité
} 
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
Ambiance::Ambiance()
{
    leTempHumi = new TempHumi();
    humidite=0;
    temperature=0;
}

int Ambiance::AcquerirAmbiance() {
    unsigned char lesOctets[4];
    leTempHumi->lireAmbiance();
    humidite = leTempHumi->calculerHumidite(lesOctets);
    temperature = leTempHumi->calculerTemp(lesOctets);
    return 0;
}

int Ambiance::EnregistrerAmbiance() {
    return 0;
}

// Méthode qui retourne la valeur de la température
float Ambiance::getTemperature()
{
    return temperature; // Retourne la valeur de la température
}

// Méthode qui retourne la valeur d'humidité
float Ambiance::getHumidite()
{

    return humidite; // Retourne la valeur de l'humidité
} 
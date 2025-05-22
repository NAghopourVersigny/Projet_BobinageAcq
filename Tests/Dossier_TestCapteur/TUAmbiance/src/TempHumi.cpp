#include "../include/TempHumi.h"
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
    cout<<"lireAmbiance"<<endl;
 
}

/**
 * @brief Méthode pour calculer la température à partir des données lues
 * @param data Les données lues depuis le capteur via I2C
 * @return La température calculée
 */
float TempHumi::calculerHumidite(unsigned char data[4])
{
    float humidity = 0;
    cout<<"calculerHumidite"<<endl;
    cout<< "Quelle valeur d'humidité souhaitez-vous ?"<<endl;
    cin >> humidity;

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
    cout<<"calculerTemperature"<<endl;
    cout<< "Quelle valeur de temperature souhaitez-vous ?"<<endl;
    cin >> temperature;
    return temperature;
}

void TempHumi::getData(unsigned char laData[4])
{
    for (int i = 0; i < 4; i++)
    {
        laData[i] = this->data[i];
    }
}
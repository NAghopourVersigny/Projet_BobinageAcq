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
    unsigned char lesOctets[4];
    // Instantiation objets lAmbiance et leTempHumi
    TempHumi *leTempHumi = new TempHumi();

    // Appel de la methode lireAmbiance
    leTempHumi->lireAmbiance();

    leTempHumi->getData(lesOctets);
    for (int i = 0; i < 4; i++)
    {
        cout << "Octet main" << i << " : " << (int)lesOctets[i] << endl;
    }
    cout << "temperature :" << leTempHumi->calculerTemp(lesOctets) << endl;
    cout << "humidite :" << leTempHumi->calculerHumidite(lesOctets) << endl;

    return 0;
}
#include "../include/Contexte.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

int main()
{
    // Modification de l'encapsulation

    // Instantiation objet leContexte
    Contexte *leContexte = new Contexte(0x28);

    // Appel de la methode lireContexte
    leContexte->lireContexte();

    cout << "Température : " << leContexte->getTemp() << endl;
    cout << "Humidité : " << leContexte->getHumidite() << endl;

    return 0;
}
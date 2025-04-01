#include "../include/Contexte.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>

using namespace std; 

int main(){

    //Modification de l'encapsulation
    this->atempAmb=tempAmb;
    this->ahumidite=humidite;

    //Instantiation objet leContexte
    Contexte* leContexte = new Contexte(tempAmb, humidite, tension_reseau, dateheure);

    //Appel des méthodes
    cout << "Température ambiance :" << leContexte->getTempAmb() << endl;
    cout << "Humidité :" << leContexte->getHumidite() << endl;

    return 0;
}
#include "include/Ambiance.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

int main(){

    Ambiance* lAmbiance = new Ambiance();
    lAmbiance->AcquerirAmbiance();
    cout << "Température : " << lAmbiance->getTemperature() << " °C" << endl;
    cout << "Humidité : " << lAmbiance->getHumidite() << " %" << endl;

    return 0;
}
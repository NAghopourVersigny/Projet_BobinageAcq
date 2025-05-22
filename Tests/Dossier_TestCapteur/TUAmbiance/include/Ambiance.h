#ifndef AMBIANCE_H
#define AMBIANCE_H

#include <string>
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "TempHumi.h"

using namespace std;

class Ambiance
{
private:
    float humidite;
    float temperature;
    TempHumi* leTempHumi;

public:
    Ambiance();
    int AcquerirAmbiance();
    int EnregistrerAmbiance();
    float getHumidite();
    float getTemperature();
};

#endif
#include <string>
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

class Ambiance
{
private:
    int addr = 0x28;


public:
    Ambiance(int addr);
    int AcquérirAmbiance();
    int EnregistrerAmbiance();
    float getHumidite();
    float getTemp();
    float humidite;
    float temp;
};


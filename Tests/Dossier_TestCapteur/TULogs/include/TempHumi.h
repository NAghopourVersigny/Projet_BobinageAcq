#include <string>
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

class TempHumi
{
private:
    int addr = 0x28;
    Ambiance* lAmbiance;

public:
    TempHumi(Ambiance* lAmbiance);
    void lireAmbiance();

    void calculerHumidite(char data[4]);
    void calculerTemp(char data[4]);

    float humidite;
    float temp;
};
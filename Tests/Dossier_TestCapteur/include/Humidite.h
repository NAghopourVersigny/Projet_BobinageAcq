#include <string>
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

class Humidite
{
private:
    int addr = 0x28;
    float humidite;

public:
    Humidite();
    float getHumidite();

private:
    void calculerHumidite(char data[4]);
};
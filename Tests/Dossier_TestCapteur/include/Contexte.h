#include <string>
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

class Contexte
{
private:
    int addr = 0x28;
    float humidite;
    float temp;

public:
    Contexte(int addr);
    void lireContexte();

    float getHumidite();
    float getTemp();

private:
    void calculerHumidite(char data[4]);
    void calculerTemp(char data[4]);
};
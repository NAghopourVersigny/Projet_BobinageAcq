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
    unsigned char data[4];


public:
    TempHumi(int addr = 0x28);
    void lireAmbiance();

    float calculerHumidite(unsigned char data[4]);
    float calculerTemp(unsigned char data[4]);

    void getData(unsigned char laData[4]);

};
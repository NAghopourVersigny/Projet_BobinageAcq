#include <string>
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

class Temperature
{
private:
    int addr = 0x28;
    float temp;

public:
    Temperature();
    float getTemp();

private:
    void calculerTemp(char data[4]);
};
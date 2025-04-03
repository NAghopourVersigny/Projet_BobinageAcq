#include "../include/Contexte.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

Contexte::Contexte(int addr)
{
    this->addr = addr;
}

float Contexte::getHumidite()
{
    this->humidite = humidite;
    return humidite;
}

float Contexte::getTemp()
{
    this->temp = temp;
    return temp;
}
void Contexte::lireContexte()
{
    char data[4];

    int fd = open("/dev/i2c-1", O_RDWR);
    if (ioctl(fd, I2C_SLAVE, addr) < 0)
    {
        /* ERROR HANDLING; you can check errno to see what went wrong */
        exit(1);
    }
    //Lancer une mesure

    write(fd, data, 0);

    usleep(150000);

    read(fd, data, 4);

    close(fd);

    calculerHumidite(data);
    calculerTemp(data);
}

void Contexte::calculerHumidite(char data[4])
{
    short resultat1 = data[0] & 0x3F;
    resultat1 = (resultat1 << 8) + data[1];
    this->humidite = (float)resultat1;
    float coefficient = 1.52;
    this->humidite = this->humidite * coefficient;
    this->humidite = (this->humidite * 100);
    this->humidite = this->humidite / 16383;
}

void Contexte::calculerTemp(char data[4])
{
    short resultat2 = data[3] & 0xFC;
    resultat2 = (data[2] << 8) + resultat2;
    resultat2 = resultat2 >> 2;
    this->temp = resultat2;
    this->temp = ((this->temp * 165) / 16383) - 40;
}
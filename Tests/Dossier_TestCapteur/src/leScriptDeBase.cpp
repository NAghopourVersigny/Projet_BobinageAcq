#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

void calculerHumidite(unsigned char data[]);
void calculerTemp(unsigned char data[]);

int main()
{
    int addr = 0x28;
    unsigned char data[4];

    int fd = open("/dev/i2c-1", O_RDWR);
    if (ioctl(fd, I2C_SLAVE, addr) < 0)
    {
        /* ERROR HANDLING; you can check errno to see what went wrong */
        return -1;
    }

    write(fd, data, 0);

    usleep(150000);

    read(fd, data, 4);

    close(fd);

    calculerHumidite(data);
    calculerTemp(data);

    return 0;
}

void calculerHumidite(unsigned char data[])
{
    short resultat1 = data[0] & 0x3F;
    resultat1 = (resultat1 << 8) + data[1];
    float humidite = (float)resultat1;
    humidite = (humidite * 100);
    humidite = humidite / 16383;
    cout << "Humidité :" << humidite << endl;
    cout << (int)(data[0] & 0x40) << endl;
    cout << (int)data[0] << endl;
    cout << (int)data[1] << endl;
}

void calculerTemp(unsigned char data[])
{
    short resultat2 = data[3] & 0xFC;
    resultat2 = (data[2] << 8) + resultat2;
    resultat2 = resultat2 >> 2;
    float temp = resultat2;
    temp = ((temp * 165) / 16383) - 40;
    cout << "Température :" << temp << endl;
    cout << (int)data[2] << endl;
    cout << (int)data[3] << endl;
}
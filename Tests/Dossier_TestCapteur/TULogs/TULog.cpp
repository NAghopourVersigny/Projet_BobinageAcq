#include "../include/TempHumi.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

int main()
{
    // Instantiation objet lAmbiance
    TempHumi *leTempHumi = new TempHumi();

    // Appel de la methode lireAmbiance
    leTempHumi->lireAmbiance();

    return 0;
}
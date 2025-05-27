#include "include/Ambiance.h"
#include "include/TempHumi.h"
#include "include/bdd.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;

int main()
{

    Ambiance *lAmbiance = new Ambiance(0x28);
    TempHumi *leTempHumi = new TempHumi(lAmbiance);

    leTempHumi->lireAmbiance();
    lAmbiance->EnregistrerAmbiance();


    return 0;
}
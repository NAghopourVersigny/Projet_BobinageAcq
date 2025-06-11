#include <string>
#include <unistd.h>
#include <cstdint>
#include <iostream>
#include <cassert>
#include "../include/CompteurElectrique.h"

using namespace std;

int main()
{
    CompteurElectrique ce;

    // Test calculer_crc
    unsigned char data[] = {0x01, 0x04, 0x00, 0x01, 0x00, 0x06};
    assert(ce.calculer_crc(data, 6) == 0xC821);
    cout << "calculer_crc = 0x" << hex << ce.calculer_crc(data, 6) << endl;

    // Tension = 236.44 V 
    unsigned char tensionBytes[4] = {0x00, 0x00, 0x5C, 0x5C};
    assert(abs(ce.calculerTension(tensionBytes) - 237.0f) / 100.0f);
    cout << "calculerTension = " << ce.calculerTension(tensionBytes) << "V" << endl;

    // Intensite = 0.16 A
    unsigned char intensiteBytes[4] = {0x00, 0x00, 0x06, 0x9A};
    assert(abs(ce.calculerIntensite(intensiteBytes) - 0.16f) < 0.0001f);
    cout << "calculerIntensite = " << ce.calculerIntensite(intensiteBytes) << "A" << endl;

    // Facteur puissance = 0.92
    unsigned char fpBytes[4] = {0x00, 0x00, 0x23, 0xF0};
    assert(abs(ce.calculerFacteurPuissance(fpBytes) - 0.92f) < 0.0001f);
    cout << "calculerFacteurPuissance = " << ce.calculerFacteurPuissance(fpBytes) << endl;

    cout << "Les methodes testes fonctionnent" << endl;

    return 0;
}
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdint>
#include "../include/CompteurElectrique.h"
#include "../include/serialib.h"

using namespace std;

unsigned short CompteurElectrique::calculer_crc(const unsigned char data[], int nb_octet)
{
    unsigned short crc = 0xFFFF;
    unsigned short octetsuivant = 0x0000;
    unsigned short crc1 = 0x0000;
    int i = 0;

    crc = 0xFFFF;
    for (i = 0; i < nb_octet; i++)
    {
        octetsuivant = data[i] & 0x00FF;
        crc = (crc ^ octetsuivant);
        for (int j = 1; j <= 8; j++)
        {
            if ((crc & 0x01) == 1)
            {
                crc = (crc >> 1);
                crc = crc ^ 0xA001;
            }
            else
                crc = (crc >> 1);
        }
    }
    return crc;
}

/**CompteurElectrique::CompteurElectrique(float tension, float intensite, float dephasage)
    : tension_reseau(tension), intensite_reseau(intensite), dephasage_reseau(dephasage) {}
**/
CompteurElectrique::CompteurElectrique(unsigned char adresse)
{
    this->adresse = adresse;

    Tension_reseau = vector<float>(3);
    Intensite_reseau = vector<float>(3);
    FacteurPuissance_reseau = vector<float>(3);
}

CompteurElectrique::~CompteurElectrique() {
    // Code de destruction de l'objet, si nécessaire
}

int CompteurElectrique::lireValeursReseauTension()
{
    unsigned char tableregistre[] = {adresse, 0x04, 00, 01, 00, 06, 0x21, 0xC8};
    unsigned char response[17];

    serialib *toto = new serialib();
    char codeErreur = toto->openDevice("/dev/ttyUSB0", 9600);

    char NbBytes = toto->writeBytes(tableregistre, 8);
    int VoltageBytes = toto->readBytes(response, 17, 5000);

    if (VoltageBytes == 17)
    {
        // Vérifier le CRC
        uint16_t crcRecu = response[15] | (response[16] << 8);
        uint16_t crcCalcule = calculer_crc(response, 15);

        if (crcRecu != crcCalcule)
        {
            cout << "de tension" << endl;
            cout << "CRC faux" << endl;
            cout << "CRC reçu: 0x" << hex << crcRecu << endl;
            cout << "CRC calculé: 0x" << hex << crcCalcule << endl;
            return -3;
        }
        else
        {
            unsigned char phase[4];
            phase[0] = response[3];
            phase[1] = response[4];
            phase[2] = response[5];
            phase[3] = response[6];
            Tension_reseau[0] = calculerTension(phase);

            phase[0] = response[7];
            phase[1] = response[8];
            phase[2] = response[9];
            phase[3] = response[10];
            Tension_reseau[1] = calculerTension(phase);

            phase[0] = response[11];
            phase[1] = response[12];
            phase[2] = response[13];
            phase[3] = response[14];
            Tension_reseau[2] = calculerTension(phase);

            toto->closeDevice();
        }
        return 0;
    }
    else
    {
        toto->closeDevice();
        return -2;
    }
}

int CompteurElectrique::lireValeursReseauIntensitee()
{
    unsigned char registres[] = {adresse, 0x04, 00, 07, 00, 06, 0xC1, 0xC9};
    unsigned char respuesta[17];

    serialib *tata = new serialib();
    char codeErreur = tata->openDevice("/dev/ttyUSB0", 9600);

    char NbBytes = tata->writeBytes(registres, 8);
    int AmpereBytes = tata->readBytes(respuesta, 17, 10000);

    if (AmpereBytes == 17)
    {
        uint16_t crcRecu = respuesta[15] | (respuesta[16] << 8);
        uint16_t crcCalcule = calculer_crc(respuesta, 15);

        if (crcRecu != crcCalcule)
        {
            cout << "CRC faux" << endl;
            cout << "CRC reçu: 0x" << hex << crcRecu << endl;
            cout << "CRC calculé: 0x" << hex << crcCalcule << endl;
            return -3;
        }
        else
        {
            unsigned char phase[4];
            phase[0] = respuesta[3];
            phase[1] = respuesta[4];
            phase[2] = respuesta[5];
            phase[3] = respuesta[6];
            Intensite_reseau[0] = calculerIntensite(phase);

            phase[0] = respuesta[7];
            phase[1] = respuesta[8];
            phase[2] = respuesta[9];
            phase[3] = respuesta[10];
            Intensite_reseau[1] = calculerIntensite(phase);

            phase[0] = respuesta[11];
            phase[1] = respuesta[12];
            phase[2] = respuesta[13];
            phase[3] = respuesta[14];
            Intensite_reseau[2] = calculerIntensite(phase);

            tata->closeDevice();
        }
        return 0;
    }
    else
    {
        tata->closeDevice();
        return -2;
    }
}

int CompteurElectrique::lireValeursReseauFacteurPuissance()
{
    unsigned char tables[] = {adresse, 0x04, 00, 0x25, 00, 06, 0x61, 0xC3};
    unsigned char answer[17];

    serialib *titi = new serialib();
    char codeErreur = titi->openDevice("/dev/ttyUSB0", 9600);

    char NbBytes = titi->writeBytes(tables, 8);

    int CosphiBytes = titi->readBytes(answer, 17, 5000);

    if (CosphiBytes == 17)
    {
        uint16_t crcRecu = answer[15] | (answer[16] << 8);
        uint16_t crcCalcule = calculer_crc(answer, 15);

        if (crcRecu != crcCalcule)
        {
            cout << "CRC faux" << endl;
            cout << "CRC reçu: 0x" << hex << crcRecu << endl;
            cout << "CRC calculé: 0x" << hex << crcCalcule << endl;
            return -3;
        }
        else
        {
            unsigned char phase[4];
            phase[0] = answer[3];
            phase[1] = answer[4];
            phase[2] = answer[5];
            phase[3] = answer[6];
            FacteurPuissance_reseau[0] = calculerFacteurPuissance(phase);

            phase[0] = answer[7];
            phase[1] = answer[8];
            phase[2] = answer[9];
            phase[3] = answer[10];
            FacteurPuissance_reseau[1] = calculerFacteurPuissance(phase);

            phase[0] = answer[11];
            phase[1] = answer[12];
            phase[2] = answer[13];
            phase[3] = answer[14];
            FacteurPuissance_reseau[2] = calculerFacteurPuissance(phase);

            titi->closeDevice();
        }
        return 0;
    }
    else
    {
        titi->closeDevice();
        return -2;
    }
}

float CompteurElectrique::calculerTension(unsigned char tension[4])
{
    int tension16 = tension[0];
    tension16 = (tension16 << 8);
    tension16 += tension[1];
    tension16 = (tension16 << 8);
    tension16 += tension[2];
    tension16 = (tension16 << 8);
    tension16 += tension[3];

    float TENSION = tension16;

    TENSION = TENSION / 100.0f;

    return TENSION;
}

float CompteurElectrique::calculerIntensite(unsigned char intensite[4])
{
    int intensite16 = intensite[0];
    intensite16 = (intensite16 << 8);
    intensite16 += intensite[1];
    intensite16 = (intensite16 << 8);
    intensite16 += intensite[2];
    intensite16 = (intensite16 << 8);
    intensite16 += intensite[3] - 0x5A;

    float INTENSITE = intensite16;
    
    INTENSITE = INTENSITE / 10000.0f;

    return INTENSITE;
}

float CompteurElectrique::calculerFacteurPuissance(unsigned char facteurP[4])
{
    int facteurP16 = facteurP[0];
    facteurP16 = (facteurP16 << 8);
    facteurP16 += facteurP[1];
    facteurP16 = (facteurP16 << 8);
    facteurP16 += facteurP[2];
    facteurP16 = (facteurP16 << 8);
    facteurP16 += facteurP[3];

    float FACTEURPUISSANCE = facteurP16;
    
    FACTEURPUISSANCE = FACTEURPUISSANCE / 10000.0f;

    return FACTEURPUISSANCE;
}

vector<float> CompteurElectrique::getTensionReseau()
{

    return Tension_reseau;
}

vector<float> CompteurElectrique::getIntensiteReseau()
{

    return Intensite_reseau;
}

vector<float> CompteurElectrique::getFacteurPuissanceReseau()
{

    return FacteurPuissance_reseau;
}
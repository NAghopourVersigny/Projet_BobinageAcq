#ifndef COMPTEUR_ELECTRIQUE_H
#define COMPTEUR_ELECTRIQUE_H
#include <vector>

#include "../include/serialib.h"

using namespace std;

class CompteurElectrique
{
private:

    unsigned char adresse;

    vector<float> Tension_reseau;
    vector<float> Intensite_reseau;
    vector<float> FacteurPuissance_reseau;

public:

    CompteurElectrique(unsigned char adresse = 0x01);

    int lireValeursReseauTension();
    int lireValeursReseauIntensitee();
    int lireValeursReseauFacteurPuissance();

    unsigned short calculer_crc(const unsigned char data[], int len);
    float calculerTension(unsigned char tension[4]);
    float calculerIntensite(unsigned char intensite[4]);
    float calculerFacteurPuissance(unsigned char facteurP[4]);

    vector<float> getTensionReseau();
    vector<float> getIntensiteReseau();
    vector<float> getFacteurPuissanceReseau();

    ~CompteurElectrique();
};

#endif
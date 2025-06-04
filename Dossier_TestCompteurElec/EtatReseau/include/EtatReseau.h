#ifndef ETATRESEAU_H
#define ETATESEAU_H
#include <vector>

#include "../include/serialib.h"
#include "../include/CompteurElectrique.h"
#include "../include/Logger.h"
#include "../include/DatabaseManager.h"

using namespace std;

class EtatReseau
{
private:

    CompteurElectrique* leCompteurReseau;

    vector<float> Tension_reseau;
    vector<float> Intensite_reseau;
    vector<float> FacteurPuissance_reseau;

public:     

    EtatReseau(CompteurElectrique* leCompteurReseau);
    void acquerirEtatReseau();
    void enregistrerReseau(string dateHeure, DatabaseManager * db);

    vector<float> getTension_Reseau();
    vector<float> getIntensite_Reseau();
    vector<float> getFacteurPuissance_Reseau();
};

#endif
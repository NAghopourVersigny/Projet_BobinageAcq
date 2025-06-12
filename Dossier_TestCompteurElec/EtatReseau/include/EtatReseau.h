#ifndef ETATRESEAU_H
#define ETATRESEAU_H
#include <vector>

#include <chrono>

#include <cstring>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

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

    EtatReseau();
    void acquerirEtatReseau();
    void enregistrerEtatReseau(DatabaseManager *leDatabaseManager);//, int id_Machine);

    vector<float> getTension_Reseau();
    vector<float> getIntensite_Reseau();
    vector<float> getFacteurPuissance_Reseau();


};

#endif
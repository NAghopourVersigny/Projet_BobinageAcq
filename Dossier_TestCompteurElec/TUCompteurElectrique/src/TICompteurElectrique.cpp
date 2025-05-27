#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdint>
#include "../include/CompteurElectrique.h"

using namespace std;

int main()
{
CompteurElectrique *leCompteur = new CompteurElectrique(0x01);
// Appel de la methode
leCompteur->lireValeursReseauTension();

vector<float> Tension_reseau = leCompteur->getTensionReseau();
cout <<"La tension en L1 est:" << Tension_reseau[0] << "V, en L2: " << Tension_reseau[1] << "V, en L3: " << Tension_reseau[2] << " V" << endl;

usleep(200);
leCompteur->lireValeursReseauIntensitee();

vector<float> Intensite_reseau = leCompteur->getIntensiteReseau();
cout << "L'intensité en Ll est: " << Intensite_reseau[0] << "A, en L2: " << Intensite_reseau[1] << "A, en L3: " << Intensite_reseau[2] << "A" << endl;

usleep(200);
leCompteur->lireValeursReseauFacteurPuissance();

vector<float> FacteurPuissance_reseau = leCompteur->getFacteurPuissanceReseau();
cout << "Le facteurde puissance en Ll est: "<< FacteurPuissance_reseau[0] << ", en L2: " << FacteurPuissance_reseau[1] << ", en L3: " << FacteurPuissance_reseau[2] <<endl;

return 0;
}

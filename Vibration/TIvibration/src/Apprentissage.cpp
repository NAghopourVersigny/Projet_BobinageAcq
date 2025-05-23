#include "../include/Apprentissage.h"
#include <cmath>
#include <numeric>

using namespace std;

Apprentissage::Apprentissage() {
    modeApprentissage = false;
}

void Apprentissage::commencerApprentissage() {
    modeApprentissage = true;
}

void Apprentissage::terminerApprentissage() {
    modeApprentissage = false;
}

bool Apprentissage::estEnModeApprentissage() const {
    return modeApprentissage;
}

void Apprentissage::ajouterLecture(string axe, int valeur) {
    historique[axe].push_back(valeur);
}

void Apprentissage::calculerModele(string axe) {
    auto& donnees = historique[axe];
    if (donnees.empty()) return;

    float somme = accumulate(donnees.begin(), donnees.end(), 0.0f);
    moyenne[axe] = somme / donnees.size();

    float variance = 0.0;
    for (int v : donnees) {
        variance += pow(v - moyenne[axe], 2);
    }
    ecartType[axe] = sqrt(variance / donnees.size());
}

bool Apprentissage::detecterAnomalie(string axe, int valeur, float seuil) {
    if (moyenne.find(axe) == moyenne.end() || ecartType.find(axe) == ecartType.end())
        return false;

    float diff = abs(valeur - moyenne[axe]);
    return diff > seuil * ecartType[axe];
}
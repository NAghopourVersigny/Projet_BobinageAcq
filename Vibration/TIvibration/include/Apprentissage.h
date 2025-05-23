#ifndef APPRENTISSAGE_H
#define APPRENTISSAGE_H

#include <vector>
#include <string>
#include <map>

using namespace std;

class Apprentissage {
private:
    bool modeApprentissage;
    map<string, vector<int>> historique; // axe → lectures
    map<string, float> moyenne;
    map<string, float> ecartType;

public:
    Apprentissage();

    void commencerApprentissage();
    void terminerApprentissage();
    bool estEnModeApprentissage() const;

    void ajouterLecture(string axe, int valeur);
    void calculerModele(string axe);
    bool detecterAnomalie(string axe, int nouvelleValeur, float seuil = 2.0);
};

#endif // APPRENTISSAGE_H
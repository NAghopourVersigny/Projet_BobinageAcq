#include <vector>
#include <algorithm>
#include <iostream>
#include "bdd.h"
#include "SeuilsIOT.h"
#include "Vibration.h" //Rajouter le chemin vers le fichier Vibration.h

class Apprentissage
{

private:
    bool apprentissageTemp;
    bool apprentissageVibra;




public:
    Apprentissage(bool apprentissageTemp, bool apprentissageVibra);
    ~Apprentissage();

    bool interrogerBDDTemp();
    /**
     * @brief 
     * 
     * @param laCamera 
     * @param lesSeuils 
     */
    void lancerApprentissageTemp(Camera * laCamera, SeuilsIOT * lesSeuils);
    bool validerApprentissageTemp();
    float getSeuilTempMoy() const;
    float getSeuilTempMax() const;

    bool interrogerBDDVibra();
    /**
     * @brief effectue l'apprentissage
     * 
     * @param lesVibrations : collection de vibration dans l'ordre : axe X, axe Y et axe Z
     * @param lesSeuils 
     */
    void lancerApprentissageVibra(vector<Vibration> lesVibrations, SeuilsIOT * lesSeuils);
    bool validerApprentissageVibra();





};
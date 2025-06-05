#include <vector>
#include <algorithm>
#include <iostream>
#include "DatabaseManager.h"
#include "SeuilsIOT.h"
#include "Camera.h"
#include "Vibration.h"

class Apprentissage
{

private:
    bool apprentissageTemp;
    bool apprentissageVibra;
    Camera *laCamera;

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
#ifndef CAMERA_H
#define CAMERA_H


/**
 * Attention ! Classe de test!
*/

#include "FLIRAX8.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <regex>
#include <ctime> //inclusion d'outils de génération de données
#include <chrono>
#include "Seuils.h"  //inclusion d'outils de générattion de données

using namespace std;
namespace fs = std::filesystem;

class Camera
{
private:
    FLIR_AX8 *flir;
    float temperatureMoyImage;
    float temperatureMaxImage;
    string nomImage;

    double seconds; //attribut simulation de timing de données
    double moment ; //attribut simulation période de fonctionnement
    time_t firstMoment; //attribut simulation date de départ de surveillance    

public:
    Camera(string hostname);
    ~Camera();

    float obtenirTempMoy();
    float obtenirTempMax();
    float obtenirTempMin();

    void capturer_Image();
    void recuperer_Image();

    string obtenir_nom_image();
};

#endif

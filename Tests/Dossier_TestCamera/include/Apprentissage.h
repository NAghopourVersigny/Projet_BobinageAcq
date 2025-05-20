#include <vector>
#include <algorithm>
#include <iostream>
#include "bdd.h"
#include "Camera.h"

class Apprentissage{

private : 

    Camera* laCamera;
    BDD* laBDD;
    vector<float> tempMoy;
    vector<float> tempMax;


public :
    Apprentissage();
    ~Apprentissage();


    bool interrogerBDDTemp();
    void lancerApprentissageTemp();
    void validerApprentissage();    
};
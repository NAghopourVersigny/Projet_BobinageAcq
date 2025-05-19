#include <vector>
#include <algorithm>
#include <iostream>

class Apprentissage{

private : 

    Camera* laCamera;
    vector<float> tempMoy;
    vector<float> tempMax;


public :
    Apprentissage();
    ~Apprentissage();


    bool interrogerBDDTemp();
    void lancerApprentissageTemp();
    void validerApprentissage();    
    void determinerSeuilMax(vector<float> tempMax);
    void determinerSeuilMoy(vector<float> tempMoy);
};
#include <algorithm>
#include <iostream>

class Apprentissage{

private : 

    Camera* laCamera;

public :
    Apprentissage();
    ~Apprentissage();


    void interrogationBDD();
    void lancementApprentissageTemp();
    void validationApprentissage();
    void determinationSeuilMax();
    void determinationSeuilMoy();
};
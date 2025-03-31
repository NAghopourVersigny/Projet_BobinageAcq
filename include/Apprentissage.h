#ifndef APPRENTISSAGE_H
#define APPRENTISSAGE_H
#include <string>
#include <iostream>

using namespace std;

class Apprentissage{

    private:

    bool apprentissage = false;
    
    public:

    Apprentissage(bool apprentissage);

    bool obtenirApprentissageTemp(bool apprentissage, int idMachine);

    bool terminerApprentissageTemp(int idMachine);

};

#endif
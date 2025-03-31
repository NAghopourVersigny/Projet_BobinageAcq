#ifndef FORMATAGE_H
#define FORMATAGE_H
#include <string>
#include <iostream>

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Stringifier.h"
#include "bdd.h"


using namespace std;

class Formatage
{

private:
public:
    Formatage();
    string mettreEnFormeTemp(list<Temperature>*);
    string mettreEnFormeVibra(list<Vibration>*);
    string mettreEnFormeCont(list<Contexte>*);
    string mettreEnFormeEven(list<Evenement>*);
    string mettreEnFormeImage(list<Image>*);

};

#endif
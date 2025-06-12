#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <string>
#include <iostream>

#include "Image.h"

using namespace std;

class Evenement
{
private : 

    Image* image;

    string type;
    string dateheure;

public : 

    Evenement();

    Evenement(string type, string dateheure);

    string getType();
    string getDateHeure();
};

#endif
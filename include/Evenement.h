#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <string>
#include <iostream>

using namespace std;

class Evenement
{
    private : 

    string type;
    string dateheure;

    public : 

    Evenement(string type, string dateheure);
    string getType();
    string getDateHeure();


};

#endif
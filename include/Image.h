#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include <iostream>

using namespace std;

class Image
{
    private : 

    string type;
    string nom;
    string dateheure;

    public : 

    Image(string nom, string type, string dateheure);
    string getType();
    string getNom();
    string getDateHeure();

};

#endif
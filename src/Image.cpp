#include "../include/Image.h"

Image::Image(string nom, string type, string dateheure)
{
    this->type = type;
    this->nom= nom;
    this->dateheure = dateheure;
}

string Image::getType()
{
    return type;
}

string Image::getNom()
{
    return nom;
}


string Image::getDateHeure()
{
    return dateheure;
}
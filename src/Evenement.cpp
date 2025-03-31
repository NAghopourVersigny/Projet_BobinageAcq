#include "../include/Evenement.h"

Evenement::Evenement(string type, string dateheure)
{
    this->type = type;
    this->dateheure = dateheure;
}

string Evenement::getType()
{
    return type;
}

string Evenement::getDateHeure()
{
    return dateheure;
}
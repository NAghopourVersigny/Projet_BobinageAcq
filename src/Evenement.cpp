#include "../include/Evenement.h"

Evenement::Evenement() {
    this->type = "type";
    this->dateheure= "2025-06-11 14:05:30";
}

Evenement::Evenement(string type, string dateheure)
{
    this->type = type;
    this->dateheure = dateheure;
}

string Evenement::getType()
{
    return this->type;
}

string Evenement::getDateHeure()
{
    return this->dateheure;
}
#include "../include/Vibration.h"

Vibration::Vibration(string axe, float asymetrie, float moyenne, float aplatissement, float dispersion, float efficace, float min, float max, string dateheure)
{
    this->axe = axe;
    this->asymetrie = asymetrie;
    this->moyenne = moyenne;
    this->aplatissement = aplatissement;
    this->dispersion = dispersion;
    this->efficace = efficace;
    this->min = min;
    this->max = max;
    this->dateheure = dateheure;
}
string Vibration::getAxe()
{
    return axe;
}

float Vibration::getAsymetrie()
{
    return asymetrie;
}

float Vibration::getMoyenne()
{
    return moyenne;
}

float Vibration::getAplatissement()
{
    return aplatissement;
}

float Vibration::getDispersion()
{
    return dispersion;
}

float Vibration::getEfficace()
{
    return efficace;
}

float Vibration::getMin()
{
    return min;
}

float Vibration::getMax()
{
    return max;
}

string Vibration::getDateHeure()
{
    return dateheure;
}
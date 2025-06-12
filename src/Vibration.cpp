#include "../include/Vibration.h"

using namespace std;

Vibration::Vibration(string axe)
{
    this->axe = axe;
    this->vitesseVibration = 0;
    this->dateheure = "2025-06-10 10:15:13";

}


string Vibration::getAxe()
{
    return axe;
}

string Vibration::getDateheure()
{
    return dateheure;
}

float Vibration::getVitesseVibration()
{
    return vitesseVibration;
}

void Vibration::setAxe()
{
    this->axe = axe;
}

void Vibration::setVitesseVibration(float vitesseVibration)
{
    this->vitesseVibration = vitesseVibration;
}

void Vibration::setDateheure(string dateheure)
{
    this->dateheure = dateheure;
}
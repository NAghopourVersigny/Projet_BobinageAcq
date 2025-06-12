#ifndef VIBRATION_H
#define VIBRATION_H
#include <string>
#include <iostream>

#include "DatabaseManager.h"

using namespace std;

class Vibration
{
private:

    string axe;
    float vitesseVibration;
    string dateheure;

public:

    Vibration(string axe);


    string getAxe();
    string getDateheure();
    float getVitesseVibration();

    void setAxe();
    void setVitesseVibration(float vitesseVibration);
    void setDateheure(string dateheure);
};

#endif
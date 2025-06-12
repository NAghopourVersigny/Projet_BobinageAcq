#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include <string>
#include <iostream>

using namespace std;

class Temperature
{
private:
    float moyenne;
    float maximale;
    string dateheure;

public:
    Temperature();
    Temperature(float moyenne, float maximale, string dateheure);
    float getMoyenne();
    float getMaximale();
    string getDateHeure();
    void setMoyenne(float moyenne);
    void setMaximale(float maximale);
    void setDateHeure(string dateheure);
};

#endif

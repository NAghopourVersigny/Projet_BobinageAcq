#ifndef VIBRATION_H
#define VIBRATION_H
#include <string>
#include <iostream>

using namespace std;

class Vibration
{
private:
    string axe;
    float asymetrie;
    float moyenne;
    float aplatissement;
    float dispersion;
    float efficace;
    float min; 
    float max;
    string dateheure;

public:
    Vibration(string axe, float asymetrie, float moyenne, float aplatissement, float dispersion, float efficace, float min, float max, string dateheure);
    string getAxe();
    float getAsymetrie();
    float getMoyenne();
    float getAplatissement();
    float getDispersion();
    float getEfficace();
    float getMin();
    float getMax();
    string getDateHeure();
};

#endif
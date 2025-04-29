#include <iostream>
#include "../include/Vibration.h"
#include "../include/ina219.h"

using namespace std;

int main(){

string axe = "X";
Vibration *laVibration = new Vibration (axe);

laVibration->lire();

cout << laVibration->getAxe() << endl;
cout << "vitesse de vibration "<< laVibration->getVitesseVibration() << endl;
//cout << laVibration->Calcul_conv(current_mA) << endl;



    return 0;
}
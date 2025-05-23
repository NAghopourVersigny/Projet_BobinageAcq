#include "../include/Vibration.h"
#include <iostream>
#include <stdexcept> // Pour lever une exception si le courant n'est pas dans la plage valide

using namespace std;
float courant_mA;
float vibration_mm_s;
float shunt_V;
int main()

{
    float vitesseVibration;
    char sortie = 'N';
    string axe;
    Vibration *vibration;
    do
    {
        cout<<"Test du constructeur"<<endl;
        cout << "Quel axe voulez-vous mesurer ? X, Y ou Z" << endl;
        cin>>axe;

        vibration = new Vibration(axe); // Peut lever une exception

        vibration->lire();
        vitesseVibration = vibration->getVitesseVibration();

        cout << "La vitesse de vibration est de " << vitesseVibration << " mm/s" << endl;

        cout << "Voulez-vous terminer ? (O pour Oui, N pour NON)" << endl;
        cin >> sortie;
    } while (sortie != 'O');

    return 0;
}
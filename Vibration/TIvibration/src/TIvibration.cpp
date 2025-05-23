#include "../include/Vibration.h"
#include <iostream>
#include <stdexcept>
#include "../include/Logger.h"

using namespace std;

int main()
{
   Logger logger("bobinage.log", true); // Crée un logger
    
    float vitesseVibration;
    string axe;

    cout << "Quel axe voulez-vous mesurer ? X, Y ou Z" << endl;
    cin >> axe;


    logger.info("Démarrage de l'application.");  // Log info au lancement
    try
    {
        Vibration* vibration = new Vibration(axe);  // Peut lever une exception
        vibration->lire();                           // Peut appeler exit(1) si courant hors plage
        vitesseVibration = vibration->getVitesseVibration();

        cout << "La vitesse de vibration est de " << vitesseVibration << " mm/s" << endl;

        delete vibration;
    }
    catch (const invalid_argument& e)
    {
        logger.error("Exception (argument invalide) dans main : " + string(e.what()));
        cerr << "Erreur : " << e.what() << endl;
        return 1;
    }
    catch (const exception& e)
    {
        logger.error("Exception générale dans main : " + string(e.what()));
        cerr << "Erreur : " << e.what() << endl;
        return 1;
    }
 logger.info("Fin de mesure des vibrations.");  // Log info a la fin
    return 0;
}
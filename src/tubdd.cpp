#include "../include/Temperature.h"
#include "../include/Vibration.h"
#include "../include/bdd.h"
#include <iostream>

int main()
{
    Base *base = new Base();
    int mode = 10;
    int idMachine = 1;
            list<Temperature> *t_resultat = base->obtenirDataFonctTemp("", "", idMachine);
        for (auto it = t_resultat->begin(); it != t_resultat->end(); ++it)
        {
            cout << "temperature = " << it->getValeur() << endl;
            cout << "date = " << it->getDateHeure() << endl;
            cout << " " << endl << " " <<endl;
        }

    while (mode != 0){
    
    if (mode > 0)
    {
        cout << "Choisir le test : 0 = Arrêter, 1 = Afficher donnee temperature, 2 = Afficher donnees vibration, 3 = Inserer donnee temperature, 4= obtenirSeuilsTemp." << endl;
        cin >> mode;
    }

    if (mode == 1)
    {
        // Voir données température
        string dateDebut = "2024-01-19 17:00:00";
        string dateFin = "2024-01-19 17:30:00";

        list<Temperature> *t_resultat = base->obtenirDataFonctTemp(dateDebut, dateFin, idMachine);
        for (auto it = t_resultat->begin(); it != t_resultat->end(); ++it)
        {
            cout << "temperature = " << it->getValeur() << endl;
            cout << "date = " << it->getDateHeure() << endl;
            cout << " " << endl << " " <<endl;
        }
    }

    if (mode == 2)
    {
        // Voir données vibration
        string dateDebut = "2024-05-27 15:50:00";
        string dateFin = "2024-05-27 17:00:00";

        list<Vibration> *v_resultat = base->obtenirDataFonctVibra(dateDebut, dateFin, idMachine);
        for (auto it = v_resultat->begin(); it != v_resultat->end(); ++it)
        {

            cout << "axe = " << it->getAxe() << endl;
            cout << "asymetrie = " << it->getAsymetrie() << endl;
            cout << "moyenne = " << it->getMoyenne() << endl;
            cout << "aplatissement = " << it->getAplatissement() << endl;
            cout << "dispersion = " << it->getDispersion() << endl;
            cout << "efficace = " << it->getEfficace() << endl;
            cout << "min = " << it->getMin() << endl;
            cout << "max = " << it->getMax() << endl;
            cout << "date = " << it->getDateHeure() << endl;
            cout << " " << endl << " " <<endl;
        }
    
    }
    if (mode == 3)
    {
        // Ajout données température :
        string date = "2099-02-20 18:00:00";
        float tempMachine = 99.9;
        int idTemp = base->ajouterDataFonctTemp(date, tempMachine, idMachine = 1);
        cout << "id ajout = " << idTemp << endl;
    }

    if (mode == 4)
    {
        // Obtention seuils de température
        float tempMax=0,tempMoy=0;
        base->obtenirSeuilTemp(tempMax,tempMoy);
        cout << "seuil alerte sur la température max de la zone surveillée" << tempMax << endl;
        cout << "seuil alerte sur la température moy de la zone surveillée" << tempMoy << endl;
    }    
    }
}
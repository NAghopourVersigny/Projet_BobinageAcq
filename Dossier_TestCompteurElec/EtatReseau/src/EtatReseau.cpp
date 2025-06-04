#include "../include/EtatReseau.h"
#include "../include/DatabaseManager.h"
#include <chrono>
#include <iostream>
#include <cstring>

EtatReseau::EtatReseau(CompteurElectrique* leCompteurReseau)
{
    this->leCompteurReseau = leCompteurReseau;

    Tension_reseau = vector<float>(3);
    Intensite_reseau = vector<float>(3);
    FacteurPuissance_reseau = vector<float>(3);
}

void EtatReseau::acquerirEtatReseau()
{   
    leCompteurReseau->lireValeursReseauTension();
    leCompteurReseau->lireValeursReseauIntensitee();
    leCompteurReseau->lireValeursReseauFacteurPuissance();

    Tension_reseau = leCompteurReseau->getTensionReseau();
    Intensite_reseau = leCompteurReseau->getIntensiteReseau();
    FacteurPuissance_reseau = leCompteurReseau->getFacteurPuissanceReseau();
}

void EtatReseau::enregistrerReseau(string dateHeure, DatabaseManager * db) //envoie des donnees vers la BDD
{
    string query = "INSERT INTO Contexte (tension1, tesnion2, tension3, intentite1, intensite2, intensite3, cosPhi1, cosPhi2, cosPhi3)) VALUES (" + to_string(Tension_reseau[0]) + "," + to_string(Tension_reseau[1]) + "," + to_string(Tension_reseau[2]) + "," + to_string(Intensite_reseau[0]) + "," + to_string(Intensite_reseau[1]) + "," + to_string(Intensite_reseau[2]) + "," + to_string(FacteurPuissance_reseau[0]) + "," + to_string(FacteurPuissance_reseau[1]) + "," + to_string(FacteurPuissance_reseau[2]) + ")";
    DatabaseManager *leDatabaseManager = new DatabaseManager();
    leDatabaseManager->executerRequete(query);
}

vector<float> EtatReseau::getTension_Reseau()
{
    return Tension_reseau;
}

vector<float> EtatReseau::getIntensite_Reseau()
{
    return Intensite_reseau;
}

vector<float> EtatReseau::getFacteurPuissance_Reseau()
{
    return FacteurPuissance_reseau;    
}
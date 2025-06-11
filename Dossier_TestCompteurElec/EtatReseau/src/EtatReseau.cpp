#include "../include/EtatReseau.h"
#include "../include/DatabaseManager.h"


EtatReseau::EtatReseau()
{
    this->leCompteurReseau = new CompteurElectrique();

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

void EtatReseau::enregistrerEtatReseau(DatabaseManager *leDatabaseManager)  //, int id_Machine) //envoie des donnees vers la BDD
{
    //string query = "INSERT INTO Contexte (date, tension1, tension2, tension3, intensite1, intensite2, intensite3, cosPhi1, cosPhi2, cosPhi3) VALUES (" + dateHeure + "," + to_string(Tension_reseau[0]) + "," + to_string(Tension_reseau[1]) + "," + to_string(Tension_reseau[2]) + "," + to_string(Intensite_reseau[0]) + "," + to_string(Intensite_reseau[1]) + "," + to_string(Intensite_reseau[2]) + "," + to_string(FacteurPuissance_reseau[0]) + "," + to_string(FacteurPuissance_reseau[1]) + "," + to_string(FacteurPuissance_reseau[2]) + ")";
    string query = "UPDATE Contexte SET tension1 = " + to_string(Tension_reseau[0]) + ", tension2 = " + to_string(Tension_reseau[1]) + ", tension3 = " + to_string(Tension_reseau[2]) + ", intensite1 = " + to_string(Intensite_reseau[0]) + ", intensite2 = " + to_string(Intensite_reseau[1]) + ", intensite3 = " + to_string(Intensite_reseau[2]) + ", cosPhi1 = " + to_string(FacteurPuissance_reseau[0]) + ", cosPhi2 = " + to_string(FacteurPuissance_reseau[1]) + ", cosPhi3 = " + to_string(FacteurPuissance_reseau[2]) + " WHERE id = (SELECT MAX(id) FROM Contexte);";
    //cout<< query <<endl;
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

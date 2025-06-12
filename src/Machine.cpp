#include "../include/Machine.h"
#include "../include/DatabaseDAO.h"

using namespace std;

Machine::Machine(int numero)
{
    this->numero = numero;
    this->apprentissageTermineTemp = false;
    this->apprentissageTermineVibra = false;
    temperature = new Temperature();
    seuils = new Seuils();
    listeVibrations.push_back(new Vibration("X"));
    listeVibrations.push_back(new Vibration("Y"));
    listeVibrations.push_back(new Vibration("Z"));
    lastEvenement = new Evenement();
    ambiance = new Ambiance();
}

int Machine::getNumero()
{
    return numero;
}

bool Machine::getApprentissageTermineTemp()
{
    return apprentissageTermineTemp;
}

bool Machine::getApprentissageTermineVibra()
{
    return apprentissageTermineVibra;
}

Temperature *Machine::getTemperature()
{
    return temperature;
}

Seuils *Machine::getSeuils()
{
    return seuils;
}
/**
 * @param axe : X, Y ou Z
 * @return un pointeur sur la vibration correspondante
 */
Vibration *Machine::getVibrations(string axe)
{
    if (axe == "X")
    {
        return listeVibrations.at(0);
    }
    else if (axe == "Y")
    {
        return listeVibrations.at(1);
    }
    else if (axe == "Z")
    {
        return listeVibrations.at(2);
    }
    else
    {
        return nullptr;
    }
}

Evenement *Machine::getLastEvenement()
{
    return lastEvenement;
}

void Machine::setApprentissageTermineTemp(bool apprentissageTermineTemp)
{
}

void Machine::setApprentissageTermineVibra(bool apprentissageTermineVibra)
{
}

void Machine::setTemperature(Temperature* temp)
{
    this->temperature = temp;
}

void Machine::setSeuils(Seuils* seuils)
{
    this->seuils = seuils;
}

void Machine::setVibrations(Vibration *vibrations, string axe)
{
    this->vibrations = vibrations;

    if (axe == "X")
    {
        listeVibrations.at(0) = vibrations;
    }
    else if (axe == "Y")
    {
        listeVibrations.at(1) = vibrations;
    }
    else if (axe == "Z")
    {
        listeVibrations.at(2) = vibrations;
    }
}

void Machine::setLastEvenement(Evenement *evenement)
{
    this->lastEvenement = evenement;
}

/*void Machine::setAmbiance(Ambiance* ambiance)
{
}*/

void Machine::enregistrerTemperature(DatabaseManager *db)
{
    float maximale;
    float moyenne;
    string dateheure;

    maximale = temperature->getMaximale();
    moyenne = temperature->getMoyenne();
    dateheure = temperature->getDateHeure();

    string query = "INSERT INTO Temperature (date, tempMoy, tempMax, id_Machine) VALUES (\'" + dateheure + "\'," + to_string(moyenne) + "," + to_string(maximale) + "," + to_string(numero) + ");";
    // string query = "UPDATE Contexte SET tension1 = " + to_string(Tension_reseau[0]) + ", tension2 = " + to_string(Tension_reseau[1]) + ", tension3 = " + to_string(Tension_reseau[2]) + ", intensite1 = " + to_string(Intensite_reseau[0]) + ", intensite2 = " + to_string(Intensite_reseau[1]) + ", intensite3 = " + to_string(Intensite_reseau[2]) + ", cosPhi1 = " + to_string(FacteurPuissance_reseau[0]) + ", cosPhi2 = " + to_string(FacteurPuissance_reseau[1]) + ", cosPhi3 = " + to_string(FacteurPuissance_reseau[2]) + " WHERE id = (SELECT MAX(id) FROM Contexte);";
    //cout << query << endl;
    db->executerRequete(query);
}

void Machine::enregistrerSeuils(DatabaseManager *db)
{
    float seuilTempMax;
    float seuilTempMoy;
    float seuilAlerteVibX;
    float seuilAlerteVibY;
    float seuilAlerteVibZ;
    float seuilAlarmeVibX;
    float seuilAlarmeVibY;
    float seuilAlarmeVibZ; 

    seuilTempMax = seuils->getTempMax();
    seuilTempMoy = seuils->getTempMoy();
    seuilAlerteVibX = seuils->getSeuilAlerteVibX();
    seuilAlerteVibY = seuils->getSeuilAlerteVibY();
    seuilAlerteVibZ = seuils->getSeuilAlerteVibZ();
    seuilAlarmeVibX = seuils->getSeuilAlarmeVibX();
    seuilAlarmeVibY = seuils->getSeuilAlarmeVibY();
    seuilAlarmeVibZ = seuils->getSeuilAlarmeVibZ();

    string listeSeuilTemp = db->executerRequete(DatabaseDAO::listeSeuilTemp());
    string listeSeuilVibra = db->executerRequete(DatabaseDAO::listeSeuilVibra());

    if (listeSeuilTemp == "")
    {
        string querytemp1 = "INSERT INTO SeuilTemp (tempMax, tempMoy, id_Machine) VALUES (" + to_string(seuilTempMax) + "," + to_string(seuilTempMoy) + "," + to_string(numero) + ");";
        //cout << querytemp1 << endl;
        db->executerRequete(querytemp1);
    }
    else
    {
        // string querytemp = "INSERT INTO SeuilTemp (tempMax, tempMoy, id_Machine) VALUES (" + to_string(seuilTempMax) + "," + to_string(seuilTempMoy) + ");";
        string querytemp2 = "UPDATE SeuilTemp SET tempMax = \'" + to_string(seuilTempMax) + "\', tempMoy = \'" + to_string(seuilTempMoy) + "\', id_Machine = \'" + to_string(numero) + "\';";
        //cout << querytemp2 << endl;
        db->executerRequete(querytemp2);
    }

    if (listeSeuilVibra == "")
    {
        string queryVibra1 = "INSERT INTO SeuilVibra (vibraAlerteX, vibraAlerteY, vibraAlerteZ, vibraAlarmeX, vibraAlarmeY, vibraAlarmeZ, id_Machine) VALUES (" + to_string(seuilAlerteVibX) + "," + to_string(seuilAlerteVibY) + "," + to_string(seuilAlerteVibZ) + "," + to_string(seuilAlarmeVibX) + "," + to_string(seuilAlarmeVibY) + "," + to_string(seuilAlarmeVibZ) + "," + to_string(numero) + ");";
        //string queryVibra1 = "UPDATE SeuilVibra SET vibraAlerteX = " + to_string(seuilAlerteVibX) + ", vibraAlerteY = " + to_string(seuilAlerteVibY) + ", vibraAlerteZ = " + to_string(seuilAlerteVibZ) + ", vibraAlarmeX = " + to_string(seuilAlarmeVibX) + ", vibraAlarmeY = " + to_string(seuilAlarmeVibY) + ", vibraAlarmeZ = " + to_string(seuilAlarmeVibZ) + ";";
        // cout << queryVibra1 << endl;
        db->executerRequete(queryVibra1);
    }
    else
    {
        // string query = "INSERT INTO Contexte (date, tension1, tension2, tension3, intensite1, intensite2, intensite3, cosPhi1, cosPhi2, cosPhi3) VALUES (" + dateHeure + "," + to_string(Tension_reseau[0]) + "," + to_string(Tension_reseau[1]) + "," + to_string(Tension_reseau[2]) + "," + to_string(Intensite_reseau[0]) + "," + to_string(Intensite_reseau[1]) + "," + to_string(Intensite_reseau[2]) + "," + to_string(FacteurPuissance_reseau[0]) + "," + to_string(FacteurPuissance_reseau[1]) + "," + to_string(FacteurPuissance_reseau[2]) + ")";
        string queryVibra2 = "UPDATE SeuilVibra SET vibraAlerteX = \'" + to_string(seuilAlerteVibX) + "\', vibraAlerteY = \'" + to_string(seuilAlerteVibY) + "\', vibraAlerteZ = \'" + to_string(seuilAlerteVibZ) + "\', vibraAlarmeX = \'" + to_string(seuilAlarmeVibX) + "\', vibraAlarmeY = \'" + to_string(seuilAlarmeVibY) + "\', vibraAlarmeZ = \'" + to_string(seuilAlarmeVibZ) + "\', id_Machine = \'" + to_string(numero) + "\';";
        // cout << queryVibra2 << endl;
        db->executerRequete(queryVibra2);
    }
}

void Machine::enregistrerVibrations(DatabaseManager *db)
{
    string axeX, axeY, axeZ;
    float vitesseVibrationX, vitesseVibrationY, vitesseVibrationZ;
    string dateheure;

    dateheure = listeVibrations[0]->getDateheure();
    axeX = listeVibrations[0]->getAxe();
    vitesseVibrationX = listeVibrations[0]->getVitesseVibration();
    axeY = listeVibrations[1]->getAxe();
    vitesseVibrationY = listeVibrations[1]->getVitesseVibration();
    axeZ = listeVibrations[2]->getAxe();
    vitesseVibrationZ = listeVibrations[2]->getVitesseVibration();

    string query = "INSERT INTO Vibrations (date, axeX, axeY, axeZ,  id_Machine) VALUES (\'" + dateheure + "\',\'" + axeX + "\',\'" + axeY + "\',\'" + axeZ + "\',\'" + to_string(numero) + "\')";
    // string query = "UPDATE Contexte SET tension1 = " + to_string(Tension_reseau[0]) + ", tension2 = " + to_string(Tension_reseau[1]) + ", tension3 = " + to_string(Tension_reseau[2]) + ", intensite1 = " + to_string(Intensite_reseau[0]) + ", intensite2 = " + to_string(Intensite_reseau[1]) + ", intensite3 = " + to_string(Intensite_reseau[2]) + ", cosPhi1 = " + to_string(FacteurPuissance_reseau[0]) + ", cosPhi2 = " + to_string(FacteurPuissance_reseau[1]) + ", cosPhi3 = " + to_string(FacteurPuissance_reseau[2]) + " WHERE id = (SELECT MAX(id) FROM Contexte);";
    //cout << query << endl;
    db->executerRequete(query);
}

void Machine::enregistrerEvenement(DatabaseManager *db)
{

    string type = lastEvenement->getType();
    string dateheure = lastEvenement->getDateHeure();

    string query = "INSERT INTO Evenements (date, type, id_Machine) VALUES(\'" + dateheure + "\',\'" + type + "\',\'" + to_string(numero) + "\')";
    // string query = "UPDATE Contexte SET tension1 = " + to_string(Tension_reseau[0]) + ", tension2 = " + to_string(Tension_reseau[1]) + ", tension3 = " + to_string(Tension_reseau[2]) + ", intensite1 = " + to_string(Intensite_reseau[0]) + ", intensite2 = " + to_string(Intensite_reseau[1]) + ", intensite3 = " + to_string(Intensite_reseau[2]) + ", cosPhi1 = " + to_string(FacteurPuissance_reseau[0]) + ", cosPhi2 = " + to_string(FacteurPuissance_reseau[1]) + ", cosPhi3 = " + to_string(FacteurPuissance_reseau[2]) + " WHERE id = (SELECT MAX(id) FROM Contexte);";
    // cout << query << endl;
    db->executerRequete(query);
}

/*void Machine::enregistrerAmbiance(DatabaseManager *db)
{
    float temp;
    float humidite;
    string dateheure;

    temp = ambiance->getTempAmb();
    humidite = ambiance->getHumidite();

    string query = "INSERT INTO Contexte (date, tempAmb, humidite) VALUES(\'" + dateheure + "\'," + to_string(temp) + "," + to_string(humidite) + ",)";
    // string query = "UPDATE Contexte SET tension1 = " + to_string(Tension_reseau[0]) + ", tension2 = " + to_string(Tension_reseau[1]) + ", tension3 = " + to_string(Tension_reseau[2]) + ", intensite1 = " + to_string(Intensite_reseau[0]) + ", intensite2 = " + to_string(Intensite_reseau[1]) + ", intensite3 = " + to_string(Intensite_reseau[2]) + ", cosPhi1 = " + to_string(FacteurPuissance_reseau[0]) + ", cosPhi2 = " + to_string(FacteurPuissance_reseau[1]) + ", cosPhi3 = " + to_string(FacteurPuissance_reseau[2]) + " WHERE id = (SELECT MAX(id) FROM Contexte);";
    cout << query << endl;
    db->executerRequete(query);
}*/
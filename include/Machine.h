#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include "Temperature.h"
#include "Seuils.h"
#include "Vibration.h"
#include "Evenement.h"
#include "Ambiance.h"
#include "DatabaseManager.h"

class Machine
{
private:

    Temperature* temperature;
    Seuils* seuils;
    Ambiance* ambiance;
    vector<Vibration*> listeVibrations;
    Vibration* vibrations;
    Evenement *lastEvenement;

    int numero;
    bool apprentissageTermineTemp;
    bool apprentissageTermineVibra;


public:

    Machine(int numero);

    // Getters
    int getNumero();
    bool getApprentissageTermineTemp();
    bool getApprentissageTermineVibra();
    Temperature *getTemperature();
    Seuils* getSeuils();
    Vibration* getVibrations(string axe); 
    Evenement *getLastEvenement();

    // Setters
    void setApprentissageTermineTemp(bool apprentissageTermineTemp);
    void setApprentissageTermineVibra(bool apprentissageTermineVibra);
    void setTemperature(Temperature* temp);
    void setSeuils(Seuils* seuils);
    void setVibrations( Vibration* vibration, string axe);
    void setLastEvenement(Evenement* evenement);
    void setAmbiance(Ambiance* ambiance);

    // Méthodes d'enregistrement
    void enregistrerTemperature(DatabaseManager* db);
    void enregistrerSeuils(DatabaseManager* db);
    void enregistrerVibrations(DatabaseManager* db);
    void enregistrerEvenement(DatabaseManager* db);
    void enregistrerAmbiance(DatabaseManager* db);
};

#endif // MACHINE_H

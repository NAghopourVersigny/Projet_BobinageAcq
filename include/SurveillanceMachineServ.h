#ifndef SURVEILLANCE_MACHINE_SERV_H
#define SURVEILLANCE_MACHINE_SERV_H

#include <iostream>
#include "MQTT.h"
#include "Ambiance.h"
#include "EtatReseau.h"
#include "DatabaseManager.h"

using namespace std; 

class SurveillanceMachine {
    private : 

    MQTTClient laCommunication;
    DatabaseManager* base;
    Ambiance ambiance;
    EtatReseau etatReseau;
    //Machine* listeMachines;

    public :

    SurveillanceMachine();
    ~SurveillanceMachine();

    void gererReceptionTemperature();
    void gererReceptionSeuils();

    void gererEtatApprentissage();

    void enregistrerAmbiance(DatabaseManager* base);
    void enregistrerEvenement(DatabaseManager* base);

    void setEtatReseau(EtatReseau etatReseau);

    void publierSeuils(int machineId, float seuils);
    void publierApprentissage();

    void modifierTemperature(int numMachine);

    string releverDateTime();

    void reprendreDerniereDonneesTemp();

    void modifierEvenement(int numMachine);
};

#endif
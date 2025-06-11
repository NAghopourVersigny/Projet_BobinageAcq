#include <exception>
#include <string>
#include <vector>
using namespace std;

#ifndef __SurveillanceMachineServ_h__
#define __SurveillanceMachineServ_h__

#include "MQTTClient.h"
#include "DatabaseManager.h"
#include "Ambiance.h"
#include "EtatReseau.h"
#include "Machine.h"
#include "Apprentissage.h"
#include "MQTTTopics.h"

class MQTTClient; // déclaration anticipée car, dans le cas d'une association, il y en a un qui existe avant l'autre.


class SurveillanceMachineServ
{
	private: MQTTClient * laCommunication;
	private: DatabaseManager* db;
	private: Ambiance * ambiance;
	private: EtatReseau * etatReseau;
	private: std::vector<Machine*> listeMachines;
    private: MQTTClient * client;

	public: SurveillanceMachineServ(MQTTClient* client);

	public: void gererReceptionTemperature(string payload, int numeroMachine);

	public: void gererReception(const std::string& topic, const std::string& payload);	

	public: void gererReceptionVibrations(string payload, int numeroMachine);

    public: void gererReceptionTemperatureAlerte(string payload, int numeroMachine);

    public: void gererReceptionVibrationsAlerte(string payload, int numeroMachine);

	public: void gererEtatApprentissage(string payload, int numeroMachine);

	public: void enregistrerAmbiance(DatabaseManager* db, int numeroMachine);

	public: void enregistrerEvenement(DatabaseManager* db, int numeroMachine);

	public: void setEtatReseau(EtatReseau* etatReseau);

	public: void setAmbiance(Ambiance* ambiance);

	public: void gererReceptionSeuils(string payload, int numeroMachine);

	public: void publierSeuils(int machineId, string seuils);

	public: void publierApprentissage(int machineId, Apprentissage apprentissage);

	public: void modifierTemperature(int numMachine);

	public: void releverDateTime();

	public: void reprendreDerniereDonnéesTemp();

	public: void modifierEvenement(int numMachine);
};

#endif

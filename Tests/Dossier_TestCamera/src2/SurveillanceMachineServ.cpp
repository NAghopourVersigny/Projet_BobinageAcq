#include <exception>
#include <sstream>

#include <iostream>

using namespace std;

#include "../include/SurveillanceMachineServ.h"
#include "../include/MQTTTopics.h"
#include "../include/DatabaseDAO.h"

SurveillanceMachineServ::SurveillanceMachineServ(MQTTClient *client)
{
	laCommunication = client;
	db = new DatabaseManager();
	ambiance = new Ambiance();
	etatReseau = new EtatReseau();
	string listeDeMachines = db->executerRequete(DatabaseDAO::listeMachines());
	if (listeDeMachines == "")
		for (int i = 1; i <= 3; i++)
		{
			db->executerRequete(DatabaseDAO::creationMachineDefaut(i, "bobinage"));
		}

	for (int i = 1; i <= 3; i++)
	{
		listeMachines.push_back(new Machine(i));
	}
	vector<string> lesTopics;
	lesTopics.push_back(MQTTTopics::temperatureTopic());
	lesTopics.push_back(MQTTTopics::temperatureAlerteTopic());
	lesTopics.push_back(MQTTTopics::vibrationsTopic());
	lesTopics.push_back(MQTTTopics::vibrationsAlerteTopic());
	lesTopics.push_back(MQTTTopics::acquisitionTopic());

	// client->setCallbackHandler(&this);
	client->connect();
	client->subscribe(lesTopics);
}

void SurveillanceMachineServ::gererReceptionTemperature(string payload, int numeroMachine)
{
	client->subscribe("ecei/+/temperature/valeurs", payload);
}

void SurveillanceMachineServ::gererReception(const std::string &topic, const std::string &payload)
{
	int numero = topic.find("machine");
	if (numero != string::npos)
	{
		string newTopic = topic.substr(numero);
		numero = newTopic.find("e");
		if (numero != string::npos)
		{
			newTopic = newTopic.substr(numero + 1, 1);
			istringstream(newTopic) >> numero;
			if ((numero >= 1) && (numero <= 3))
				if (topic.find("/temperature/valeurs") != std::string::npos)
				{
					gererReceptionTemperature(payload, numero);
				}
				else if (topic.find("/temperature/alerte") != std::string::npos)
				{
					gererReceptionTemperatureAlerte(payload, numero);
				}
				else if (topic.find("/vibration/valeurs") != std::string::npos)
				{
					gererReceptionVibrations(payload, numero);
				}
				else if (topic.find("/vibration/alerte") != std::string::npos)
				{
					gererReceptionVibrationsAlerte(payload, numero);
				}
				else if (topic.find("/commande/apprentissage") != std::string::npos)
				{
					gererEtatApprentissage(payload, numero);
				}
				else if (topic.find("/config/seuils/") != std::string::npos)
				{
					gererReceptionSeuils(payload, numero);
				}
		}
	}
}

void SurveillanceMachineServ::gererReceptionVibrations(string payload, int numeroMachine)
{
	client->subscribe("ecei/+/vibrations/valeurs", payload);
}


void SurveillanceMachineServ::gererEtatApprentissage(string payload, int numeroMachine)
{
	cout << " Serveur a reçu l'état d'apprentissage : " << payload << "pour la machine n°" << numeroMachine << endl;
}

void SurveillanceMachineServ::gererReceptionTemperatureAlerte(string payload, int numeroMachine)
{
	client->subscribe("ecei/+/temperature/alerte", payload);
}

void SurveillanceMachineServ::gererReceptionVibrationsAlerte(string payload, int numeroMachine)
{
	client->subscribe("ecei/+/vibrations/alerte", payload);
	client->subscribe("ecei/+/vibrations/alerte", payload);
	client->subscribe("ecei/+/vibrations/alerte", payload);
}

void SurveillanceMachineServ::enregistrerAmbiance(DatabaseManager *db, int numeroMachine)
{
	throw "Not yet implemented";
}

void SurveillanceMachineServ::enregistrerEvenement(DatabaseManager *db, int numeroMachine)
{
	throw "Not yet implemented";
}

void SurveillanceMachineServ::setEtatReseau(EtatReseau *etatReseau)
{
	this->etatReseau = etatReseau;
}

void SurveillanceMachineServ::setAmbiance(Ambiance *ambiance)
{
	this->ambiance = ambiance;
}

void SurveillanceMachineServ::gererReceptionSeuils(string payload, int numeroMachine)
{
	client->subscribe("ecei/+/config/seuils", payload);
}

void SurveillanceMachineServ::publierSeuils(int machineId, string seuils)
{
    string payload = createAcquisitionJson(45.0 + i, 65.0 + i);
    client->publish("ecei/+/config/seuils", payload);
      
}

void SurveillanceMachineServ::publierApprentissage(int machineId, Apprentissage apprentissage)
{
	// Récupération de l'heure actuelle pour horodatage
    time_t maintenant = time(nullptr);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&maintenant));

    ostringstream oss;
    oss << "{\"vibration\": \"" << """" << "\","
        << "\"dureeApprentissageVib\": " << "" << ", "
        << "\"coeffVibAlerte\": " << "" << ", "
        << "\"coeffVibAlarme\": " << "" <<  "}";
    return oss.str();

		// Récupération de l'heure actuelle pour horodatage
    time_t maintenant = time(nullptr);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&maintenant));

    ostringstream oss;
    oss << "{\"temperature\": \"" << """" << "\","
        << "\"dureeApprentissageTemp\": " << "" << ", "
        << "\"coeffTemp\": " << "" <<  "}";
    return oss.str();


	string payload = createApprentissageSeuilsTempJson();
	client->publish("ecei/+/commande/apprentissage", payload);

		
	string payload = createApprentissageSeuilsVibraJson();
	client->publish("ecei/+/commande/apprentissage", payload);
		
}

void SurveillanceMachineServ::modifierTemperature(int numMachine)
{
	throw "Not yet implemented";
}

void SurveillanceMachineServ::releverDateTime()
{
	throw "Not yet implemented";
}

void SurveillanceMachineServ::reprendreDerniereDonnéesTemp()
{
	throw "Not yet implemented";
}

void SurveillanceMachineServ::modifierEvenement(int numMachine)
{
	throw "Not yet implemented";
}

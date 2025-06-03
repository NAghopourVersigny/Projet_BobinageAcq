#ifndef BDD_H
#define BDD_H
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <mariadb/conncpp.hpp>
#include <thread>
#include <iomanip>        // std::put_time
#include <chrono>         // std::chrono::system_clock

#include "../include/Temperature.h"
#include "../include/Vibration.h"
#include "../include/Contexte.h"
#include "../include/Evenement.h"
#include "../include/Image.h"
#include "../include/Apprentissage.h"

using namespace std;
using namespace sql;
using std::chrono::system_clock;


class Base
{

private:
	Connection *connec;

public:
	Base();
	~Base();
	// obtenir valeurs
	list<Temperature> *obtenirDataFonctTemp(string dateDebut, string dateFin, int idMachine);

	list<Vibration> *obtenirDataFonctVibra(string dateDebut, string dateFin, int idMachine);

	list<Contexte> *obtenirDataCont(string dateDebut, string dateFin);

	list<Evenement> *obtenirListeEven(string dateDebut, string dateFin, int idMachine);
	
	list<Image> *obtenirImage(string dateDebut, string dateFin, int idMachine);

	void obtenirSeuilTemp(float &tempMax, float &tempMoy, int idMachine);

	void obtenirSeuilVibra(float &vibraMaxX, float &vibraMaxY, float &vibraMaxZ, int idMachine);

	bool obtenirApprentissageTemp( int idMachine);

	// ajouter valeurs
	int ajouterDataFonctTemp(string date, float tempMachine, int idMachine);

	int ajouterDataFonctVibra(string date, string axe, float asymetrie, float moyenne, float aplatissement, float dispersion, float efficace, float min, float max, int idMachine);

	int ajouterDataCont(string date, float tempAmb, float humidite, float tension_reseau);

	int ajouterImage(string date, string nom, string type, int idEven);

	int ajouterSeuilTemp(float tempMax, float tempMoy, int idMachine);

	int ajouterSeuilVibra(float vibraMaxX, float vibraMaxY, float vibraMaxZ, int idMachine);
	
	int ajouterListeEven(string date, string type, Temperature* tempe, Contexte* contexte, Image* image,  int idMachine = 1);

	bool terminerApprentissageTemp(int idMachine);

	// json
	string mettreEnForme(list<Temperature>);

	// supprimer valeurs
	void supprimer(); //void comme paramètre


	thread renvoie_supprimer();






	Connection* getConnection();
	
};

#endif

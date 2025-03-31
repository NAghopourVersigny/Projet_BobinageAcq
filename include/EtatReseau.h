#ifndef ETATRESEAU_H
#define ETATRESEAU_H

#include <iostream>
#include "serialib.h"
#include <cstring>
#include <stdlib.h>
#include <sstream>
#include <iomanip>

using namespace std;

#define SERIAL_DEV "/dev/ttyUSB0" /*Chemin d'arborescence du port*/
#define REGISTER 0x0000           /*Addresse du registre qu'on cherche*/
#define CODE_FUNCTION 0x03 /*Lecture de n registres (mots) de maintien consécutifs*/

/*Les codes d'erreurs afin de recommencer la procédure en cas de problème*/
#define CODE_3RR0R_ACCES -1
#define CODE_3RR0R_TRANS -2
#define CODE_3RROR_RESP -3
#define CODE_3RR0R_TENSION -10

class EtatReseau {

private:
	//Variable
	float Tension;
	bool etat;
	string hostIP;
    string username;
    string password;
	unsigned char registre;
	unsigned char requete[8]; //{ADDRESS, CODE_FUNCTION, REGISTER, 0x00, 0x00, 0x01}; 
    unsigned char reponse[11];
	short detrame[2];
    int Err;
    serialib * serial;

	
	
	//Methode
	int ouvrir_acces();
	void calculer_CRC();
	int transmettre_Requete();
	void construire_trame();
	int traiter_reponse();
	short detramer();
	bool verifier_crc();
	int calculerTension();
	void fermer_port();

public:
	EtatReseau();

	~EtatReseau();

	int relever_Tension();

	float get_tension();
};

#endif

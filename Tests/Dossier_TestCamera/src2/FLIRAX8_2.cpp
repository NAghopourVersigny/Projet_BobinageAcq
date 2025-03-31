#include "../include/FLIRAX8.h"

FLIR_AX8::FLIR_AX8(string hostname)
{
	string ip = resolveHostname(hostname);
	mb = new modbus(ip, 502);
	mb->modbus_connect();
}

int FLIR_AX8::ConnectionFLIR_AX8()
{
	string chemin_sshpass = "/usr/bin/sshpass"; //chemin absolue
	string composite =chemin_sshpass + " -p 3vlig ssh fliruser@neco-10655D.local";
    int status = system(composite.c_str());
    if (status != 0) 
	{
		cout << "Echec de la connexion" <<endl;
        return -1; // Échec de la connexion
    } else cout << "Connexion réussie" << endl;
    return 0; // Connexion réussie
}

/***
 * Attention ! La clé ssh de la caméra doit, au préalable, avoir été ajoutée à la liste des hôtes connus
 * en faisant une connexion ssh par exemple
 * Faire en sudo... pour la suite (tous les utilisateurs doivent avoir la clé)
*/
int FLIR_AX8::requerir_Image()
{
 	Username = "fliruser";
	hostIP = "neco-10655D.local";
	chemin = "/var/www/html/img/";
	std::string composite = "sshpass -p 3vlig scp -o StrictHostKeyChecking=no " + Username + "@" + hostIP + ":/FLIR/system/images/""*.jpg " + chemin;
	strcpy(command, composite.c_str());

	
	int reussi = system(command);
	if (reussi == 0)
	{
		return 0;
	}
	else
	{
		return -1;
	} 
}

void FLIR_AX8::store_Image()
{
	mb->modbus_set_slave_id(SLAVE_ID_IMAGE);
	mb->modbus_write_registers(REGISTER_STORE_IMAGE, 1, &execute);
}

float FLIR_AX8::acquerirTempMoy()
{
	uint16_t tempmoy[2];
	int valeur;
	mb->modbus_set_slave_id(SLAVE_ID_BASIC);
	mb->modbus_read_holding_registers(AVERAGE_TEMP, 2, tempmoy);
	valeur = (tempmoy[1] << 16) + tempmoy[0];
	return valeur;
}

float FLIR_AX8::acquerirTempMax()
{
	uint16_t tempMax[2];
	int valeur;
	mb->modbus_set_slave_id(SLAVE_ID_BASIC);
	mb->modbus_read_holding_registers(MAXIMUM_TEMP, 2, tempMax);
	valeur = tempMax[1];
	valeur = (valeur<< 16) + tempMax[0];
	
	return valeur;
}

float FLIR_AX8::acquerirTempMin()
{
	uint16_t tempMin[2];
	int valeur;

	mb->modbus_set_slave_id(SLAVE_ID_BASIC);
	mb->modbus_read_holding_registers(MIMINUM_TEMP, 2, tempMin);
	valeur = (tempMin[1] << 16) + tempMin[0];
	return valeur;
}

//Méthode incomplète
int FLIR_AX8::mettre_visible()
{
	uint16_t test[20];
	uint16_t normal = 0;
	uint16_t reserve = 1;
	uint16_t span[2];
	uint16_t level[2];

	mb->modbus_set_slave_id(1);
	int val = mb->modbus_read_holding_registers(0,1,span);
	cout << span[0] << endl;
	if(val ==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	/*mb->modbus_read_holding_registers(4001,20,test);
	cout << "Lecture champ: ";
	for(int i=0; i < 20; i ++)
	{
		cout << test[i] << '\t';
	}
	cout << endl;*/
	/*mb->modbus_read_holding_registers(4121,2,span);
	cout << "span: ";
	cout << span[0] << '\t'<< span[1];
	cout << endl;

	mb->modbus_read_holding_registers(4141,2,level);
	cout << "level: ";
	cout << level[0]<< '\t' << level[1];
	cout << endl;

	mb->modbus_read_holding_registers(4061,3,test);
	for(int i=0; i < 3; i ++)
	{
		cout << test[i] << '\t';
	}
	cout << endl;
	test[0] = 0x4D61;
	test[1] = 0x6E75;
	test[2] = 0x616C;
	mb->modbus_write_registers(4061,3,test); //4D 61 6E 75 61 6C*/
	
	/*mb->modbus_write_registers(4121,2,&normal); //Span
	mb->modbus_write_registers(4141,2,&normal); //Level*/
}


//Impossible raison on a pas les permissions
int FLIR_AX8::supprimer_image()
{
/* 	sleep(5);
	composite ="sshpass -p hello ssh root@neco-10655D.local rm -f /FLIR/system/images/" +"*.jpg";
	system(composite.c_str()); */
	return 0;
}

bool FLIR_AX8::alarme()
{
	uint16_t Rep[1];
	mb->modbus_set_slave_id(106);
	mb->modbus_read_holding_registers(4001,1,Rep);
	return Rep;
}

string FLIR_AX8::resolveHostname(const std::string &hostname)
{
	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET; // or AF_INET6 to force version
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(hostname.c_str(), NULL, &hints, &res)) != 0)
	{
		cerr << "getaddrinfo: " << gai_strerror(status) << std::endl;
		return "";
	}

	for (p = res; p != NULL; p = p->ai_next)
	{
		void *addr;
		if (p->ai_family == AF_INET)
		{
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
			addr = &(ipv4->sin_addr);
		}
		else
		{
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
			addr = &(ipv6->sin6_addr);
		}

		// convertir l'adresse IP en une chaîne lisible
		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
	}

	freeaddrinfo(res); // libérer la mémoire réservée pour les résultats

	return ipstr;
}


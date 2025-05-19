#include "../include/FLIRAX8.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"

using Poco::Net::StreamSocket;

FLIR_AX8::FLIR_AX8(string hostname)
{
	string ip = resolveHostname(hostname);
	mb = new modbus(ip, 502);
}

void FLIR_AX8::Connection_Modbus()
{
	mb->modbus_connect();
}

void FLIR_AX8::Deconnection_Modbus()
{
	mb->modbus_close();
}

/***
 * Attention ! La clé ssh de la caméra doit, au préalable, avoir été ajoutée à la liste des hôtes connus
 * en faisant une connexion ssh par exemple
 * Faire en sudo... pour la suite (tous les utilisateurs doivent avoir la clé)
*/
int FLIR_AX8::setVisionMode(int mode) {
    // mode = 0 pour visuel, 1 pour thermique
    const uint16_t registre_mode = 4001; // À remplacer par le bon registre

    mb->modbus_set_slave_id(104); // Adapter l'ID esclave

    if (mb->modbus_write_register(registre_mode, mode) == -1) {
        cout << "Erreur : Impossible d’écrire le mode." << endl;
        return -1;
    }

    usleep(200000); // Attente de 200ms

    uint16_t confirmation;
    if (mb->modbus_read_holding_registers(registre_mode, 1, &confirmation) == -1) {
        cout << "Erreur : Lecture du registre après écriture échouée." << endl;
        return -1;
    }

    return (confirmation == mode) ? 0 : -1;
}


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

void FLIR_AX8::set_image_mode(int mode) {
    // Adresse de la caméra (changer l'IP si nécessaire)
    string server = "10.119.1.19";  // Remplacez par l'IP de votre caméra
    int port = 44818; // Port EtherNet/IP par défaut pour les appareils FLIR

    uint8_t preambule[] = {0x35, 0x70, 0x01};

    // Données pour chaque mode (IR, Visual, etc.)
    uint8_t data_ir_1[] = { 
        0x2a, 0x2e, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x2e, 0x73, 0x79, 0x73, 0x69, 0x6d, 0x67, 0x2e, 0x66, 0x75, 
        0x73, 0x69, 0x6f, 0x6e, 0x2e, 0x66, 0x75, 0x73, 0x69, 0x6f, 0x6e, 0x44, 0x61, 0x74, 0x61, 0x2e, 0x66, 
        0x75, 0x73, 0x69, 0x6f, 0x6e, 0x4d, 0x6f, 0x64, 0x65, 0x01, 0x00, 0x00, 0x00
    };

    uint8_t data_ir_2[] = { 
        0x2c, 0x2e, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x2e, 0x73, 0x79, 0x73, 0x69, 0x6d, 0x67, 0x2e, 0x66, 0x75, 
        0x73, 0x69, 0x6f, 0x6e, 0x2e, 0x66, 0x75, 0x73, 0x69, 0x6f, 0x6e, 0x44, 0x61, 0x74, 0x61, 0x2e, 0x75, 
        0x73, 0x65, 0x4c, 0x65, 0x76, 0x65, 0x6c, 0x53, 0x70, 0x61, 0x6e, 0x01, 0x00, 0x00, 0x00
    };

    uint8_t data_visual_1[] = { 
        0x2a, 0x2e, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x2e, 0x73, 0x79, 0x73, 0x69, 0x6d, 0x67, 0x2e, 0x66, 0x75, 
        0x73, 0x69, 0x6f, 0x6e, 0x2e, 0x66, 0x75, 0x73, 0x69, 0x6f, 0x6e, 0x44, 0x61, 0x74, 0x61, 0x2e, 0x66, 
        0x75, 0x73, 0x69, 0x6f, 0x6e, 0x4d, 0x6f, 0x64, 0x65, 0x01, 0x00, 0x00, 0x00
    };

    uint8_t data_visual_2[] = { 
        0x2c, 0x2e, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x2e, 0x73, 0x79, 0x73, 0x69, 0x6d, 0x67, 0x2e, 0x66, 0x75, 
        0x73, 0x69, 0x6f, 0x6e, 0x2e, 0x66, 0x75, 0x73, 0x69, 0x6f, 0x6e, 0x44, 0x61, 0x74, 0x61, 0x2e, 0x75, 
        0x73, 0x65, 0x4c, 0x65, 0x76, 0x65, 0x6c, 0x53, 0x70, 0x61, 0x6e, 0x00, 0x00, 0x00, 0x00
    };

    // Créer une connexion socket avec la caméra FLIR via EtherNet/IP
    Poco::Net::SocketAddress address(server, port);
    Poco::Net::StreamSocket socket(address);

     auto send_with_preambule = [&](uint8_t* data, size_t data_len) {
        std::vector<uint8_t> buffer(sizeof(preambule) + data_len);
        memcpy(buffer.data(), preambule, sizeof(preambule));
        memcpy(buffer.data() + sizeof(preambule), data, data_len);
        socket.sendBytes(buffer.data(), buffer.size());
    };

    switch (mode) {
        case 1: // Mode IR
            send_with_preambule(data_ir_1, sizeof(data_ir_1));
            send_with_preambule(data_ir_2, sizeof(data_ir_2));
            break;
        case 2: // Mode Visual
            send_with_preambule(data_visual_1, sizeof(data_visual_1));
            send_with_preambule(data_visual_2, sizeof(data_visual_2));
            break;
        default:
            std::cout << "Mode non valide!" << std::endl;
            break;
    }
/*
    // Sélectionner le mode à utiliser et envoyer les données correspondantes
    switch (mode) {
        case 1: // Mode IR
            socket.sendBytes(préambule, sizeof(préambule));
            socket.sendBytes(data_ir_1, sizeof(data_ir_1));  // Envoi des données pour le mode IR
            socket.sendBytes(data_ir_2, sizeof(data_ir_2));  // Envoi des données supplémentaires pour le mode IR
            break;
        case 2: // Mode Visual
            socket.sendBytes(préambule, sizeof(préambule));
            socket.sendBytes(data_visual_1, sizeof(data_visual_1));  // Envoi des données pour le mode Visual
            socket.sendBytes(data_visual_2, sizeof(data_visual_2));  // Envoi des données supplémentaires pour le mode Visual
            break;
        default:
            cout << "Mode non valide!" << endl;
            break;
    }*/
}

/* v4
int FLIR_AX8::enableThermalMode() {
    uint16_t mode_value = 0x01;  // Valeur pour le mode thermique
    uint16_t registre_mode = 4001; // Adresse du registre Mode d'Image

    mb->modbus_set_slave_id(104); // Assurez-vous que l'ID de l'esclave est correct

    // Lire la valeur actuelle du registre Mode d'image
    uint16_t current_value;
    if (mb->modbus_read_holding_registers(registre_mode, 1, &current_value) == -1) {
        cout << "Erreur : Impossible de lire le registre Mode d'Image." << endl;
        return -1;
    }

    // Écrire la nouvelle valeur pour le mode thermique
    if (mb->modbus_write_register(registre_mode, mode_value) == -1) {
        cout << "Erreur : Impossible d'écrire dans le registre Mode." << endl;
        return -1;
    }

    // Attente et vérification
    usleep(200000);
    if (mb->modbus_read_holding_registers(registre_mode, 1, &current_value) == -1) {
        cout << "Erreur : Impossible de relire le registre Mode après écriture." << endl;
        return -1;
    }

    if (current_value == mode_value) {
        cout << "Mode thermique activé avec succès." << endl;
        return 1;
    } else {
        cout << "Erreur : Le changement de mode thermique a échoué." << endl;
        return -1;
    }
}

int FLIR_AX8::enableVisualMode() {
    uint16_t mode_value = 0x01;  // Valeur pour le mode visuel
    uint16_t registre_mode = 4001; // Adresse du registre Mode d'Image

    mb->modbus_set_slave_id(104);

    uint16_t current_value;
    if (mb->modbus_read_holding_registers(registre_mode, 1, &current_value) == -1) {
        cout << "Erreur : Impossible de lire le registre Mode d'Image." << endl;
        return -1;
    }

    if (mb->modbus_write_register(registre_mode, mode_value) == -1) {
        cout << "Erreur : Impossible d'écrire dans le registre Mode." << endl;
        return -1;
    }

    usleep(200000);
    if (mb->modbus_read_holding_registers(registre_mode, 1, &current_value) == -1) {
        cout << "Erreur : Impossible de relire le registre Mode après écriture." << endl;
        return -1;
    }

    if (current_value == mode_value) {
        cout << "Mode visuel activé avec succès." << endl;
        return 1;
    } else {
        cout << "Erreur : Le changement de mode visuel a échoué." << endl;
        return -1;
    }
}
*/


/*v1
int FLIR_AX8::toggle_IsothermEnable() {
    uint16_t isotherm_value;
    uint16_t registre_isotherm = 4001;  // Remplace par l'adresse correcte du registre "Isotherm Enable"

    mb->modbus_set_slave_id(1); // Assurez-vous que l'ID de l'esclave est correct

    // Lire la valeur actuelle
    if (mb->modbus_read_holding_registers(registre_isotherm, 1, &isotherm_value) == -1) {
        cout << "Erreur : Impossible de lire le registre Isotherm Enable." << endl;
        return -1;
    }
    cout << "Valeur actuelle du registre Isotherm Enable : " << isotherm_value << endl;

    // Inverser la valeur (0 -> 1 ou 1 -> 0)
    uint16_t nouvelle_valeur = (isotherm_value == 0) ? 1 : 0;

    // Écrire la nouvelle valeur
    if (mb->modbus_write_register(registre_isotherm, nouvelle_valeur) == -1) {
        cout << "Erreur : Impossible d'écrire dans le registre Isotherm Enable." << endl;
        return -1;
    }
    cout << "Nouvelle valeur écrite : " << nouvelle_valeur << endl;

    // Vérifier si l'écriture a bien eu lieu
    if (mb->modbus_read_holding_registers(registre_isotherm, 1, &isotherm_value) == -1) {
        cout << "Erreur : Impossible de relire le registre après écriture." << endl;
        return -1;
    }
    cout << "Valeur après écriture : " << isotherm_value << endl;

    return 1;
}*/

/* v3
int FLIR_AX8::toggle_IsothermEnable() {
    uint16_t isotherm_value;
    uint16_t registre_isotherm = 4001; // L'adresse correcte du registre Isotherm Enable

    mb->modbus_set_slave_id(104); // Assurez-vous que l'ID de l'esclave est correct

    // Lire la valeur actuelle du registre Isotherm
    if (mb->modbus_read_holding_registers(registre_isotherm, 1, &isotherm_value) == -1) {
        cout << "Erreur : Impossible de lire le registre Isotherm Enable." << endl;
        return -1;
    }
    cout << "Valeur actuelle du registre Isotherm Enable : " << isotherm_value << endl;

    // Inverser la valeur (0 -> 1 ou 1 -> 0)
    uint16_t nouvelle_valeur = (isotherm_value == 0) ? 1 : 0;

    // Écrire la nouvelle valeur dans le registre
    if (mb->modbus_write_register(registre_isotherm, nouvelle_valeur) == -1) {
        cout << "Erreur : Impossible d'écrire dans le registre Isotherm Enable." << endl;
        return -1;
    }
    cout << "Nouvelle valeur écrite : " << nouvelle_valeur << endl;

    // Attente pour s'assurer que la caméra a pris en compte le changement
    usleep(200000); // Attente de 200ms, ajustez si nécessaire

    // Vérifier si l'écriture a bien eu lieu en relisant le registre
    if (mb->modbus_read_holding_registers(registre_isotherm, 1, &isotherm_value) == -1) {
        cout << "Erreur : Impossible de relire le registre après écriture." << endl;
        return -1;
    }

    cout << "Valeur après écriture : " << isotherm_value << endl;

    // Ajouter un contrôle supplémentaire pour confirmer le changement de mode
    if (isotherm_value == nouvelle_valeur) {
        cout << "Mode modifié avec succès." << endl;
        return 1;
    } else {
        cout << "Erreur : Le changement de mode a échoué." << endl;
        return -1;
    }
}
*/


/* v2
int FLIR_AX8::toggle_IsothermEnable() {
    uint16_t isotherm_value;
    uint16_t registre_isotherm = 6; // Remplace par l'adresse correcte du registre "Isotherm Enable"

    mb->modbus_set_slave_id(1); // Assurez-vous que l'ID de l'esclave est correct

    // Lire la valeur actuelle
    if (mb->modbus_read_holding_registers(registre_isotherm, 1, &isotherm_value) == -1) {
        cout << "Erreur : Impossible de lire le registre Isotherm Enable." << endl;
        return -1;
    }
    cout << "Valeur actuelle du registre Isotherm Enable : " << isotherm_value << endl;

    // Inverser la valeur (0 -> 1 ou 1 -> 0)
    uint16_t nouvelle_valeur = (isotherm_value == 0) ? 1 : 0;

    // Écrire la nouvelle valeur
    if (mb->modbus_write_register(registre_isotherm, nouvelle_valeur) == -1) {
        cout << "Erreur : Impossible d'écrire dans le registre Isotherm Enable." << endl;
        return -1;
    }
    cout << "Nouvelle valeur écrite : " << nouvelle_valeur << endl;

    // Attente pour s'assurer que la valeur est bien prise en compte
    usleep(100000); // Pause de 100ms

    // Vérifier si l'écriture a bien eu lieu
    if (mb->modbus_read_holding_registers(registre_isotherm, 1, &isotherm_value) == -1) {
        cout << "Erreur : Impossible de relire le registre après écriture." << endl;
        return -1;
    }
    cout << "Valeur après écriture : " << isotherm_value << endl;

    return 1;
}


//Méthode incomplète
/*int FLIR_AX8::mettre_visible()
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
	mb->modbus_write_registers(4141,2,&normal); //Level

*/

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
#include <curl/curl.h>
#include <string>
#include <iostream>
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

size_t FLIR_AX8::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

CURLcode FLIR_AX8::perform_request(const string& url, const string& username, const string& password, string& response, bool isPost, const string& postData) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        cout << "Erreur d'initialisation de CURL" << endl;
        return CURLE_FAILED_INIT;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_USERPWD, (username + ":" + password).c_str());  // Authentification
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    // Si on utilise POST
    if (isPost) {
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");  // Lire les cookies
    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");  // Sauvegarder les cookies

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        cout << "Erreur CURL : " << curl_easy_strerror(res) << endl;
    }

    curl_easy_cleanup(curl);
    return res;
}

string FLIR_AX8::get_image_mode() {
    string response;
    string url = "http://neco-10655d.local/home/getviewmode";

    CURLcode res = perform_request(url, "admin", "admin", response);
    if (res == CURLE_OK) {
        // Nettoyage retour
        response.erase(remove(response.begin(), response.end(), '\n'), response.end());
        return response;
    } else {
        return "";
    }
}

void FLIR_AX8::set_image_mode_IR() {
    string response;
    string url = "http://neco-10655d.local/home/setviewmode/IR";

    CURLcode res = perform_request(url, "admin", "admin", response);
    if (res == CURLE_OK) {
        cout << "Mode changé vers IR" << endl;
    } else {
        cout << "Erreur lors du changement vers IR" << endl;
    }
}

void FLIR_AX8::set_image_mode_VISUAL() {
    string response;
    string url = "http://neco-10655d.local/home/setviewmode/VISUAL";

    CURLcode res = perform_request(url, "admin", "admin", response);
    if (res == CURLE_OK) {
        cout << "Mode changé vers VISUAL" << endl;
    } else {
        cout << "Erreur lors du changement vers VISUAL" << endl;
    }
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


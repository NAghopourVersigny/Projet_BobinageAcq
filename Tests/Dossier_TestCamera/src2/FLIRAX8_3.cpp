#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <curl/curl.h>
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
	std::string composite = "sshpass -p 3vlig scp -o StrictHostKeyChecking=no " + Username + "@" + hostIP + ":/FLIR/system/images/"
																											"*.jpg " +
							chemin;
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
	uint16_t execute = 1;
	mb->modbus_connect();
	mb->modbus_set_slave_id(SLAVE_ID_IMAGE);
	mb->modbus_write_registers(REGISTER_STORE_IMAGE, 1, &execute);
	mb->modbus_close();
}

float FLIR_AX8::acquerirTempMoy()
{
	mb->modbus_connect();
	uint16_t tempmoy[2];
	int valeur;
	mb->modbus_set_slave_id(SLAVE_ID_BASIC);
	mb->modbus_read_holding_registers(AVERAGE_TEMP, 2, tempmoy);
	valeur = (tempmoy[1] << 16) + tempmoy[0];
	mb->modbus_close();
	return valeur;
}

float FLIR_AX8::acquerirTempMax()
{
	mb->modbus_connect();
	uint16_t tempMax[2];
	int valeur;
	mb->modbus_set_slave_id(SLAVE_ID_BASIC);
	mb->modbus_read_holding_registers(MAXIMUM_TEMP, 2, tempMax);
	valeur = tempMax[1];
	valeur = (valeur << 16) + tempMax[0];
	mb->modbus_close();
	return valeur;
}

float FLIR_AX8::acquerirTempMin()
{
	mb->modbus_connect();
	uint16_t tempMin[2];
	int valeur;

	mb->modbus_set_slave_id(SLAVE_ID_BASIC);
	mb->modbus_read_holding_registers(MIMINUM_TEMP, 2, tempMin);
	valeur = (tempMin[1] << 16) + tempMin[0];
	mb->modbus_close();
	return valeur;
}

size_t FLIR_AX8::WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output)
{
	size_t totalSize = size * nmemb;
	output->append((char *)contents, totalSize);
	return totalSize;
}

size_t FLIR_AX8::write_to_string(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total_size = size * nmemb;
    ((std::string*)userp)->append((char*)contents, total_size);
    return total_size;
}

size_t FLIR_AX8::write_to_file(void *ptr, size_t size, size_t nmemb, void *stream) {
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
    return written;
}

int FLIR_AX8::set_image_mode_IR()
{

	CURL *curl;
    CURLcode res;
    std::string read_buffer;

    const std::string login_url = "http://neco-10655d.local/login/dologin";
    const std::string snapshot_url = "http://neco-10655d.local/snapshot.jpg";
    const std::vector<std::string> viewmodes = {"IR"};

    // Fichier pour stocker les cookies
    const char* cookie_file = "cookies.txt";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        // 1. Authentification
        std::string post_fields = "user_name=admin&user_password=admin";
        curl_easy_setopt(curl, CURLOPT_URL, login_url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

        // Stockage des cookies
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookie_file);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookie_file);

        // Capture de la réponse
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_to_string);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK || read_buffer.find("success") == std::string::npos) {
            std::cerr << " Authentification échouée.\n";
            curl_easy_cleanup(curl);
            return 1;
        }
        std::cout << "Authentification réussie.\n";
        read_buffer.clear();

        // 2. Pour chaque mode, changer le viewmode et récupérer le snapshot
        for (const auto& mode : viewmodes) {
            std::string mode_url = "http://neco-10655d.local/home/setviewmode/" + mode;

            // Changer le mode
            curl_easy_setopt(curl, CURLOPT_URL, mode_url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 0L);  // mode POST
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");  // POST vide
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_to_string);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "Erreur POST setviewmode " << mode << "\n";
                continue;
            }
            std::cout << " Passage au mode " << mode << "\n";
            read_buffer.clear();

            // Pause d'1 seconde pour laisser le temps au changement
            std::this_thread::sleep_for(std::chrono::seconds(1));

            // Télécharger l'image
            curl_easy_setopt(curl, CURLOPT_URL, snapshot_url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

            std::string filename = mode + ".jpg";
            FILE *fp = fopen(filename.c_str(), "wb");
            if (!fp) {
                std::cerr << "Impossible d’ouvrir " << filename << "\n";
                continue;
            }

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &write_to_file);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);
            fclose(fp);

            if (res == CURLE_OK) {
                std::cout << " Image enregistrée : " << filename << "\n";
            } else {
                std::cerr << " Erreur téléchargement image : " << curl_easy_strerror(res) << "\n";
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}

int FLIR_AX8::set_image_mode_VISUAL()
{
	CURL *curl;
    CURLcode res;
    std::string read_buffer;

    const std::string login_url = "http://neco-10655d.local/login/dologin";
    const std::string snapshot_url = "http://neco-10655d.local/snapshot.jpg";
    const std::vector<std::string> viewmodes = {"VISUAL"};

    // Fichier pour stocker les cookies
    const char* cookie_file = "cookies.txt";

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        // 1. Authentification
        std::string post_fields = "user_name=admin&user_password=admin";
        curl_easy_setopt(curl, CURLOPT_URL, login_url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

        // Stockage des cookies
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookie_file);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookie_file);

        // Capture de la réponse
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK || read_buffer.find("success") == std::string::npos) {
            std::cerr << " Authentification échouée.\n";
            curl_easy_cleanup(curl);
            return 1;
        }
        std::cout << "Authentification réussie.\n";
        read_buffer.clear();

        // 2. Pour chaque mode, changer le viewmode et récupérer le snapshot
        for (const auto& mode : viewmodes) {
            std::string mode_url = "http://neco-10655d.local/home/setviewmode/" + mode;

            // Changer le mode
            curl_easy_setopt(curl, CURLOPT_URL, mode_url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 0L);  // mode POST
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");  // POST vide
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "Erreur POST setviewmode " << mode << "\n";
                continue;
            }
            std::cout << " Passage au mode " << mode << "\n";
            read_buffer.clear();

            // Pause d'1 seconde pour laisser le temps au changement
            std::this_thread::sleep_for(std::chrono::seconds(1));

            // Télécharger l'image
            curl_easy_setopt(curl, CURLOPT_URL, snapshot_url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

            std::string filename = mode + ".jpg";
            FILE *fp = fopen(filename.c_str(), "wb");
            if (!fp) {
                std::cerr << "Impossible d’ouvrir " << filename << "\n";
                continue;
            }

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_file);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);
            fclose(fp);

            if (res == CURLE_OK) {
                std::cout << " Image enregistrée : " << filename << "\n";
            } else {
                std::cerr << " Erreur téléchargement image : " << curl_easy_strerror(res) << "\n";
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}

bool FLIR_AX8::alarme()
{
	uint16_t Rep[1];
	mb->modbus_connect();
	mb->modbus_set_slave_id(106);
	mb->modbus_read_holding_registers(4001, 1, Rep);
	mb->modbus_close();
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

void FLIR_AX8::toggle_isotherm_enable()
{

	mb->modbus_connect();
	mb->modbus_set_slave_id(104);

	uint16_t current_value = 0;

	// Lecture initiale
	mb->modbus_read_holding_registers(4001, 1, &current_value);
	cout << "Valeur lue du registre 4001 : " << current_value << endl;

	uint16_t new_value = (current_value == 0) ? 1 : 0;

	// Écriture
	mb->modbus_write_register(4001, new_value);

	// Lecture après écriture
	uint16_t verify_value = 0;
	mb->modbus_read_holding_registers(4001, 1, &verify_value);
	cout << "Valeur après écriture : " << verify_value << endl;

	cout << "Mode isotherm changé : " << (new_value ? "ON" : "OFF") << endl;

	mb->modbus_close();
}

void FLIR_AX8::OneShotimage(){

	mb->modbus_connect();
	mb->modbus_set_slave_id(103);

	uint16_t current_value = 0;

	mb->modbus_read_holding_registers(4261, 1, &current_value);
	uint16_t new_value = (current_value == 0) ? 1 : 0;
	mb->modbus_write_register(4261, new_value);

	uint16_t current_value2 = 0;

	mb->modbus_read_holding_registers(4281, 1, &current_value2);
	uint16_t new_value2 = (current_value2 == 0) ? 1 : 0;
	mb->modbus_write_register(4281, new_value);

}
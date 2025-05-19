#ifndef FLIR_AX8_H
#define FLIR_AX8_H

#include "modbus.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <bitset>
#include <sys/socket.h>
#include <netdb.h>
#include <cmath>
#include <curl/curl.h>

using namespace std;

#define SCP "scp fliruser@neco-10655D.local:/FLIR/system/images.jpg"
#define DOMAIN_NAME ".local"
#define LOGIN "fliruser"
#define PASSWORD "3vlig"
#define SSH "ssh "
#define SLAVE_ID_IMAGE 105
#define REGISTER_STORE_IMAGE 4001
#define SLAVE_ID_BASIC 1
#define AVERAGE_TEMP 1024
#define MAXIMUM_TEMP 1022
#define MIMINUM_TEMP 1020


class FLIR_AX8 {

private:
	//string Image;
	char Address;
	
	uint16_t execute = 1;
	uint16_t nothing = 0;
	
	modbus * mb;
	
	string hostIP;
    string Username;
    string Password;
	string composite;
	string chemin;

	char command[1024];

//	ssh_session ma_session;
  	int rc;
	const char *host = "neco-10655D.local";
    const char *username = "fliruser";
    const char *password = "3vlig";

	string resolveHostname(const string &hostname);

public:
	FLIR_AX8(string hostname);
void set_image_mode(int mode);

	int ConnectionFLIR_AX8();
	void Connection_Modbus();
	void Deconnection_Modbus();

	int requerir_Image();

	float acquerirTempMoy();
	float acquerirTempMax();
	float acquerirTempMin();
	int setVisionMode(int mode);
	CURLcode perform_request(const string& url, const string& username, const string& password, string& response, bool isPost = false, const string& postData = "");
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
	string get_image_mode();
	void set_image_mode_IR();
	void set_image_mode_VISUAL();
	int mettre_visible();

 
	int supprimer_image();

	//void obtenirEvent();

	void store_Image();
	bool alarme();
};


#endif
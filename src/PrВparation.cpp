
#include "../include/serialib.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

#define SERIAL_DEV "/dev/ttyUSB0" /*Chemin d'arborescence du port*/
#define ADDRESS 0x25              /*Addresse de la machine*/
#define REGISTER 0x0000           /*Addresse du registre qu'on cherche*/

#define CODE_FUNCTION 0x03 /*Lecture de n registres (mots) de maintien consécutifs*/


int main()
{
    /*unsigned char requete[8] = {ADDRESS, CODE_FUNCTION, REGISTER, 0x00, 0x00, 0x01};
    unsigned char reponse[11] = {0};
    unsigned char crcl, crch;
    unsigned short crc, octetsuivant;
    float decimalNumber;
    float convDec;
    int Err;
    stringstream ss;

    serialib serial;

    string composite;
    string hostIP;
    string username;
    string chemin;
    char command[100];
    
    /*cout << "Entrer l'ip ou le nom d'hôte" << endl;
	cin >> hostIP;

	cout << "Le nom d'utilisateur où vous souhaitez" << endl;
	cin >> username;

    cout << "Chemin où vous souhaitez déposer les images WARNING:ATTENTION À L'ENDROIT OÙ VOUS ÊTES" << endl;
	cin >> chemin;

    composite = "scp " + username + "@" + hostIP +":/FLIR/system/images/*.jpg " + chemin;
	strcpy(command, composite.c_str());

	bool reussi;
	reussi = system(command);
	if (reussi == true)
	{
		cout << "L'image a été récuperer" << endl;
	}
	else
	{
		return true;
    }*/
    string hostname = "neco-10655D.local";
    string ip = resolveHostname(hostname);
    if (!ip.empty())
    {
        cout << "L'adresse IP de " << hostname << " est : " << ip << endl;
    }
    else
    {
        cerr << "Impossible de résoudre l'adresse IP de " << hostname << endl;
    }
    uint16_t trame[1];
    uint16_t temp[2];
    uint16_t execute=1;
    uint16_t nothing=0;
    modbus *mb = new modbus(ip, 502);
    bool connecter = mb->modbus_connect();
    if (connecter != true)
    {
        return -1;
    }
    mb->modbus_set_slave_id(105);
    bool capture = mb->modbus_write_registers(4001,1,&execute);
    cout << capture << endl;
    if(capture == true)
    {
        cout << "La capture a été effectué" << endl;
    }
    else
    {
        cout << "La capture n'a pas été faites" << endl;
    }
    /*mb->modbus_set_slave_id(1);
    mb->modbus_read_holding_registers(1022, 2, temp);

    string hex = decimalToHexadecimal(temp[1]) + decimalToHexadecimal(temp[0]);
    cout << "Hexadecimal:" << hex << endl;

    string ieee = hexToIEEE754(hex);
    cout << "IEEE:" << ieee << endl;
    cout << "Longueur: "<< ieee.size() << endl;

    float kelvin = ieee_to_decimal(ieee);
    cout << "Valeur température en kelvin: " << kelvin << endl;

    float degree = kelvin - 273.15;
    cout << "Valeur temperature en celsus: " << degree << endl;*/

    mb->modbus_close();
    

    Err = serial.openDevice(SERIAL_DEV, 4800); // On ouvre le port
    cout << Err << endl;

    /*On vérifie si il est connecté*/
    if (Err == -2)
    {
        cout << "Elle est introuvable" << endl;
    }
    else
    {
        cout << "Elle accessible" << endl;
    }

    /*Formule pour calculer le crc*/
    crc = 0xFFFF;
    for (int i = 0; i <= 5; i++)
    {
        octetsuivant = requete[i] & 0x00FF;
        crc = (crc ^ octetsuivant); //(unsigned short)
        for (int cpt = 1; cpt <= 8; cpt++)
        {
            if ((crc & 0x01) == 1)
            {
                crc = (crc >> 1);
                crc = crc ^ 0xA001;
            }
            else
                crc = (crc >> 1);
        }
    }
    crcl = (unsigned char)(crc & 0x00FF);
    crch = (unsigned char)(crc >> 8);
    requete[6] = crcl;
    requete[7] = crch;
    printf("Le crc est :  %x %x\n", crcl, crch);

    cout << "Trame de la requête: ";
    for (int y = 0; y <= 8; y++)
    {
        cout << (int)requete[y] << '\t';
    }
    cout << endl;

    serial.writeBytes(requete, 8); /*Ecris sur le bus*/
    serial.readBytes(reponse, 7);  /*Lis la trame*/

    cout << "Trame de la réponse: ";
    for (int y = 0; y <= 8; y++)
    {
        cout << (int)reponse[y] << '\t';
    }
    cout << endl;

    decimalNumber = ((reponse[3] << 8) + reponse[4])/10;
    cout << "Valeur décimal: " <<decimalNumber <<endl;


    return 0;

    serial.closeDevice();
}
string resolveHostname(const std::string &hostname)
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

string hexToBinary(string hexValue)
{
    string binaryValue = "";
    for (char &c : hexValue)
    {
        switch (toupper(c))
        {
        case '0':
            binaryValue += "0000";
            break;
        case '1':
            binaryValue += "0001";
            break;
        case '2':
            binaryValue += "0010";
            break;
        case '3':
            binaryValue += "0011";
            break;
        case '4':
            binaryValue += "0100";
            break;
        case '5':
            binaryValue += "0101";
            break;
        case '6':
            binaryValue += "0110";
            break;
        case '7':
            binaryValue += "0111";
            break;
        case '8':
            binaryValue += "1000";
            break;
        case '9':
            binaryValue += "1001";
            break;
        case 'A':
            binaryValue += "1010";
            break;
        case 'B':
            binaryValue += "1011";
            break;
        case 'C':
            binaryValue += "1100";
            break;
        case 'D':
            binaryValue += "1101";
            break;
        case 'E':
            binaryValue += "1110";
            break;
        case 'F':
            binaryValue += "1111";
            break;
        default:
            std::cerr << "Caractère non hexadécimal détecté: " << c << std::endl;
            return "";
        }
    }
    return binaryValue;
}

string hexToIEEE754(string hexValue)
{
    string binaryValue = hexToBinary(hexValue);

    if (binaryValue.length() != 32)
    {
        std::cerr << "Le nombre hexadécimal doit être de 8 caractères (32 bits) pour être converti en IEEE 754." << std::endl;
        return "";
    }

    string signBit = binaryValue.substr(0, 1);
    string exponentBits = binaryValue.substr(1, 8);
    string mantissaBits = binaryValue.substr(9);

    return signBit+exponentBits+mantissaBits;
}

string decimalToHexadecimal(int decimalValue)
{
    stringstream ss;
    ss << hex << uppercase << decimalValue;
    return ss.str();
}

float ieee_to_decimal(const std::string &binary)
{
    // Vérifie si le nombre binaire est dans le bon format
    if (binary.size() != 32 || binary.find_first_not_of("01") != std::string::npos)
    {
        std::cerr << "Format binaire incorrect." << std::endl;
        return 0.0f;
    }

    // Récupère le signe, l'exposant et la fraction
    int sign = binary[0] == '1' ? -1 : 1;
    int exponent = std::bitset<8>(binary.substr(1, 8)).to_ulong() - 127;
    float fraction = 1.0f;

    for (int i = 0; i < 23; ++i)
    {
        fraction += (binary[9 + i] - '0') * pow(2, -i - 1);
    }

    // Calcule la valeur décimale
    float result = sign * fraction * pow(2, exponent);
    return result;
}
/*
composite = "ssh fliruser@neco-10655D.local";
	strcpy(command, composite.c_str());

	bool connecter;
	connecter = system(command);
	if (connecter != true)
	{
		return connecter;
	}
	return 0;
*/
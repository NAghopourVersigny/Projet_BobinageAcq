#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

#include "../include/MQTTClient.h"

string createVibrationsJson(double vx, double vy, double vz)
{
    // Récupération de l'heure actuelle pour horodatage
    time_t maintenant = std::time(nullptr);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&maintenant));

    ostringstream oss;
    oss << "{\"timestamp\": \"" << buffer << "\","
        << "\"vx\": " << vx << ", "
        << "\"vy\": " << vy << ", "
        << "\"vz\": " << vz << "}";
    return oss.str();
}

string createTemperatureJson(double moy, double max)
{
    // Récupération de l'heure actuelle pour horodatage
    time_t maintenant = time(nullptr);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&maintenant));

    ostringstream oss;
    oss << "{\"timestamp\": \"" << buffer << "\","
        << "\"temp_moy\": " << moy << ", "
        << "\"temp_max\": " << max << "}";
    return oss.str();
}

string createTemperatureAlerteJson(double max)
{
    // Récupération de l'heure actuelle pour horodatage
    time_t maintenant = time(nullptr);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&maintenant));

    ostringstream oss;
    oss << "{\"timestamp\": \"" << buffer << "\","
        << "\"type\": " << "Alerte" << ", "
        << "\"seuil\": " << max << ", "
        << "\"valeur\": " << "" << ", "
        << "\"seuil_declenchement\": " << "" << ", "
        << "\"imageThermique\": " << "" << ", "
        << "\"imageVisible\": " << "" << "}";
    return oss.str();
}

string createVibrationsAlerteJsonX(double vx)
{
    // Récupération de l'heure actuelle pour horodatage
    time_t maintenant = time(nullptr);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&maintenant));

    ostringstream oss;
    oss << "{\"timestamp\": \"" << buffer << "\","
        << "\"type\": " << "Alerte" << ", "
        << "\"axe\": " << vx << ", "
        << "\"valeur\": " << "" << ", "
        << "\"seuil_declenchement\": " << "" << ", "
        << "\"imageThermique\": " << "" << ", "
        << "\"imageVisible\": " << "" << "}";
    return oss.str();
}

string createVibrationsAlerteJsonY(double vy)
{
    // Récupération de l'heure actuelle pour horodatage
    time_t maintenant = time(nullptr);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&maintenant));

    ostringstream oss;
    oss << "{\"timestamp\": \"" << buffer << "\","
        << "\"type\": " << "Alerte" << ", "
        << "\"axe\": " << vy << ", "
        << "\"valeur\": " << "" << ", "
        << "\"seuil_declenchement\": " << "" << ", "
        << "\"imageThermique\": " << "" << ", "
        << "\"imageVisible\": " << "" << "}";
    return oss.str();
}


string createVibrationsAlerteJsonZ(double vz)
{
    // Récupération de l'heure actuelle pour horodatage
    time_t maintenant = std::time(nullptr);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&maintenant));

    ostringstream oss;
    oss << "{\"timestamp\": \"" << buffer << "\","
        << "\"type\": " << "Alerte" << ", "
        << "\"axe\": " << vz << ", "
        << "\"valeur\": " << "" << ", "
        << "\"seuil_declenchement\": " << "" << ", "
        << "\"imageThermique\": " << "" << ", "
        << "\"imageVisible\": " << "" << "}";
    return oss.str();
}


string createAcquisitionJson(double temp_max_alerte, double temp_moy_alerte)
{
    ostringstream oss;
    oss << "\"temp_moy_alerte\": " << temp_max_alerte << ", "
        << "\"temp_max_alerte\": " << temp_moy_alerte << "}";
    return oss.str();
}


int main()
{
    MQTTClient client("IOT1", "10.119.1.33", 1883, "ecei/+/+/+", "adminECEI", "adminECEI");

    if (!client.connect())
    {
        cerr << "Erreur connexion MQTT IOT\n";
        return 1;
    }

    client.disconnect();
    return 0;
}

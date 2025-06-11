#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <string>

#include "../include/Message.h"
#include "../include/MQTTTopics.h"

string Message::createVibrationsJson(double vx, double vy, double vz)
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

string Message::createTemperatureJson(double moy, double max)
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

string Message::createTemperatureAlerteJson(double max)
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

string Message::createVibrationsAlerteJsonX(double vx, string imageIR, string imageVISUAL)
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

string Message::createVibrationsAlerteJsonY(double vy, string imageIR, string imageVISUAL)
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


string Message::createVibrationsAlerteJsonZ(double vz, string imageIR, string imageVISUAL)
{
    // Récupération de l'heure actuelle pour horodatage
{
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
}

string Message::createVibrationsAlarmeJsonX(double vx, string imageIR, string imageVISUAL)
{
    // Récupération de l'heure actuelle pour horodatage
    time_t maintenant = time(nullptr);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&maintenant));

    ostringstream oss;
    oss << "{\"timestamp\": \"" << buffer << "\","
        << "\"type\": " << "Alarme" << ", "
        << "\"axe\": " << vx << ", "
        << "\"valeur\": " << "" << ", "
        << "\"seuil_declenchement\": " << "" << ", "
        << "\"imageThermique\": " << "" << ", "
        << "\"imageVisible\": " << "" << "}";
    return oss.str();
}

string Message::createVibrationsAlarmeJsonY(double vy, string imageIR, string imageVISUAL)
{
    // Récupération de l'heure actuelle pour horodatage
    time_t maintenant = time(nullptr);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&maintenant));

    ostringstream oss;
    oss << "{\"timestamp\": \"" << buffer << "\","
        << "\"type\": " << "Alarme" << ", "
        << "\"axe\": " << vy << ", "
        << "\"valeur\": " << "" << ", "
        << "\"seuil_declenchement\": " << "" << ", "
        << "\"imageThermique\": " << "" << ", "
        << "\"imageVisible\": " << "" << "}";
    return oss.str();
}

string Message::createVibrationsAlarmeJsonZ(double vz, string imageIR, string imageVISUAL)
{
    // Récupération de l'heure actuelle pour horodatage
    time_t maintenant = time(nullptr);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&maintenant));

    ostringstream oss;
    oss << "{\"timestamp\": \"" << buffer << "\","
        << "\"type\": " << "Alarme" << ", "
        << "\"axe\": " << vz << ", "
        << "\"valeur\": " << "" << ", "
        << "\"seuil_declenchement\": " << "" << ", "
        << "\"imageThermique\": " << "" << ", "
        << "\"imageVisible\": " << "" << "}";
    return oss.str();
}

string Message::createAcquisitionJson(double temp_max_alerte, double temp_moy_alerte)
{
    ostringstream oss;
    oss << "\"temp_moy_alerte\": " << temp_max_alerte << ", "
        << "\"temp_max_alerte\": " << temp_moy_alerte << "}";
    return oss.str();
}
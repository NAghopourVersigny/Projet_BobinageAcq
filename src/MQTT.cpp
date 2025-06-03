#include "../include/MQTT.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <fstream>
#include "../test/json.hpp"

using namespace std;
using json = nlohmann::json;

MQTTClient::MQTTClient(const std::string &host, int port, const std::string &topic)
    : host_(host), port_(port), topic_(topic), mosq_(nullptr)
{
    mosquitto_lib_init();
    mosq_ = mosquitto_new(nullptr, true, this);

    if (!mosq_) {
        throw std::runtime_error("Erreur lors de la création du client Mosquitto");
    }
}

MQTTClient::~MQTTClient()
{
    if (mosq_)
    {
        mosquitto_destroy(mosq_);
    }
    mosquitto_lib_cleanup();
}

bool MQTTClient::connect()
{
    if (!mosq_)
        return false;

    int ret = mosquitto_connect(mosq_, host_.c_str(), port_, 60);
    if (ret != MOSQ_ERR_SUCCESS)
    {
        std::cerr << "Erreur de connexion : " << mosquitto_strerror(ret) << std::endl;
        return false;
    }

    mosquitto_subscribe(mosq_, nullptr, ("ecei/machine" + std::to_string(machineId) + "/config/seuils").c_str(), 1);
    mosquitto_subscribe(mosq_, nullptr, ("ecei/machine" + std::to_string(machineId) + "/commande/apprentissage").c_str(), 1);

    return true;
}

void MQTTClient::disconnect()
{
    if (mosq_)
    {
        mosquitto_disconnect(mosq_);
    }
}

bool MQTTClient::subscribeAndListen()
{
    if (!mosq_)
        return false;

    int ret = mosquitto_subscribe(mosq_, nullptr, topic_.c_str(), 1);
    if (ret != MOSQ_ERR_SUCCESS)
    {
        std::cerr << "Erreur d'abonnement : " << mosquitto_strerror(ret) << std::endl;
        return false;
    }

    std::cout << "Abonné au topic : " << topic_ << std::endl;
    mosquitto_loop_start(mosq_);
    std::cin.get();
    mosquitto_loop_stop(mosq_, true);
    return true;
}

void MQTTClient::ReceptionseuilsMessage(const std::string& payload)
{
    try {
        auto json = nlohmann::json::parse(payload);

        seuil_temp_moy_alerte_ = json.value("temp_moy_alerte", 0.0);
        seuil_temp_max_alerte_ = json.value("temp_max_alerte", 0.0);
        seuil_temp_moy_alarme_ = json.value("temp_moy_alarme", 0.0);
        seuil_temp_max_alarme_ = json.value("temp_max_alarme", 0.0);
        seuil_vibration_alerte_ = json.value("vibration_alerte", 0.0);
        seuil_vibration_alarme_ = json.value("vibration_alarme", 0.0);
        seuilsInitialises_ = true;

        std::cout << "Seuils reçus via MQTT." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Erreur parsing seuils : " << e.what() << std::endl;
    }
}

void MQTTClient::ReceptionTempMachineMessage(const std::string& payload)
{
    try {
        auto json = nlohmann::json::parse(payload);
        if (json.contains("timestamp")) dateTime_ = json["timestamp"];
        if (json.contains("temp_max")) tmax_ = std::to_string(json["temp_max"].get<double>());
        if (json.contains("temp_moy")) tmoy_ = std::to_string(json["temp_moy"].get<double>());

        std::cout << "\n--- Température reçue ---\n"
                  << "  ➤ Timestamp : " << dateTime_ << "\n"
                  << "  ➤ Temp max : " << tmax_ << " °C\n"
                  << "  ➤ Temp moy : " << tmoy_ << " °C\n"
                  << "--------------------------\n";
    } catch (const std::exception& e) {
        std::cerr << "Erreur parsing température : " << e.what() << std::endl;
    }
}

void MQTTClient::ReceptionVibrationsMessage(const std::string& payload)
{
    try {
        auto json = nlohmann::json::parse(payload);
        if (json.contains("timestamp")) dateTime_ = json["timestamp"];
        if (json.contains("vx")) vibrationX_ = json["vx"];
        if (json.contains("vy")) vibrationY_ = json["vy"];
        if (json.contains("vz")) vibrationZ_ = json["vz"];

        std::cout << "\n--- Vibrations reçues ---\n"
                  << "  ➤ Timestamp : " << dateTime_ << "\n"
                  << "  ➤ X : " << vibrationX_ << " mm/s\n"
                  << "  ➤ Y : " << vibrationY_ << " mm/s\n"
                  << "  ➤ Z : " << vibrationZ_ << " mm/s\n"
                  << "--------------------------\n";
    } catch (const std::exception& e) {
        std::cerr << "Erreur parsing vibrations : " << e.what() << std::endl;
    }
}

bool MQTTClient::publishTemperatureMachine(int machineId)
{
    if (!mosq_) return false;
    if (!seuilsInitialises_) {
        std::cerr << "Seuils non reçus. Publication température ignorée.\n";
        return false;
    }

    std::string timestamp = getCurrentDateTime();
    double temp_moy = getTemperatureMoy();
    double temp_max = getTemperatureMax();

    json valeurs = {
        {"timestamp", timestamp},
        {"temp_moy", temp_moy},
        {"temp_max", temp_max}
    };

    std::string topic = "ecei/machine" + std::to_string(machineId) + "/temperature/valeurs";
    std::string payload = valeurs.dump();

    int ret = mosquitto_publish(mosq_, nullptr, topic.c_str(), payload.size(), payload.c_str(), 1, false);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Erreur publication température : " << mosquitto_strerror(ret) << std::endl;
        return false;
    }

    std::cout << "Température publiée : " << payload << std::endl;
    return true;
}

bool MQTTClient::publishVibrations(int machineId)
{
    if (!mosq_) return false;
    if (!seuilsInitialises_) {
        std::cerr << "Seuils non reçus. Publication vibration ignorée.\n";
        return false;
    }

    std::string timestamp = getCurrentDateTime();
    double vx = getVibrationX();
    double vy = getVibrationY();
    double vz = getVibrationZ();

    json valeurs = {
        {"timestamp", timestamp},
        {"vx", vx}, {"vy", vy}, {"vz", vz}
    };

    std::string topic = "ecei/machine" + std::to_string(machineId) + "/vibration/valeurs";
    std::string payload = valeurs.dump();

    int ret = mosquitto_publish(mosq_, nullptr, topic.c_str(), payload.size(), payload.c_str(), 1, false);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Erreur publication vibration : " << mosquitto_strerror(ret) << std::endl;
        return false;
    }

    std::cout << "Vibration publiée : " << payload << std::endl;
    return true;
}

bool MQTTClient::publishMACCamera(int machineId, const std::string& macAdresse)
{
    if (!mosq_) return false;

    std::string topic = "ecei/machine" + std::to_string(machineId) + "/config/maccamera";
    json data = { {"adresse", macAdresse} };
    std::string payload = data.dump();

    int ret = mosquitto_publish(mosq_, nullptr, topic.c_str(), payload.size(), payload.c_str(), 1, false);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Erreur publication MAC : " << mosquitto_strerror(ret) << std::endl;
        return false;
    }

    std::cout << "MAC caméra publiée : " << payload << std::endl;
    return true;
}

double MQTTClient::getTemperatureMax() { return 29.7; }
double MQTTClient::getTemperatureMoy() { return 27.2; }
double MQTTClient::getVibrationX() { return 4.6; }
double MQTTClient::getVibrationY() { return 4.6; }
double MQTTClient::getVibrationZ() { return 4.6; }

std::string MQTTClient::getCurrentDateTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t), "%Y-%m-%dT%H:%M:%SZ");
    return oss.str();
}


void MQTTClient::ReceptionApprentissageTempMessage(const std::string& payload)
{
    try {
        auto json = nlohmann::json::parse(payload);

        apprentissage_temperature_ = json.value("temperature", false);
        apprentissage_duree_temp_ = json.value("dureeApprentissageTemp", 0);
        coeff_temp_ = json.value("coeffTemp", 1.0);

        std::cout << "\n Paramètres d'apprentissage température mis à jour :\n"
                  << "  ➤ temperature = " << (apprentissage_temperature_ ? "true" : "false") << "\n"
                  << "  ➤ durée = " << apprentissage_duree_temp_ << " sec\n"
                  << "  ➤ coeff = " << coeff_temp_ << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Erreur parsing apprentissage température : " << e.what() << std::endl;
    }
}


void MQTTClient::ReceptionApprentissageVibrationMessage(const std::string& payload)
{
    try {
        auto json = nlohmann::json::parse(payload);

        apprentissage_vibration_ = json.value("vibration", false);
        apprentissage_duree_vib_ = json.value("dureeApprentissageVibration", 0);
        coeff_vib_alerte_ = json.value("coeffVibAlerte", 1.0);
        coeff_vib_alarme_ = json.value("coeffVibAlarme", 1.0);

        std::cout << "\n Paramètres d'apprentissage vibration mis à jour :\n"
                  << "  ➤ vibration = " << (apprentissage_vibration_ ? "true" : "false") << "\n"
                  << "  ➤ durée = " << apprentissage_duree_vib_ << " sec\n"
                  << "  ➤ coeff alerte = " << coeff_vib_alerte_ << "\n"
                  << "  ➤ coeff alarme = " << coeff_vib_alarme_ << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Erreur parsing apprentissage vibration : " << e.what() << std::endl;
    }
}

if (topic == "ecei/machine1/commande/apprentissage") {
    client->ReceptionApprentissageTempMessage(payload);
    client->ReceptionApprentissageVibrationMessage(payload);
}



#include "../include/MQTT.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>

MQTTClient::MQTTClient(const std::string& host, int port, const std::string& topic)
    : host_(host), port_(port), topic_(topic), mosq_(nullptr) {
    mosquitto_lib_init();
    mosq_ = mosquitto_new(nullptr, true, this);

    if (mosq_) {
        mosquitto_message_callback_set(mosq_, &MQTTClient::onMessage);
    }
}

MQTTClient::~MQTTClient() {
    if (mosq_) {
        mosquitto_destroy(mosq_);
    }
    mosquitto_lib_cleanup();
}

bool MQTTClient::connect() {
    if (!mosq_) return false;
    int ret = mosquitto_connect(mosq_, host_.c_str(), port_, 60);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Erreur de connexion : " << mosquitto_strerror(ret) << std::endl;
        return false;
    }
    return true;
}

void MQTTClient::disconnect() {
    if (mosq_) {
        mosquitto_disconnect(mosq_);
    }
}

bool MQTTClient::publishTemperature() {
    double tmax = getTemperatureMax();
    double tmoy = getTemperatureMoy();
    std::string dt = getCurrentDateTime();

    std::ostringstream oss;
    oss << tmax << ";" << tmoy << ";" << dt;
    std::string payload = oss.str();

    int ret = mosquitto_publish(mosq_, nullptr, topic_.c_str(), payload.size(), payload.c_str(), 1, false);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Erreur de publication : " << mosquitto_strerror(ret) << std::endl;
        return false;
    }

    std::cout << "Message publié : " << payload << std::endl;
    return true;
}

bool MQTTClient::subscribeAndListen() {
    if (!mosq_) return false;

    int ret = mosquitto_subscribe(mosq_, nullptr, topic_.c_str(), 1);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Erreur d'abonnement : " << mosquitto_strerror(ret) << std::endl;
        return false;
    }

    std::cout << "Abonné au topic : " << topic_ << std::endl;

    mosquitto_loop_start(mosq_);
    std::cout << "En écoute... Appuyez sur Entrée pour quitter." << std::endl;
    std::cin.get();
    mosquitto_loop_stop(mosq_, true);
    return true;
}

void MQTTClient::onMessage(struct mosquitto* mosq, void* obj, const struct mosquitto_message* message) {
    std::string payload(static_cast<char*>(message->payload), message->payloadlen);
    
    std::cout << "Message reçu : " << payload << std::endl;
    MQTTClient* client = static_cast<MQTTClient*>(obj);
    std::istringstream iss(payload);
    std::string tmax, tmoy, dt, humidite, temperature, vibration;

    if (std::getline(iss, tmax, ';') &&
        std::getline(iss, tmoy, ';') &&
        std::getline(iss, dt, ';') &&
        std::getline(iss, humidite, ';') &&
        std::getline(iss, temperature, ';') &&
        std::getline(iss, vibration)) {
        
        client->onMessageTmax(tmax);
        client->onMessageTmoy(tmoy);
        client->onMessageDateTime(dt);
        client->onMessageHumidite(humidite);
        client->onMessageTemperature(temperature);
        client->onMessageVibration(vibration);

        client->afficherDonnees();
    } else {
        std::cerr << "Erreur de format du message." << std::endl;
    }
}

void MQTTClient::onMessageTmax(const std::string& tmax) {
    tmax_ = tmax;
    std::cout << "  ➤ Temp. max : " << tmax_ << " °C" << std::endl;
}

void MQTTClient::onMessageTmoy(const std::string& tmoy) {
    tmoy_ = tmoy;
    std::cout << "  ➤ Temp. moy : " << tmoy_ << " °C" << std::endl;
}

void MQTTClient::onMessageDateTime(const std::string& dt) {
    dateTime_ = dt;
    std::cout << "  ➤ Date/Heure : " << dateTime_ << std::endl;
}

void MQTTClient::onMessageHumidite(const std::string& humidite) {
    humidite_ = humidite;
    std::cout << "  ➤ Humidité : " << humidite_ << " %" << std::endl;
}

void MQTTClient::onMessageTemperature(const std::string& temperature) {
    temperature_ = temperature;
    std::cout << "  ➤ Température : " << temperature_ << " °C" << std::endl;
}

void MQTTClient::onMessageVibration(const std::string& vibration) {
    vibration_ = vibration;
    std::cout << "  ➤ Vibration : " << vibration_ << " g" << std::endl;
}


double MQTTClient::getTemperatureMax() {
    return 29.7;
}

double MQTTClient::getTemperatureMoy() {
    return 27.2;
}

double MQTTClient::getHumidite() {
    return 50.5;
}

double MQTTClient::getTemperature() {
    return 25.3;
}

double MQTTClient::getVibration() {
    return 0.5;
}

std::string MQTTClient::getCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t), "%FT%T");
    return oss.str();
}

void MQTTClient::afficherDonnees() {
    std::cout << "\n--- Données capteur ---" << std::endl;
    std::cout << "  ➤ Temp. max     : " << tmax_ << " °C" << std::endl;
    std::cout << "  ➤ Temp. moy     : " << tmoy_ << " °C" << std::endl;
    std::cout << "  ➤ Température   : " << temperature_ << " °C" << std::endl;
    std::cout << "  ➤ Humidité      : " << humidite_ << " %" << std::endl;
    std::cout << "  ➤ Vitesse Vibration     : " << vibration_ << " g" << std::endl;
    std::cout << "  ➤ Date/Heure    : " << dateTime_ << std::endl;
    std::cout << "------------------------\n" << std::endl;
}

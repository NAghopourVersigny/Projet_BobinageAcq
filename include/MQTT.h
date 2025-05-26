#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <string>
#include <mosquitto.h>

class MQTTClient {
public:
    MQTTClient(const std::string& host, int port, const std::string& topic);
    ~MQTTClient();

    bool connect();
    void disconnect();
    bool publishTemperature();
    bool subscribeAndListen();

    void onMessageTmax(const std::string& tmax);
    void onMessageTmoy(const std::string& tmoy);
    void onMessageDateTime(const std::string& dt);
    void onMessageHumidite(const std::string& humidite);
    void onMessageTemperature(const std::string& temperature);
    void onMessageVibration(const std::string& vibration);

    double getTemperatureMax();
    double getTemperatureMoy();
    double getHumidite();
    double getTemperature();
    double getVibration();
    std::string getCurrentDateTime();

    void afficherDonnees();
    
private:
    std::string host_;
    int port_;
    std::string topic_;
    struct mosquitto* mosq_;

    static void onMessage(struct mosquitto* mosq, void* obj, const struct mosquitto_message* message);

    std::string tmax_;
    std::string tmoy_;
    std::string dateTime_;
    std::string humidite_;
    std::string temperature_;
    std::string vibration_;
};

#endif // MQTT_CLIENT_H
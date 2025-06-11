#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <mosquitto.h>

#include "../../Dossier_TestCamera/include/SurveillanceMachineServ.h"

class SurveillanceMachineServ; // déclaration anticipée car, dans le cas d'une association, il y en a un qui existe avant l'autre.

class MQTTClient {
public:
    MQTTClient(const std::string& id, const std::string& host, int port, const std::string& topic, const std::string& username = "", const std::string& password = "");
    ~MQTTClient();

    void setCallbackHandler(SurveillanceMachineServ* handler); 

    bool connect();
    void disconnect();
    bool publish(const std::string& topic, const std::string& payload);
    bool subscribe(vector<string> topics);

    void loopForever();

private:
    std::string id_, host_, topic_, username_,password_;
    int port_;
    struct mosquitto* mosq_;

    static void onMessage(struct mosquitto* mosq, void* obj, const struct mosquitto_message* message);
    double vx_, vy_, vz_;
    double temp_max_alerte, temp_moy_alerte;
    SurveillanceMachineServ* callbackHandler_; 
};

#endif // MQTT_CLIENT_H

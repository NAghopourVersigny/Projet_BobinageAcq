#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <mosquitto.h>

#include "../../Dossier_TestCamera/include/SurveillanceMachineServ.h"

using namespace std;

class SurveillanceMachineServ; // déclaration anticipée car, dans le cas d'une association, il y en a un qui existe avant l'autre.

class Message {
public:
    Message(const string& id, const std::string& host, int port, const std::string& topic, const std::string& username = "", const std::string& password = "");
    ~Message();

    void setCallbackHandler(SurveillanceMachineServ* handler); 

    bool connect();
    void disconnect();
    bool publish(const std::string& topic, const std::string& payload);
    bool subscribe(vector<string> topics);
    


    void loopForever();


    string createVibrationsJson(double vx, double vy, double vz);
    
    string createTemperatureJson(double moy, double max);
    string createTemperatureAlerteJson(double max);

    string createVibrationsAlerteJsonX(double vx, string imageIR, string imageVISUAL);
    string createVibrationsAlerteJsonY(double vy, string imageIR, string imageVISUAL);
    string createVibrationsAlerteJsonZ(double vz, string imageIR, string imageVISUAL);

    string createVibrationsAlarmeJsonX(double vx, string imageIR, string imageVISUAL);
    string createVibrationsAlarmeJsonY(double vy, string imageIR, string imageVISUAL);
    string createVibrationsAlarmeJsonZ(double vz, string imageIR, string imageVISUAL);
    
    string createAcquisitionJson(double temp_max_alerte, double temp_moy_alerte);
};

#endif // MQTT_CLIENT_H
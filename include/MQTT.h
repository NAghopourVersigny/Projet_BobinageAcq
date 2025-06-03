#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <string>
#include <mosquitto.h>

class MQTTClient {
public:
    MQTTClient(const std::string& host, int port, const std::string& topic);
    ~MQTTClient();

    bool connect();
    void disconnect();
    bool subscribeAndListen();

    bool publishTemperatureMachine(int machineId);
    bool publishVibrations(int machineId);
    bool publishMACCamera(int machineId, const std::string& macAdresse);
    bool publishApprentissageSeuilsTemp(int machineId);
    bool publishApprentissageSeuilsVibration(int machineId);
    bool publishSeuils(int machineId);

    void ReceptionseuilsMessage(const std::string& payload);
    void ReceptionTempMachineMessage(const std::string& payload);
    void ReceptionVibrationsMessage(const std::string& payload);
    void ReceptionApprentissageTempMessage(const std::string& payload);
    void ReceptionApprentissageVibrationMessage(const std::string& payload);

    double getTemperatureMax();
    double getTemperatureMoy();
    double getVibrationX();
    double getVibrationY();
    double getVibrationZ();
    std::string getCurrentDateTime();

private:
   int machineId;
    std::string host_;
    int port_;
    std::string topic_;
    struct mosquitto* mosq_;

    // Données capteurs
    std::string dateTime_;
    std::string tmax_, tmoy_;
    double vibrationX_ = 0;
    double vibrationY_ = 0;
    double vibrationZ_ = 0;

    // Seuils dynamiques
    double seuil_temp_moy_alerte_ = 0;
    double seuil_temp_max_alerte_ = 0;
    double seuil_temp_moy_alarme_ = 0;
    double seuil_temp_max_alarme_ = 0;
    double seuil_vibration_alerte_ = 0;
    double seuil_vibration_alarme_ = 0;
    bool seuilsInitialises_ = false;

    // Apprentissage
    bool apprentissage_temperature_ = false;
    bool apprentissage_vibration_ = false;
    int apprentissage_duree_temp_ = 0;
    int apprentissage_duree_vib_ = 0;
    double coeff_temp_ = 1.0;
    double coeff_vib_alerte_ = 1.0;
    double coeff_vib_alarme_ = 1.0;
};

#endif



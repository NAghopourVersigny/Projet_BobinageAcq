#ifndef MQTT_TOPICS_H
#define MQTT_TOPICS_H

#include <string>

class MQTTTopics
{
public:
    /*     static std::string temperatureTopic(int machineId) {
            return "ecei/machine" + std::to_string(machineId) + "/temperature/valeurs";
        } */
    static std::string temperatureTopic()
    {
        return "ecei/+/temperature/valeurs";
    }

    static std::string temperatureAlerteTopic()
    {
        return "ecei/+/temperature/alerte";
    }

    /*     static std::string vibrationsTopic(int machineId) {
            return "ecei/machine" + std::to_string(machineId) + "/vibrations/valeurs";
        } */
    static std::string vibrationsTopic()
    {
        return "ecei/+/vibrations/valeurs";
    }

    static std::string vibrationsAlerteTopic()
    {
        return "ecei/+/vibrations/alerte";
    }


    static std::string acquisitionTopic()
    {
        return "ecei/+/acquisition/seuils";
    }    

    /*     static std::string apprentissageTopic(int machineId) {
            return "ecei/machine" + std::to_string(machineId) + "/apprentissage";
        } */
    /**
     * topic Serveur --> IOT
     */
    static std::string apprentissageTopic(int machineId)
    {
        return "ecei/machine" + std::to_string(machineId) + "/commande/apprentissage";
    }



    /*     static std::string seuilsTopic(int machineId) {
            return "ecei/machine" + std::to_string(machineId) + "/seuils";
        } */

    static std::string confSeuilsTopic(int machineId)
    {
        return "ecei/machine" + std::to_string(machineId) + "/config/seuils";
    }

    static std::string confCameraTopic(int machineId)
    {
        return "ecei/machine" + std::to_string(machineId) + "/config/maccamera";
    }

    static std::string wildcardTemperature()
    {
        return "ecei/+/temperature/valeurs";
    }

    static std::string wildcardVibrations()
    {
        return "ecei/+/vibrations/valeurs";
    }
};

#endif

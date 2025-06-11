#include <thread>
#include <chrono>

#include "../include/SurveillanceMachineServ.h"

int main()
{

    MQTTClient *client = new MQTTClient("SERV", "localhost", 1883, "ecei/+/+/+", "adminECEI", "adminECEI");

    SurveillanceMachineServ serveur(client);
    client->setCallbackHandler(&serveur);

    client->loopForever();

    for (int i = 0; i < 5; ++i)
    {
        string payload = createCameraJson("00:40:7F:10:65:5D");
        client->publish("ecei/+/temperature/alerte", payload);
        cout << "Donnée d'Adresse MAC envoyée : " << payload << "\n";
        this_thread::sleep_for(chrono::seconds(2));
    }
    return 0;
}

string createApprentissageSeuilsVibraJson()
{
    ostringstream oss;
    oss << "\"vibration\": " << false << ", "
        << "\"dureeApprentissageVib\": " << "" << ", "
        << "\"coeffVibAlerte\": " << "" << "}";
    return oss.str();
}

string createApprentissageSeuilsTempJson()
{
    ostringstream oss;
    oss << "\"temperature\": " << true << ", "
        << "\"dureeApprentissageVib\": " << "" << ", "
        << "\"coeffTemp\": " << "" << "}";
    return oss.str();
}

string createCameraJson(string adresse)
{
    ostringstream oss;
    oss << "\"adresse\": " << adresse << "}";
    return oss.str();
}

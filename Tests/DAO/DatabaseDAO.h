#ifndef DATABASEDAO_H
#define DATABASEDAO_H

#include <string>
using namespace std;

class DatabaseDAO
{
public:
    static string listeMachines()
    {
  
        return "SELECT * FROM Machine;";
    }

    static string creationMachineDefaut(int numero, string type)
    {
        string requete = "INSERT INTO Machine VALUES (" + to_string(numero) + ",\"" + type + "\",0,0,\"05:00:00\",\"05:00:00\",1.05,1.1,1.2,\"00:00:00:00:00:00\");";
  
        return requete;
    }    

    static string acquisitionAmbiance()
    {
        string requete = "INSERT INTO Contexte (date, tempAmb, humidite) VALUES(\'" + dateHeure + "\'," + to_string(temp) + "," + to_string(humidite) + ",)";
    }
};

#endif

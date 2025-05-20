#include <algorithm>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include "../../../mariadb-connector-cpp-1.0.2-rhel9-amd64/include/mariadb/conncpp.hpp"
#include "../include/Apprentissage.h"
#include "../include/Camera.h"
#include "../include/bdd.h"

using namespace std;
using namespace sql;
using namespace mariadb;

Apprentissage::Apprentissage()
{
    Camera* laCamera = new Camera("neco-10655D.local");
}

bool Apprentissage::interrogerBDDTemp(){

BDD* laBDD = new BDD("jdbc:mariadb://localhost:3306/BobinageAcq");

// Instantiate Driver
Driver* driver = get_driver_instance();

// Configure Connection
SQLString url = laBDD->getURL();
Properties properties({{"user", ""}, {"password", ""}});

// Establish Connection
unique_ptr<Connection> conn(driver->connect(url, properties));


// Create a new PreparedStatement
unique_ptr<PreparedStatement> stmnt(conn->prepareStatement("SELECT apprentissageTermineTemp FROM Machine WHERE id = ?"));
stmnt->setInt(1, 1);

// Execute query
ResultSet *res = stmnt->executeQuery();

// Loop through and print results
while (res->next()) {
       cout << "apprentissageTermineTemp = " << res->getInt(1);
}

return 0;

}

void Apprentissage::lancerApprentissageTemp()
{
        // Acquisition des températures
        float temperatureMoy = laCamera->obtenirTempMoy();
        float temperatureMax = laCamera->obtenirTempMax();

        // Ajouter les températures au tableau
        tempMoy.push_back(temperatureMoy);
        tempMax.push_back(temperatureMax);

        // Attendre 1 seconde entre chaque lecture
        sleep(1);

        if (!tempMax.empty())
        {
        float temp_Max = *max_element(tempMax.begin(), tempMax.end());
        float seuilTempMax = temp_Max * 1.15f;
        }

        if (!tempMoy.empty())
        {
        float temp_Moy = *max_element(tempMoy.begin(), tempMoy.end());
        float seuilTempMoy = temp_Moy * 1.15f;
        }



}

/*void Apprentissage::validerApprentissage(){

mysql_query(conn, "UPDATE Machine SET apprentissageTermineTemp = 1");

}*/

Apprentissage::~Apprentissage() {
}
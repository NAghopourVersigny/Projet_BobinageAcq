#include <algorithm>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include "../include/Apprentissage.h"
#include "../include/Camera.h"

using namespace std;

Apprentissage::Apprentissage()
{
    Camera* laCamera = new Camera("neco-10655D.local");
}
/*bool interrogationBDD(){

//Connex
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialisation
    conn = mysql_init(NULL);

    // Connexion à la BDD
    mysql_real_connect(conn, "localhost", "root", "adminECEI", "ProjetBobinageAcq", 0, NULL, 0);

    //Requete SQL
    mysql_query(conn, "SELECT apprentissageTermineTemp FROM Machine") == 0

}*/

void Apprentissage::lancerApprentissageTemp()
{

    int i;
    int temps;

    auto start = chrono::steady_clock::now();

    do
    {
        // Acquisition des températures
        float temperatureMoy = laCamera->obtenirTempMoy();
        float temperatureMax = laCamera->obtenirTempMax();

        // Ajouter les températures au tableau
        tempMoy.push_back(temperatureMoy);
        tempMax.push_back(temperatureMax);

        // Attendre 1 seconde entre chaque lecture
        sleep(1);

    } while (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count() < temps);
}

/*void validationApprentissage(){

mysql_query(conn, "UPDATE Machine SET apprentissageTermineTemp = 1");

}*/

void Apprentissage::determinerSeuilMax(vector<float> tempMax)
{
if (!tempMax.empty())
    {
        float temp_Max = *max_element(tempMax.begin(), tempMax.end());
        float seuilTempMax = temp_Max * 1.15f;
    }
}

void Apprentissage::determinerSeuilMoy(vector<float> tempMoy)
{
    if (!tempMoy.empty())
    {
        float temp_Moy = *max_element(tempMoy.begin(), tempMoy.end());
        float seuilTempMoy = temp_Moy * 1.15f;
    }
}
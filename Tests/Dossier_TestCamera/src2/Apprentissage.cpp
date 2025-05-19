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
/*void interrogationBDD(){

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

void Apprentissage::lancementApprentissageTemp()
{

    int i;
    int temps;
    vector<float> tableau(i);

    auto start = chrono::steady_clock::now();

    do
    {
        // Acquisition des températures
        float temperatureMoy = laCamera->obtenirTempMoy();
        float temperatureMax = laCamera->obtenirTempMax();

        // Ajouter les températures au tableau
        tableau.push_back(temperatureMoy);
        tableau.push_back(temperatureMax);

        // Attendre 1 seconde entre chaque lecture
        sleep(1);

    } while (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count() < temps);
}

/*void validationApprentissage(){

mysql_query(conn, "UPDATE Machine SET apprentissageTermineTemp = 1");

}*/

void Apprentissage::determinationSeuilMax()
{
}

void Apprentissage::determinationSeuilMoy()
{
}
#include <algorithm>
#include <iostream>
#include <chrono>
#include <unistd.h>
#include <mariadb/conncpp.hpp>
#include "../include/Apprentissage.h"
#include "../include/Camera.h"
#include "../include/Vibration.h"
#include "../include/DatabaseManager.h"

using namespace std;
using namespace sql;
using namespace mariadb;

Apprentissage::Apprentissage(bool apprentissageTemp, bool apprentissageVibra)
{

}

bool Apprentissage::interrogerBDDTemp()
{
    string SQLStringQuery = "SELECT apprentissageTermineTemp FROM Machine WHERE id = ?";
    DatabaseManager *leDatabaseManager = new DatabaseManager();
    leDatabaseManager->executerRequete(SQLStringQuery);

    return false;
}

void Apprentissage::lancerApprentissageTemp(Camera *laCamera, SeuilsIOT *lesSeuils)
{
    vector<float> tempMoy;
    vector<float> tempMax;
    float seuilTempMax;
    float seuilTempMoy;

    cin >> apprentissageTemp;
    if (apprentissageTemp == 0)
    {
        int temps;
        cin >> temps;

        auto start = chrono::steady_clock::now();

        do
        {
            float temperatureMoy = laCamera->obtenirTempMoy();
            float temperatureMax = laCamera->obtenirTempMax();

            tempMoy.push_back(temperatureMoy);
            tempMax.push_back(temperatureMax);

            sleep(1);

            if (!tempMax.empty())
            {
                float temp_Max = *max_element(tempMax.begin(), tempMax.end());
                seuilTempMax = temp_Max * 1.15f;
            }

            if (!tempMoy.empty())
            {
                float temp_Moy = *max_element(tempMoy.begin(), tempMoy.end());
                seuilTempMoy = temp_Moy * 1.15f;
            }

        } while (chrono::duration_cast<chrono::hours>(chrono::steady_clock::now() - start).count() < temps);
        lesSeuils->setSeuils_temperature(seuilTempMoy, seuilTempMax);
        cout << seuilTempMax << endl;
        cout << seuilTempMoy << endl;
    }
}

bool Apprentissage::validerApprentissageTemp()
{
    string SQLStringQuery = "UPDATE Machine SET apprentissageTermineTemp = 1 WHERE id = ?";
    DatabaseManager *leDatabaseManager = new DatabaseManager();
    leDatabaseManager->executerRequete(SQLStringQuery);

    return true;
}


/*
bool Apprentissage::interrogerBDDVibra()
{
    BDD *laBDD = new BDD();
    unique_ptr<Connection> conn = laBDD->SeConnecterBDD();

    unique_ptr<PreparedStatement> stmnt(conn->prepareStatement("SELECT apprentissageTermineVibra FROM Machine WHERE id = ?"));
    stmnt->setInt(1, 1);

    unique_ptr<ResultSet> res(stmnt->executeQuery());

    while (res->next())
    {
        return res->getBoolean(1);
    }

    return false;
}


void Apprentissage::lancerApprentissageVibra(vector<Vibration> lesVibrations, SeuilsIOT *lesSeuils)
{
    vector<float> TableauAxeX;
    vector<float> TableauAxeY;
    vector<float> TableauAxeZ;
    float seuilVibraX;
    float seuilVibraY;
    float seuilVibraZ;
    float seuilAxeX;
    float seuilAxeY;
    float seuilAxeZ;

    if (this->interrogerBDDVibra() == false)
    {
        int temps;
        cin >> temps;

        auto start = chrono::steady_clock::now();

        do
        {
            // Stockage des méthodes dans des variables

            (lesVibrations[0]).lire();
            TableauAxeX.push_back((lesVibrations[0]).getVitesseVibration());
            TableauAxeY.push_back((lesVibrations[1]).getVitesseVibration());
            TableauAxeZ.push_back((lesVibrations[2]).getVitesseVibration());

            sleep(1);

            if (!TableauAxeX.empty())
            {
                float AxeXMax = *max_element(TableauAxeX.begin(), TableauAxeX.end());
                seuilAxeX = AxeXMax;
            }

            if (!TableauAxeY.empty())
            {
                float AxeYMax = *max_element(TableauAxeY.begin(), TableauAxeY.end());
                seuilAxeY = AxeYMax;
            }

            if (!TableauAxeZ.empty())
            {
                float AxeZMax = *max_element(TableauAxeZ.begin(), TableauAxeZ.end());
                seuilAxeZ = AxeZMax;
            }
        } while (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start).count() < temps);
        lesSeuils->setSeuils_vibrations(seuilAxeX, seuilAxeY, seuilAxeZ);
    }
}

bool Apprentissage::validerApprentissageVibra()
{
    BDD *laBDD = new BDD();
    unique_ptr<Connection> conn = laBDD->SeConnecterBDD();

    unique_ptr<PreparedStatement> stmnt(conn->prepareStatement("UPDATE Machine SET apprentissageTermineVibra = 1 WHERE id = ?"));
    stmnt->setInt(1, 1);

    stmnt->execute();

    return true;
}
*/

Apprentissage::~Apprentissage()
{
}
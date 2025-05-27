#include "../include/Ambiance.h"
#include "../include/TempHumi.h"
#include "../include/bdd.h"
#include <iostream>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace std;
using namespace sql;
using namespace mariadb;

// Constructeur de la classe Ambiance. Il initialise l'I2C du capteur.
Ambiance::Ambiance(int addr)
{
    this->addr = addr;
}

int Ambiance::AcquérirAmbiance() {
    return 0;
}

int Ambiance::EnregistrerAmbiance() {
        BDD *laBDD = new BDD();
    unique_ptr<Connection> conn = laBDD->SeConnecterBDD();
    cout << "Préparation de la requête" << endl;

    unique_ptr<PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO Contexte (datetime, tempAmb, humidite) VALUES(?,?,?)"));
    stmnt->setInt(1, 1);

    cout << "Exécution de la requête" << endl;
    stmnt->execute();

    return true;
    
}

// Méthode qui retourne la valeur de la température
float Ambiance::getTemp()
{
    this->temp = temp;
    return temp; // Retourne la valeur de la température
}

// Méthode qui retourne la valeur d'humidité
float Ambiance::getHumidite()
{
    this->humidite = humidite;
    return humidite; // Retourne la valeur de l'humidité
} 
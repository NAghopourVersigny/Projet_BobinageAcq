#include <iostream>
#include <mariadb/conncpp.hpp>
#include "../include/DatabaseManager.h"

using namespace std;
using namespace sql;
using namespace mariadb;

DatabaseManager::DatabaseManager()
{
    this->url = SQLString("jdbc:mariadb://localhost:3306/bobinage");
}

string DatabaseManager::executerRequete(string StringQuery)
{

    SQLString conversion(StringQuery);
    DatabaseManager *leDatabaseManager = new DatabaseManager();

    unique_ptr<Connection> conn = leDatabaseManager->SeConnecterBDD();

    unique_ptr<PreparedStatement> stmnt(conn->prepareStatement(conversion));
    // stmnt->setInt(1, 1);

    stmnt->execute();

    cout << "executerRequete" << endl;

    return "OK";
}

SQLString DatabaseManager::getURL()
{

    return this->url;
}

unique_ptr<Connection> DatabaseManager::SeConnecterBDD()
{

    // Instantiate Driver
    Driver *driver = get_driver_instance();

    // Configure Connection
    Properties properties({{"user", "adminECEI"}, {"password", "adminECEI"}});

    // Establish Connection
    unique_ptr<Connection> conn(driver->connect(url, properties));

    cout << "Connexion réussie" << endl;

    return conn;
}
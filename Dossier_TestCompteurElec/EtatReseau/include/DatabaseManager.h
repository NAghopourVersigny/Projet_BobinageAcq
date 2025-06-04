#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>
#include <mariadb/conncpp.hpp>

using namespace std;
using namespace sql;

class DatabaseManager
{

private:
    SQLString url;

public:
    DatabaseManager();
    string executerRequete(string SQLStringQuery);
    SQLString getURL();
    unique_ptr<Connection> SeConnecterBDD();
};

#endif
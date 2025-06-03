#include <iostream>
#include <mariadb/conncpp.hpp>
#include "../include/bdd.h"


using namespace std;
using namespace sql;
using namespace mariadb;


BDD::BDD()
{
   this->url = SQLString("jdbc:mariadb://localhost:3306/Bobinage");
}


SQLString BDD::getURL()
{
   return this->url;
}


unique_ptr<Connection> BDD::SeConnecterBDD()
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

#include <iostream>
#include "../../../mariadb-connector-cpp-1.0.2-rhel9-amd64/include/mariadb/conncpp.hpp"
#include "../include/bdd.h"

using namespace std;
using namespace sql;
using namespace mariadb;

BDD::BDD(SQLString url){

this->url = url;
}

SQLString BDD::getURL(){

return this->url;

}

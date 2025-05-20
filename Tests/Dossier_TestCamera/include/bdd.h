#ifndef BDD_H
#define BDD_H

#include <string>
#include "../../../mariadb-connector-cpp-1.0.2-rhel9-amd64/include/mariadb/conncpp.hpp"

using namespace std;
using namespace sql;

class BDD{

private :

SQLString url;


public :

BDD(SQLString url);
SQLString getURL();


};


#endif
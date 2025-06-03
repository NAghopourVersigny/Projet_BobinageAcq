#ifndef BDD_H
#define BDD_H

#include <string>
#include <mariadb/conncpp.hpp>

using namespace std;
using namespace sql;

class BDD{

private :

SQLString url;


public :

BDD();
SQLString getURL();

unique_ptr<Connection> SeConnecterBDD();
};


#endif

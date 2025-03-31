#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <string>

using namespace std::chrono;
using namespace std;
namespace fs = std::filesystem;

class date
{
public:
time_t currentTime, creationTime;
tm* localTime, localCreationTime;
int annee, mois, jour;
system_clock::time_point now;


private:
date();
~date();

int annee_actuel();
int mois_actuel();
int jour_actuel();
time_t date_system();

int creation_annee();
int creation_mois();
int creation_jour();
time_t date_image();

}

#endif
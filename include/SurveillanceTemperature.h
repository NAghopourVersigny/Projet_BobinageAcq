#ifndef SURVEILLANCE_TEMPERATURE_H
#define SURVEILLANCE_TEMPERATURE_H

#include <thread>
#include <iomanip>        // std::put_time
#include <chrono>         // std::chrono::system_clock
#include <ctime>          // std::time_t, std::tm, std::localtime, std::mktime
#include <signal.h>
#include "Seuils.h"
#include "bdd.h"
#include "Camera.h"
#include "Contexte.h"

using namespace std;
using std::chrono::system_clock;

class SurveillanceTemperature 
{
private:
Camera * camera;
Base * base;
Seuils * seuils;
//std::atomic<bool> stop_threads(false);

public:
SurveillanceTemperature(string hostname);
~SurveillanceTemperature();

void surveillance();

thread renvoie_surveillance();

bool tester_seuil();

string date();

void determiner_seuils();
void calculer_seuils(float &moy, float &max);
//void handle_signal(int sig);


};
#endif

#include "../include/Seuils.h"
#include <iostream>

Seuils::Seuils()
{
    this->seuilTempMax;
    this->seuilTempMoy;
}

Seuils::~Seuils() {}

void Seuils::setSeuils_temperature(float valMoy, float valMax, int idMachine) {
    seuilTempMoy = valMoy;
    seuilTempMax = valMax;
}

float Seuils::getTempMax() {
    return seuilTempMax;
}

float Seuils::getTempMoy() {
    return seuilTempMoy;
}

float Seuils::getSeuilAlerteVibX() {
    return seuilAlerteVibX;
}

void Seuils::setSeuilAlerteVibX(float seuilAlerteVibX) {
    this->seuilAlerteVibX = seuilAlerteVibX;
}

float Seuils::getSeuilAlarmeVibX() {
    return seuilAlarmeVibX;
}

void Seuils::setSeuilAlarmeVibX(float seuilAlarmeVibX) {
    this->seuilAlarmeVibX = seuilAlarmeVibX;
}

float Seuils::getSeuilAlerteVibY() {
    return seuilAlerteVibY;
}

void Seuils::setSeuilAlerteVibY(float seuilAlerteVibY) {
    this->seuilAlerteVibY = seuilAlerteVibY;
}

float Seuils::getSeuilAlarmeVibY() {
    return seuilAlarmeVibY;
}

void Seuils::setSeuilAlarmeVibY(float seuilAlarmeVibY) {
    this->seuilAlarmeVibY = seuilAlarmeVibY;
}

float Seuils::getSeuilAlerteVibZ() {
    return seuilAlerteVibZ;
}

void Seuils::setSeuilAlerteVibZ(float seuilAlerteVibZ) {
    this->seuilAlerteVibZ = seuilAlerteVibZ;
}

float Seuils::getSeuilAlarmeVibZ() {
    return seuilAlarmeVibZ;
}

void Seuils::setSeuilAlarmeVibZ(float seuilAlarmeVibZ) {
    this->seuilAlarmeVibZ = seuilAlarmeVibZ;
}

void Seuils::enregistrer(DatabaseManager *db)
{
    this->enregistrer(db);
}

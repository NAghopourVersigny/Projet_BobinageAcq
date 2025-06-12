#ifndef SEUILS_H
#define SEUILS_H

#include "DatabaseManager.h"

class Seuils 
{
private:
    
    float seuilTempMax = 0;
    float seuilTempMoy = 0;
    float seuilAlerteVibX = 0;
    float seuilAlerteVibY = 0;
    float seuilAlerteVibZ = 0;
    float seuilAlarmeVibX = 0;
    float seuilAlarmeVibY = 0;
    float seuilAlarmeVibZ = 0;

public:

    Seuils();
    ~Seuils();

    void setSeuils_temperature(float valMoy, float valMax, int idMachine);
    
    float getTempMax();
    float getTempMoy();

    float getSeuilAlerteVibX();
    void setSeuilAlerteVibX(float seuilAlerteVibX);
    float getSeuilAlarmeVibX();
    void setSeuilAlarmeVibX(float seuilAlarmeVibX);
    float getSeuilAlerteVibY();
    void setSeuilAlerteVibY(float seuilAlerteVibY);
    float getSeuilAlarmeVibY();
    void setSeuilAlarmeVibY(float seuilAlarmeVibY);
    float getSeuilAlerteVibZ();
    void setSeuilAlerteVibZ(float seuilAlerteVibZ);
    float getSeuilAlarmeVibZ();
    void setSeuilAlarmeVibZ(float seuilAlarmeVibZ);

    void enregistrer(DatabaseManager *db);

};
#endif

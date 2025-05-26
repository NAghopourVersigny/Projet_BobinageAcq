#ifndef SEUILS_H
#define SEUILS_H


class SeuilsIOT 
{
private:
    float seuilTempMax, seuilTempMoy;
    float AlerteVibX, AlerteVibY, AlerteVibZ;
    float AlarmeVibX, AlarmeVibY, AlarmeVibZ;
    
public:
    SeuilsIOT();
    ~SeuilsIOT();
    /**
     * @brief Set the Seuils temperature object
     * 
     * @param valMoy 
     * @param valMax 
     */
    void setSeuils_temperature(float valMoy, float valMax);
    float getSeuilTempMax();
    float getTempMax();
    void setSeuilTempMax(float seuilTempMax);
    float getSeuilTempMoy();
    void setSeuilTempMoy(float seuilTempMoy);
    float getTempMoy();
    



    void setSeuils_vibrations(float seuilAxeX, float seuilAxeY, float seuilAxeZ);
    float getSeuilAlertVibX();
    void setSeuilAlerteVibX(float seuilAlerteVibX);
    float getSeuilAlarmeVibX();
    void setSeuilAlarmeVibX(float seuilAlarmeVibX);
    float getSeuilAlertVibY();
    void setSeuilAlerteVibY(float seuilAlerteVibY);
    float getSeuilAlarmeVibY();
    void setSeuilAlarmeVibY(float seuilAlarmeVibY);
    float getSeuilAlertVibZ();
    void setSeuilAlerteVibZ(float seuilAlerteVibZ);
    float getSeuilAlarmeVibZ();
    void setSeuilAlarmeVibZ(float seuilAlarmeVibZ);
};
#endif
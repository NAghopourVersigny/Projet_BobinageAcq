#ifndef SEUILS_H
#define SEUILS_H


class SeuilsIOT 
{
private:
    float seuilTempMax, seuilTempMoy;
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
    float getTempMax();
    float getTempMoy();
    

    void setSeuils_vibrations(float seuilAxeX, float seuilAxeY, float seuilAxeZ);
    float getTempMax();
    float getTempMoy();
};
#endif

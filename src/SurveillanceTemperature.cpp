
#include "../include/SurveillanceTemperature.h"

SurveillanceTemperature::SurveillanceTemperature(string hostname)
{
    this->camera = new Camera(hostname);
    this->base = new Base();
    this->seuils = new Seuils();
}

SurveillanceTemperature::~SurveillanceTemperature()
{
    delete camera;
    delete seuils;
}

/*Surveillance est une boucle infini avec une période de tous les 5 minutes
 */
void SurveillanceTemperature::surveillance()
{

    if (!base->obtenirApprentissageTemp(1))
    {
        determiner_seuils();
    }

    do
    {
        std::this_thread::sleep_for(std::chrono::minutes(5)); // Cette ligne permet de mettre en pause la boucle pendant 5 minutes
        float tempMoy = camera->obtenirTempMoy();
        float tempMax = camera->obtenirTempMax();
        if ((tempMoy > seuils->getTempMoy()) || (tempMax > seuils->getTempMax()))
        {

            camera->capturer_Image();
            camera->recuperer_Image();
            string laDate = date();
            Image *limage = new Image(camera->obtenir_nom_image(), "thermal", laDate);
            Temperature *laTempMoy = new Temperature(tempMoy, laDate);
            Contexte *leContexte = new Contexte();
            /*leContexte->obtenirContexte();
            string nom=limage->getNom();
            string type=limage->getType();
            base->ajouterImage(laDate,nom,type,1);*/
            if (tempMoy > seuils->getTempMoy())
                base->ajouterListeEven(laDate, "température moyenne dépassée", laTempMoy, leContexte, limage, 1);
            else
                base->ajouterListeEven(laDate, "température maximale dépassée", laTempMoy, leContexte, limage, 1);
        }
        else
        {
            base->ajouterDataFonctTemp(date(), tempMoy, 1);
        }
    } while (true);
}

/*Permet d'utiliser la méthode surveillance en thread*/
thread SurveillanceTemperature::renvoie_surveillance()
{
    return thread(&SurveillanceTemperature::surveillance, this);
}

string SurveillanceTemperature::date()
{

    time_t now = time(0); // get current dat/time with respect to system
    tm *ltm = localtime(&now);

    string date = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday) +
                  " " + to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
    return date;
}

void SurveillanceTemperature::determiner_seuils()
{
    int compteur = 0;
    float NewTempMax = 0;
    float tempMax = 0;
    float NewTempMoy = 0;
    float tempMoy = 0;
    do
    {
        std::this_thread::sleep_for(std::chrono::minutes(5));
        tempMax = camera->obtenirTempMax();
        if (tempMax > NewTempMax)
        {
            NewTempMax = tempMax;
        }
        tempMoy = camera->obtenirTempMoy();
        base->ajouterDataFonctTemp(date(), tempMoy, 1);
        if (tempMoy > NewTempMoy)
        {
            NewTempMoy = tempMoy;
        }
        compteur += 1;
        cout << "Compteur:" << compteur << endl;
    } while (compteur < 10);
    calculer_seuils(NewTempMoy, NewTempMax);
}

void SurveillanceTemperature::calculer_seuils(float &moy, float &max)
{
    float seuil_moy = moy + (moy * 0.05);
    float seuil_max = max + (max * 0.05);
    seuils->setSeuils_temperature(seuil_moy, seuil_max, 1);
}
/*
//à continuer demain matin
thread Base::renvoie_base_supprimer()
{
    return thread(&Base::supprimer, this);
}
*/

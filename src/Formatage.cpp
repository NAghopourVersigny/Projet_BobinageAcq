#include "../include/Formatage.h"

string Formatage::mettreEnFormeTemp(list<Temperature> *liste)
{
    /*          Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
            ostringstream oss;
            string response = "{\"dateTempMachine\":\n\t[";

            for (auto it = liste->begin(); it != liste->end(); ++it)
            {

                string time = it->getDateHeure();
                float laTemp = it->getValeur();
                Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
                ostringstream oss;
                response += "\n\t\t";
                json->set("tempMachine", laTemp);
                json->set("date", time);
                Poco::JSON::Stringifier::stringify(json, oss);
                response += oss.str();
                response += ",";
            }

            response = response.substr(0, response.length() - 1);
            response += "\n\t]\n}";

            return response;
          */
    string result = "";
    if (!liste->empty())
    {
        Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
        ostringstream response;
        response << "{\"dateTempMachine\":\n\t[";

        for (auto it = liste->begin(); it != liste->end(); ++it)
        {

            string time = it->getDateHeure();
            float laTemp = it->getValeur();

            Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
            ostringstream tempOss;
            json->set("tempMachine", laTemp);
            json->set("date", time);
            Poco::JSON::Stringifier::stringify(json, tempOss);
            response << "\n\t\t" << tempOss.str() << ",";
        }
        result = response.str();


        result.pop_back();
        result += "\n\t]\n}";
    }
    else
    {
        string time = "0000-00-00 00:00:00";
        float laTemp = 0;
        ostringstream response;

        Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
        ostringstream tempOss;
        json->set("tempMachine", laTemp);
        Poco::JSON::Stringifier::stringify(json, tempOss);
        json->set("date", time);
        Poco::JSON::Stringifier::stringify(json, tempOss);
        response << "\n\t\t" << tempOss.str();
        string result = response.str();

        result.pop_back();
        result += "\n\t]\n}";
    }
    return result;
}
string Formatage::mettreEnFormeVibra(list<Vibration> *liste)
{
}
string Formatage::mettreEnFormeCont(list<Contexte> *liste)
{
}
string Formatage::mettreEnFormeEven(list<Evenement> *liste)
{
   string result = "";
    if (!liste->empty())
    {
        Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
        ostringstream response;
        response << "{\"dateEventMachine\":\n\t[";

        for (auto it = liste->begin(); it != liste->end(); ++it)
        {

            string time = it->getDateHeure();
            string leType = it->getType();

            Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
            ostringstream tempOss;
            json->set("type", leType);
            json->set("date", time);
            Poco::JSON::Stringifier::stringify(json, tempOss);
            response << "\n\t\t" << tempOss.str() << ",";
        }
        result = response.str();


        result.pop_back();
        result += "\n\t]\n}";
    }
    else
    {
        string time = "0000-00-00 00:00:00";
        string leType  = "no event";
        ostringstream response;

        Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
        ostringstream tempOss;
        json->set("type", leType);
        Poco::JSON::Stringifier::stringify(json, tempOss);
        json->set("date", time);
        Poco::JSON::Stringifier::stringify(json, tempOss);
        response << "\n\t\t" << tempOss.str();
        string result = response.str();

        result.pop_back();
        result += "\n\t]\n}";
    }
    return result;    
}
string Formatage::mettreEnFormeImage(list<Image> *liste)
{
}
Formatage::Formatage()
{
}
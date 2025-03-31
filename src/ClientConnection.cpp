#include <iostream>
#include <limits>
#include <fstream>
#include <syslog.h>

#include "../include/ClientConnection.h"

using namespace std;

void ClientConnection::run()
{
    StreamSocket &ss = socket();
    try
    {
        char buffer[256];
        int n = ss.receiveBytes(buffer, sizeof(buffer));
        while (n > 0)
        {
            string message = buffer;
            string response;
            cout << "Le message reçu est : " << message << endl;

            memset(buffer, 0, sizeof(buffer));

            size_t found = message.find("getTempData");
            if (found != string::npos)
            {
                list<Temperature> *lesTepmperatures = base->obtenirDataFonctTemp("", "", 1);
                response = leformatage->mettreEnFormeTemp(lesTepmperatures);
            }

            found = message.find("getVibrationData");
            if (found != string::npos)
            {
                list<Vibration> *lesVibrationss = base->obtenirDataFonctVibra("", "", 1);
                response = leformatage->mettreEnFormeVibra(lesVibrationss);
            }

            ss.sendBytes(response.c_str(), response.length());

            n = ss.receiveBytes(buffer, sizeof(buffer));
        }
    }
    catch (Exception &exc)
    {
        cerr << "ClientConnection: " << exc.displayText() << endl;
    }
}
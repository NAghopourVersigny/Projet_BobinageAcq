#include <iostream>
#include <limits>
#include <fstream>
#include <syslog.h>

// #include "../include/ClientConnection.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/NumberParser.h"
#include "Poco/Logger.h"
#include "Poco/Process.h"
#include "Poco/NamedEvent.h"

#include "../include/FLIRAX8.h"
#include "../include/Camera.h"
#include "../include/SurveillanceTemperature.h"
#include "../include/bdd.h"
#include "../include/Formatage.h"

using namespace std;

using Poco::Event;
using Poco::Exception;
using Poco::Logger;
using Poco::NamedEvent;
using Poco::NumberParser;
using Poco::Process;
using Poco::ProcessImpl;
using Poco::UInt16;
using Poco::Net::StreamSocket;
using Poco::Net::TCPServer;
using Poco::Net::TCPServerConnection;
using Poco::Net::TCPServerConnectionFactory;
using Poco::Net::TCPServerConnectionFactoryImpl;
using Poco::Net::TCPServerConnectionFilter;

namespace
{
    class ClientConnection : public TCPServerConnection
    {
    private:
        Base *base;
        Formatage *leformatage;

    public:
        ClientConnection(const StreamSocket &s) : TCPServerConnection(s)
        {
            base = new Base();            
        }

        void run()
        {
            StreamSocket &ss = socket();
            try
            {
                char buffer[2569536];
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
                                cout<<"getTempData found"<<response<<endl;
                     
                    }

                    found = message.find("getVibrationData");
                    if (found != string::npos)
                    {
                        list<Vibration> *lesVibrationss = base->obtenirDataFonctVibra("", "", 1);
                        response = leformatage->mettreEnFormeVibra(lesVibrationss);
                    }
                    found = message.find("getEven");
                    if (found != string::npos)
                    {
                        list<Evenement> *lesEvenements = base->obtenirListeEven("", "", 1);
                        response = leformatage->mettreEnFormeEven(lesEvenements);
                    }
    cout<<response<<"*"<<response.length()<<endl;
                    ss.sendBytes(response.c_str(), response.length());

                    n = ss.receiveBytes(buffer, sizeof(buffer));
                }
            }
            catch (Exception &exc)
            {
                cerr << "ClientConnection: " << exc.displayText() << endl;
            }
        }
    };
    typedef TCPServerConnectionFactoryImpl<ClientConnection> TCPFactory;
    Event terminator;
}

int main()
{
	Base * base = new Base();
	//base->supprimer();
        SurveillanceTemperature *surveillancetemp = new SurveillanceTemperature("neco-10655D.local"); //neco-105F68.local
    // SurveillanceVibration * surveillancevibration = new SurveillanceVibration();
    thread temp = surveillancetemp->renvoie_surveillance();
    std::thread supp=base->renvoie_supprimer();
    // thread vibr = surveillancevibration-> surveillance();
    try
    {
        Poco::UInt16 port = 2053;
        TCPServer srv(new TCPFactory(), port);
        srv.start();
        cout << "TCP server listening on port " << port << '.'
             << endl
             << "Press Ctrl-C to quit." << endl;
        terminator.wait();
    }
    catch (Exception &exc)
    {
        cerr << exc.displayText() << endl;
        return 1;
    }
    supp.join();
    temp.join();
    // vibr.join()
    return 0;
}

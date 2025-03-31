#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/NumberParser.h"
#include "Poco/Logger.h"
#include "Poco/Process.h"
#include "Poco/NamedEvent.h"
#include "bdd.h"
#include "Formatage.h"

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

using namespace std;

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

        void run();
    };
    typedef TCPServerConnectionFactoryImpl<ClientConnection> TCPFactory;
    Event terminator;
}

#endif
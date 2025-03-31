#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/Object.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Stringifier.h"

using namespace std;
using namespace cgicc;

int main()
{

    string server = "127.0.0.1";
    int port = 2053;
    string message = "getEven";

    Poco::Net::SocketAddress address(server, port);
    Poco::Net::StreamSocket socket(address);

    socket.sendBytes(message.c_str(), message.length());

    char buffer[2569536];
    int n = socket.receiveBytes(buffer, sizeof(buffer));
    message = string(buffer);
    size_t found = message.find("\n\t]\n}");
    if (found!=std::string::npos)
        message = message.substr(0, found+5);

    cout << HTTPHTMLHeader();

    cout << message << endl;

    return 0;
}

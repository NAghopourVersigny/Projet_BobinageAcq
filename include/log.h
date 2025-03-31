#ifndef LOG_H
#define LOG_H

#include <time.h>
#include <string>
#include "../include/CkSsh.h"
#include "../include/CkScp.h"
using namespace std;



/// Structure DateTime
/// Structure pour stocker la Date et l’heure de la connexion
typedef struct _SshDateTime
    {
    string date;
    int hour;
    int minute;
    int seconnd;

    } 	SshDateTime;


/// Structure SSHLoggin
/// Structure pour stocker les éléments concernant les log de connexion SSH
typedef struct _SSHLogging
    {
    SshDateTime _dateTime;
    string hostname;
    string username;
    string sshUser;
    string sshHost;
    int sshPortNumber;

    } 	SSHLogging;

int extrairesudoLog(string nomHote);

int extrairesshLog(string nomHote);

int enregistrerSSHLog(SSHLogging sshlog );


int recupererAuthLog(string nomHote, const char * login, const char * password , const char * cheminFichierDistant);

#endif

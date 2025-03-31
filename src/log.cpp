#include <iostream>
#include <fstream>
#include <string>
#include "../include/log.h"

int extrairesudoLog(string nomHote)
{
	ifstream leFichier;
	string substring = "sudo";
	string nomJournal = nomHote + ".log";
	string x;

	leFichier.open(nomJournal, std::fstream::in | std::fstream::out | std::fstream::app);
	if (leFichier.is_open()) // is_open open the text file.
	{





		leFichier.close(); // to close text file.
		return 1;
	}
	else
		return -1;
}

int extrairesshLog(string nomHote)
{
	ifstream leFichier;
	ofstream logsSSH;
	string substring = "ssh";
	string nomJournal = nomHote + ".log";
	string nomJournalSSH = nomHote + "SSH.log";
	string x;
	bool ans = false;

	leFichier.open(nomJournal, std::fstream::in | std::fstream::app);
	logsSSH.open(nomJournalSSH, std::fstream::out | std::fstream::app);
	if (leFichier.is_open()) // is_open open the text file.
	{
		if (logsSSH.is_open()) // is_open open the text file.
		{









			logsSSH.close();
		}

		leFichier.close(); // to close text file.
		return 1;
	}
	else
		return -1;
}

int enregistrerSSHLog(SSHLogging sshlog)
{
}

int recupererAuthLog(string nomHote, const char *login, const char *password, const char *cheminFichierDistant)
{

	CkSsh ssh;
	char message[50];
	ifstream leFichier;
	string nomJournal = nomHote + ".log";
	nomHote = nomHote + ".local";
	// Hostname may be an IP address or hostname:
	const char *hostname = nomHote.c_str();

	int port = 22;

	// Connect to an SSH server:
	bool success = ssh.Connect(hostname, port);
	if (success != true)
	{
		//       std::cout << ssh.lastErrorText() << "\r\n";
		return -1;
	}

	// Wait a max of 5 seconds when reading responses..
	ssh.put_IdleTimeoutMs(5000);

	// Authenticate using login/password:
	success = ssh.AuthenticatePw(login, password);
	if (success != true)
	{
		//        std::cout << ssh.lastErrorText() << "\r\n";
		return -1;
	}

	// Once the SSH object is connected and authenticated, we use it
	// in our SCP object.
	CkScp scp;

	success = scp.UseSsh(ssh);
	if (success != true)
	{
		//       std::cout << scp.lastErrorText() << "\r\n";
		return -1;
	}
	leFichier.open(nomJournal, std::fstream::in | std::fstream::out | std::fstream::app);
	const char *remotePath = cheminFichierDistant;
	const char *localPath = nomJournal.c_str();
	success = scp.DownloadFile(remotePath, localPath);
	// system("tail -n20 *.log");
	if (success != true)
	{
		std::cout << scp.lastErrorText() << "\r\n";
		return -1;
	}

	// Disconnect
	ssh.Disconnect();
	return 1;
}

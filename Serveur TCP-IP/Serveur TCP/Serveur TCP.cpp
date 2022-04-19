// MySqlTest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstring>
#include <WS2tcpip.h>
#include <stdlib.h>
#include <ctime>
#include "jdbc/cppconn/prepared_statement.h"
#include "jdbc/cppconn/driver.h"
#include "jdbc/cppconn/exception.h"
#include "jdbc/mysql_connection.h"
#include <n>

#pragma comment (lib, "ws2_32.lib")

using namespace std;
//using namespace rapidjson;
int qstate;

struct Pongiste {
	string idPongiste;
	string email;
	string nom;
	string prenom;
	string mdp;
	int Entraineur_idEntraineur;
};

struct Entraineur {
	int idEntraineur;
	char email[256];
	char nom[256];
	char prenom[256];
	char mdp[256];
};

struct Partie {
	int idPartie;
	int nbrBalle;
	int frequence;
	int vitesse;
	char email[256];
	char zoneEnvoie[256];
	char zoneRetour[256];
	float tauxDeReussite;
	int Entraineur_idEntraineur;
	int Pongiste_idPongiste;
};

Pongiste pongiste;
Entraineur entraineur;
Partie partie;

const string server = "localhost:3306";
const string username = "root";
const string password = "root";

void main() {

	//initialisé winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);

	//initialisé la BDD
	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;


	if (wsOk != 0) {
		cerr << "Can't Initialize winsock ! Quitting" << endl;
		return;
	}

	//crée une socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket ! Quitting" << endl;
		return;
	}

	//Bind une adresse ip et un numero de port à une socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	//Dire a winsock que la socket est faite pour écouter
	listen(listening, SOMAXCONN);

	//Attendre une connection
	sockaddr_in client;
	int clientSize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

	char host[NI_MAXHOST];		//Client's remote name
	char service[NI_MAXSERV];	//Service (i.e. port) the client is connect on

	memset(host, 0, NI_MAXHOST); //Same as a 
	memset(service, 0, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		cout << host << " connect on port " << service << endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << "connect on port" << ntohs(client.sin_port) << endl;
	}

	//Fermer la socket d'ecoute
	closesocket(listening);

	//boucle while : accepter et echo le message au client
	char buf[4096];

	while (true)
	{
		memset(buf, 0, 4096);

		try
		{
			driver = get_driver_instance();
			//for demonstration only. never save password in the code!
			con = driver->connect(server, username, password);
		}
		
		catch (sql::SQLException e)
		{
			cout << "Could not connect to server. Error message: " << e.what() << endl;
			system("pause");
			exit(1);
		}
		
		con->setSchema("testsensorpong");
			//Attendre que le client envoie des données
			int bytesReceived = recv(clientSocket, buf, 4096, 0);

			/*if (bytesReceived > 0)
				{
					cout << "donnees recues : " << buf << endl;
					//Send the message back to client
					//printf("données reçues : %s ", buf);
			}*/

			if (bytesReceived == SOCKET_ERROR)
			{
				cerr << "Error in recv(). Quitting" << endl;
				break;
			}

			if (bytesReceived == 0)
			{
				cout << "Client disconnected " << endl;
				break;
			}
			// Echo le message au client

			//char message[] = "p";

			if (strcmp(buf, "p") == 0) {

				pstmt = con->prepareStatement("SELECT idJoueur, email, nom, prenom, mdp FROM sensorpong.joueur");
				result = pstmt->executeQuery();

				while (result->next()) {		

					int i = 0;
					//int tab[10];
					/*map<int, int> tab{{0,map<string,int> { {"Prénom",1}}},{0,map<string,int> { {"Prénom",1}}},{0,map<string,int> { {"Prénom",1}}}};
					cout << tab[0]["Prenom"] << "\n";*/

					pongiste.idPongiste = result->getString(1).c_str();
					pongiste.email = result->getString(2).c_str();
					pongiste.nom = result->getString(3).c_str();
					pongiste.prenom = result->getString(4).c_str();
					pongiste.mdp = result->getString(5).c_str();

					//const char* joueur = {"ID": pongiste.idPongiste , "email" : +pongiste.email + , "nom" : +pongiste.nom + , "prenom" : +pongiste.prenom + , "mdp " : +pongiste.mdp + };

					//auto json = "{"firstName":"Sean","lastName":"Brown","empId":21453,"department":"Computer"}";

	

					//cout << json;

					//char* val = json;

					send(clientSocket, json, sizeof(json), 0);
					
				}
				
			}

		
	}

	//supprimer une socket
	closesocket(clientSocket);

	//fermer winsock
	WSACleanup();
}
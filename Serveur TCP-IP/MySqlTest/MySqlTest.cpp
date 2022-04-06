// MySqlTest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstring>
#include <WS2tcpip.h>
#include <mysql.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;
int qstate;

void main() {

	//initialisé winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);

	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "root", "sensorpong", 3306, NULL, 0);

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

		ZeroMemory(buf, 4096);

		if (conn) {
			puts("Successful connection to database!");

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

			char message[] = "Pongiste";

			if (strcmp(buf, message) == 0) {

				cout << "Affiche l'historique des joueurs" << endl;
				string query = "SELECT * FROM sensorpong.joueur";
				const char* q = query.c_str();
				qstate = mysql_query(conn, q);

				if (!qstate)
				{
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res))
					{
						printf("ID: %s, Email: %s, Nom: %s, Prenom: %s, Password: %s\n", row[0], row[1], row[2], row[3], row[4], row[5]);
					}
				}
				else
				{
					cout << "Query failed: " << mysql_error(conn) << endl;
				}

			}

		}
		else {
			puts("Connection to database has failed!");

		}
	}

	//supprimer une socket
	closesocket(clientSocket);

	//fermer winsock
	WSACleanup();
}

/*#include <mysql.h>
#include <iostream>

using namespace std;
int qstate;

int main()
{
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "root", "sensorpong", 3306, NULL, 0);

	if (conn) {
		puts("Successful connection to database!");

		string query = "SELECT * FROM sensorpong.joueur";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				printf("ID: %s, Email: %s, Nom: %s, Prenom: %s, Password: %s\n", row[0], row[1], row[2], row[3], row[4], row[5]);
			}
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}
	}
	else {
		puts("Connection to database has failed!");
	}

	return 0;
}*/
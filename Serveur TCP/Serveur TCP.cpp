#include <iostream>
#include <WS2tcpip.h>
#include "test.h"

#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main() {
	
	//initialisé winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);


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
	sockaddr_in adress;
	adress.sin_family = AF_INET;
	adress.sin_port = htons(54000);
	adress.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton

	bind(listening, (sockaddr*)&adress, sizeof(adress));

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

		//Attendre que le client envoie des données
		int bytesReceived = recv(clientSocket, buf, 4096, 0);

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

		if (strcmp(buf, "{\"ConnexionUser\":{\"email\":\"kylian.alger-leonard@lycee-jeanrostand.fr\",\"mdp\":\"147852\"}}") == 0) {
			//cout << "coucou\n";
			//char msg_rcv[] = "{\"ConnexionUser\":{\"email\":\"kylian.alger-leonard@lycee-jeanrostand.fr\",\"mdp\":\"147852\"}}";
			//cout << msg_rcv;
			string msg_s = test(buf);

			//cout << msg_s << endl;
			//cout << sizeof(msg_s) << endl;
			//cout << msg_s.c_str() << endl;

			char* tab2 = new char[msg_s.length() + 1];
			strcpy(tab2, msg_s.c_str());

			send(clientSocket, tab2, sizeof(tab2), 0);
			
		}

		/*if (strcmp(buf, "H") == 0) {
			cout << "salut\n";
			char msg_rcv[] = "{\"ConnexionAdmin\":{\"email\":\"ahmedsalih.hazim@gmail.com\",\"mdp\":\"1234\"}}";
			//cout << msg_rcv;
			test2(msg_rcv);
			cout << test2(msg_rcv);

			send(clientSocket, msg_rcv, sizeof(msg_rcv), 0);

		}*/

	}


	//supprimer une socket
	closesocket(clientSocket);

	//fermer winsock
	WSACleanup();
}
#include <iostream>
#include <WS2tcpip.h>
#include "requete.h"

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
	char msgRcv[4096];
	char error[] = "Erreur";
	//char error[] ="Erreur";

	while (true)
	{
		memset(msgRcv, 0, 4096);

		//Attendre que le client envoie des données
		int bytesReceived = recv(clientSocket, msgRcv, 4096, 0);

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

		//Condition pour la création d'un profil utilisateur
		if (strstr(msgRcv, "CreerCompte") != NULL) {

			creationUser(msgRcv);

		}

		//Condition pour la reception des données pour la connexion du joueur
		if (strstr(msgRcv, "ConnexionUser") != NULL) {

			string json = connexionUser(msgRcv);

			char* msg = new char[json.size() + 1];
			copy(json.begin(), json.end(), msg);
			msg[json.size()] = '\0';

			int size_msg = json.size();
			if (strcmp(msg, "{\"ConnexionUser\":}") == 0) {
				send(clientSocket, error, sizeof(error), 0);
			}
			else {
				send(clientSocket, msg, size_msg, 0);
			}

		}

		//Condition pour la reception des données pour la connexion de l'entraineur
		if (strstr(msgRcv, "ConnexionAdmin") != NULL) {

			string json = connexionAdmin(msgRcv);

			char* msg = new char[json.size() + 1];
			copy(json.begin(), json.end(), msg);
			msg[json.size()] = '\0';

			int size_msg = json.size();

			if (strcmp(msg, "{\"ConnexionAdmin\":}") == 0) {
				send(clientSocket, error, sizeof(error), 0);
			}
			else {
				send(clientSocket, msg, size_msg, 0);
			}

		}

		//Boucle pour la reception et l'envoie des données de l'historique complet d'un joueur
		if (strstr(msgRcv, "HistoriqueJoueurC") != NULL) {

			string json = HistoriqueJoueurC(msgRcv);

			char* msg = new char[json.size() + 1];
			copy(json.begin(), json.end(), msg);
			msg[json.size()] = '\0';

			int size_msg = json.size();

			send(clientSocket, msg, size_msg, 0);
		}

		//Condition pour la reception et l'envoie des données de l'historique des 10 dernieres partie d'un joueur en fonction de la configuration
		if (strstr(msgRcv, "HistoriqueJoueur") != NULL) {

			string json = HistoriqueJoueur(msgRcv);

			char* msg = new char[json.size() + 1];
			copy(json.begin(), json.end(), msg);
			msg[json.size()] = '\0';

			int size_msg = json.size();

			if (strcmp(msg, "{\"HistoriqueJoueur\":}") == 0) {
				send(clientSocket, error, sizeof(error), 0);
			}
			else {
				send(clientSocket, msg, size_msg, 0);
			}
		}

		//Condition pour la reception et l'envoie des données de l'historique complet des joueurs
		if (strstr(msgRcv, "HistoriqueComplet") != NULL) {

			string json = HistoriqueComplet(msgRcv);

			char* msg = new char[json.size() + 1];
			copy(json.begin(), json.end(), msg);
			msg[json.size()] = '\0';

			int size_msg = json.size();		

		}

		//Condition pour la reception et l'envoie des données de la liste des joueurs
		if (strstr(msgRcv, "ListeJoueurs") != NULL) {

			string json = ListeJoueurs(msgRcv);

			char* msg = new char[json.size() + 1];
			copy(json.begin(), json.end(), msg);
			msg[json.size()] = '\0';

			int size_msg = json.size();

			send(clientSocket, msg, size_msg, 0);

		}

		

		if (strstr(msgRcv, "GameStart") != NULL) {

			string json = GameStart(msgRcv);

			char* msg = new char[json.size() + 1];
			copy(json.begin(), json.end(), msg);
			msg[json.size()] = '\0';

			int size_msg = json.size();

			
		}

		//Condition pour enregistrer la partie d'un joueur
		if (strstr(msgRcv, "EnregistrerPartie") != NULL) {

			enregistrerPartie(msgRcv);

		}

		//Condition pour la mise à jour du profil d'un utilisateur
		if (strstr(msgRcv, "UpdateUser") != NULL) {

			UpdateUser(msgRcv);

		}

		//Condition pour la suppresion d'un utilisateur et de ces parties
		if (strstr(msgRcv, "DeleteUser") != NULL) {

			DeleteUser(msgRcv);

		}
	}

	//supprimer une socket
	closesocket(clientSocket);

	//fermer winsock
	WSACleanup();
}
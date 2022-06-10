#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h> 
#include <netinet/in.h> 
#include <unistd.h>
#include <arpa/inet.h> 
#include "requete.h"
  
using namespace std;

int main() {
	printf("Processus SERVEUR \n \n");
	int listening;
	int clientSocket;
	struct sockaddr_in adress;
	socklen_t longueurAdresse;
	// Crée un socket de communication
	listening = socket(AF_INET, SOCK_STREAM, 0);
	// Teste la valeur renvoyée par l’appel système socket()
	if (listening < 0) {
		perror("socket"); // Affiche le message d’erreur
		exit(-1); // On sort en indiquant un code erreur
	}
	printf("Socket créée avec succès ! numeor descripteur socket %d \n", listening);
	//--- Début de l’étape n°2 :
	// Obtient la longueur en octets de la structure sockaddr_in
	longueurAdresse = sizeof(adress);
	// Initialise à 0 la structure sockaddr_in
	memset(&adress, 0x00, longueurAdresse);
	// Renseigne la structure sockaddr_in avec les informations du serveur distant
	adress.sin_family = AF_INET;
	// On choisit le numéro de port d’écoute du serveur
	adress.sin_port = htons(5000); // = 5000
	// On choisit l’adresse IPv4 du serveur
	inet_aton("localhost", &adress.sin_addr); // à modifier selon ses besoins


	//bind une adresse

	if (bind(listening, (struct sockaddr*)&adress, longueurAdresse) == -1)
	{
		perror("echec bind \n");
		close(listening);
		exit(-1);
	}

	printf("récupération du port TCP 5000 du serveur OK \n");

	//listen to connection
	if (listen(listening, 10) == -1)
	{
		perror("erreur dans l'écoute listen");
		close(listening);
		exit(-1);
	}

	printf("serveur en écoute \n");


	//préparation de la struture pour récupérer l'adresse du client
	struct sockaddr_in pointRencontreClient;
	longueurAdresse = sizeof(pointRencontreClient);
	// Initialise à 0 la structure sockaddr_in pour le client
	memset(&adress, 0x00, longueurAdresse);

	clientSocket = accept(listening, (struct sockaddr*)&pointRencontreClient, &longueurAdresse);

	if (clientSocket == -1)
	{
		perror("echec de l'acceptation");
		close(listening);
		exit(-1);

	}
	printf("Vous etes en connectez avec le client. Envoyezlui des choses ..send et recv !!! \n");

	//boucle while : accepter et echo le message au client
	while (true)
	{
		char msgRcv[4096];
		memset(msgRcv, 0, 4096);

		//Attendre que le client envoie des données
		int bytesReceived = recv(clientSocket, msgRcv, 4096, 0);

		if (bytesReceived == -1)
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

			char error[] = "{\"Erreur\":\"ConnexionUser\"}";
			string json = connexionUser(msgRcv);
			
			cout << "connexion reçu";

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
			char error[] = "{\"Erreur\":\"ConnexionAdmin\"}";

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
		if (strstr(msgRcv, "HistoriqueCJoueur") != NULL) {

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
			char error[] = "{\"Erreur\":\"HistoriqueJoueur\"}";

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

			send(clientSocket, msg, size_msg, 0);

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

			send(clientSocket, msg, size_msg, 0);
			
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

	//Fermer la socket d'ecoute
	close(listening);
	//supprimer une socket
	close(clientSocket);
	
	return 0;
}

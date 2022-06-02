#include <iostream>
#include "rapidjson/document.h"
#include "jdbc/cppconn/prepared_statement.h"
#include "jdbc/cppconn/exception.h"
#include "jdbc/mysql_connection.h"
#include "jdbc/cppconn/driver.h"

using namespace std;
using namespace rapidjson;

const string server = "127.0.0.1:3306";
const string username = "root";
const string password = "root";
sql::Connection* con;
sql::PreparedStatement* pstmt;
sql::ResultSet* result;
sql::Driver* driver;

void creationUser(char msg[]) {

	Document mydoc;
	mydoc.Parse(msg);

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

	con->setSchema("sensorpong");

	pstmt = con->prepareStatement("INSERT INTO sensorpong.joueur (email,nom,prenom,mdp,Entraineur_idEntraineur) VALUES(?, ?, ?, ?, ?);");

	pstmt->setString(1, mydoc["CreerCompte"]["email"].GetString());
	pstmt->setString(2, mydoc["CreerCompte"]["nom"].GetString());
	pstmt->setString(3, mydoc["CreerCompte"]["prenom"].GetString());
	pstmt->setString(4, mydoc["CreerCompte"]["mdp"].GetString());
	pstmt->setInt(5, mydoc["CreerCompte"]["idEntraineur"].GetInt());

	result = pstmt->executeQuery();
}

string connexionUser(char msg[]) {

	
	Document mydoc;
	mydoc.Parse(msg);

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

	con->setSchema("sensorpong");

	string json = "{\"ConnexionUser\":";

	pstmt = con->prepareStatement("SELECT idJoueur, email, nom, prenom, mdp, Entraineur_idEntraineur FROM sensorpong.joueur WHERE email = ? &&  mdp = ?;");

	pstmt->setString(1, mydoc["ConnexionUser"]["email"].GetString());
	pstmt->setString(2, mydoc["ConnexionUser"]["mdp"].GetString());

	result = pstmt->executeQuery();
	
		while (result->next()) {

			int idJoueur = result->getInt(1);
			string email = result->getString(2).c_str();
			string nom = result->getString(3).c_str();
			string prenom = result->getString(4).c_str();
			string mdp = result->getString(5).c_str();
			int idEntraineur = result->getInt(6);

			json += "{\"idJoueur\": " + to_string(idJoueur) + ", \"email\": \"" + email + "\", \"nom\": \"" + nom + "\", \"prenom\": \"" + prenom + "\", \"mdp\": \"" + mdp + "\", \"idEntraineur\": " + to_string(idEntraineur) + "}";

		}
		json += "}";
		return json;
}

string connexionAdmin(char msg[]) {

	string json = "{\"ConnexionAdmin\":";
	Document mydoc;
	mydoc.Parse(msg);

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

	con->setSchema("sensorpong");

	pstmt = con->prepareStatement("SELECT idEntraineur, email, nom, prenom, mdp FROM sensorpong.entraineur WHERE email = ? &&  mdp = ?;");

	pstmt->setString(1, mydoc["ConnexionAdmin"]["email"].GetString());
	pstmt->setString(2, mydoc["ConnexionAdmin"]["mdp"].GetString());

	result = pstmt->executeQuery();

	while (result->next()) {

		int idEntraieur = result->getInt(1);
		string email = result->getString(2).c_str();
		string nom = result->getString(3).c_str();
		string prenom = result->getString(4).c_str();
		string mdp = result->getString(5).c_str();

		json += "{\"idEntraieur\": " + to_string(idEntraieur) + ", \"email\": \"" + email + "\", \"nom\": \"" + nom + "\", \"prenom\": \"" + prenom + "\", \"mdp\": \"" + mdp + "\"}";
		
	}
	json += "}";
	return json; 
}

string ListeJoueurs(char msg[]) {

	string* json = new string[4000];
	int i = 0;
	Document mydoc;
	mydoc.Parse(msg);

	string jsoncomplet = "{\"ListeJoueurs\":";

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

	con->setSchema("sensorpong");

	pstmt = con->prepareStatement("SELECT idJoueur, email, nom, prenom, mdp FROM sensorpong.joueur WHERE Entraineur_idEntraineur = ?;");

	pstmt->setInt(1, mydoc["ListeJoueurs"]["idEntraineur"].GetInt());

	result = pstmt->executeQuery();
	;
	while (result->next()) {

		int idJoueur = result->getInt(1);
		string email = result->getString(2).c_str();
		string nom = result->getString(3).c_str();
		string prenom = result->getString(4).c_str();
		string mdp = result->getString(5).c_str();

		json[i] = "{\"idJoueur\": " + to_string(idJoueur) + ", \"email\": \"" + email + "\", \"nom\": \"" + nom + "\", \"prenom\": \"" + prenom + "\", \"mdp\": \"" + mdp + "\"}";

		jsoncomplet += json[i];
		i++;
	}
	jsoncomplet += "}";
	return jsoncomplet;

}

string HistoriqueComplet(char msg[] ) {

	string *json = new string[4000];
	int i = 0;
	Document mydoc;
	mydoc.Parse(msg);

	string jsoncomplet = "{\"HistoriqueComplet\":";

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

	con->setSchema("sensorpong");

	pstmt = con->prepareStatement("SELECT nom, prenom, nbrBalle, frequence, vitesse, zone_envoie, zone_retour, taux_de_reussite, Date FROM sensorpong.joueur INNER JOIN sensorpong.partie WHERE Joueur_idJoueur = idJoueur AND partie.Entraineur_idEntraineur = ? ORDER BY Date DESC");

	pstmt->setInt(1, mydoc["HistoriqueComplet"]["idEntraineur"].GetInt());

	result = pstmt->executeQuery();
;
	while (result->next()) {
		string nom = result->getString(1).c_str();
		string prenom = result->getString(2).c_str();
		int nbrBalle = result->getInt(3);
		string frequence = result->getString(4).c_str();
		string vitesse = result->getString(5).c_str();
		int zone_envoie = result->getInt(6);
		int zone_retour = result->getInt(7);
		float taux_de_reussite = result->getDouble(8);
		string date = result->getString(9).c_str();


		json[i] = "{\"nom\": \"" + nom + "\", \"prenom\": \"" + prenom + "\", \"nbrBalle\": " + to_string(nbrBalle) + ", \"frequence\": \"" + frequence + "\", \"vitesse\": \"" + vitesse + "\", \"zone_envoie\": " + to_string(zone_envoie) + ", \"zone_retour\": " + to_string(zone_retour) + ", \"taux_de_reussite\": " + to_string(taux_de_reussite) + ", \"date\": \"" + date + "\"}";

			jsoncomplet += json[i];
			i++;

	}
	jsoncomplet += "}";
	return jsoncomplet;

}

string HistoriqueJoueurC(char msg[]) {

	string* json = new string[4000];
	int i = 0;

	string jsoncomplet = "{\"HistoriqueCJoueur\":";

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

	Document mydoc;
	mydoc.Parse(msg);

	con->setSchema("sensorpong");

	pstmt = con->prepareStatement("SELECT nom, prenom, nbrBalle, frequence, vitesse, zone_envoie, zone_retour, taux_de_reussite, Date FROM sensorpong.joueur INNER JOIN sensorpong.partie WHERE Joueur_idJoueur = ? && nom = ? && prenom = ? ORDER BY Date DESC;");

	pstmt->setInt(1, mydoc["HistoriqueCJoueur"]["idJoueur"].GetInt());
	pstmt->setString(2, mydoc["HistoriqueCJoueur"]["nom"].GetString());
	pstmt->setString(3, mydoc["HistoriqueCJoueur"]["prenom"].GetString());

	result = pstmt->executeQuery();
	;
	while (result->next()) {


		string nom = result->getString(1).c_str();
		string prenom = result->getString(2).c_str();
		int nbrBalle = result->getInt(3);
		string frequence = result->getString(4).c_str();
		string vitesse = result->getString(5).c_str();
		int zone_envoie = result->getInt(6);
		int zone_retour = result->getInt(7);
		float taux_de_reussite = result->getDouble(8);
		string date = result->getString(9).c_str();


		json[i] = "{\"nom\": \"" + nom + "\", \"prenom\": \"" + prenom + "\", \"nbrBalle\": " + to_string(nbrBalle) + ", \"frequence\": \"" + frequence + "\", \"vitesse\": \"" + vitesse + "\", \"zone_envoie\": " + to_string(zone_envoie) + ", \"zone_retour\": " + to_string(zone_retour) + ", \"taux_de_reussite\": " + to_string(taux_de_reussite) + ", \"date\": \"" + date + "\"}";

		jsoncomplet += json[i];
		i++;

	}
	jsoncomplet += "}";
	return jsoncomplet;

}

string HistoriqueJoueur(char msg[]) {

	string* json = new string[4000];
	int i = 0;
	Document mydoc;
	mydoc.Parse(msg);

	string jsoncomplet = "{\"HistoriqueJoueur\":";

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

	con->setSchema("sensorpong");

	pstmt = con->prepareStatement("SELECT nom, prenom, nbrBalle, frequence, vitesse, zone_envoie, zone_retour, taux_de_reussite, Date FROM sensorpong.joueur INNER JOIN sensorpong.partie WHERE Joueur_idJoueur = idJoueur AND idJoueur = ? AND zone_envoie = ? AND zone_retour = ? ORDER BY Date DESC LIMIT 10;");

	pstmt->setInt(1, mydoc["HistoriqueJoueur"]["idJoueur"].GetInt());
	pstmt->setInt(2, mydoc["HistoriqueJoueur"]["zone envoie"].GetInt());
	pstmt->setInt(3, mydoc["HistoriqueJoueur"]["zone retour"].GetInt());

	result = pstmt->executeQuery();
	;
	while (result->next()) {


		string nom = result->getString(1).c_str();
		string prenom = result->getString(2).c_str();
		int nbrBalle = result->getInt(3);
		string frequence = result->getString(4).c_str();
		string vitesse = result->getString(5).c_str();
		int zone_envoie = result->getInt(6);
		int zone_retour = result->getInt(7);
		float taux_de_reussite = result->getDouble(8);
		string date = result->getString(9).c_str();


		json[i] = "{\"nom\": \"" + nom + "\", \"prenom\": \"" + prenom + "\", \"nbrBalle\": " + to_string(nbrBalle) + ", \"frequence\": \"" + frequence + "\", \"vitesse\": \"" + vitesse + "\", \"zone_envoie\": " + to_string(zone_envoie) + ", \"zone_retour\": " + to_string(zone_retour) + ", \"taux_de_reussite\": " + to_string(taux_de_reussite) + ", \"date\": \"" + date + "\"}";

		jsoncomplet += json[i];
		i++;

	}
	jsoncomplet += "}";
	return jsoncomplet;

}

void UpdateUser(char msg[]) {

	Document mydoc;
	mydoc.Parse(msg);

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

	con->setSchema("sensorpong");

	pstmt = con->prepareStatement("UPDATE sensorpong.joueur SET email = ?, nom = ?, prenom = ?, mdp = ? WHERE idJoueur = ?;");

	pstmt->setString(1, mydoc["UpdateUser"]["email"].GetString());
	pstmt->setString(2, mydoc["UpdateUser"]["nom"].GetString());
	pstmt->setString(3, mydoc["UpdateUser"]["prenom"].GetString());
	pstmt->setString(4, mydoc["UpdateUser"]["mdp"].GetString());
	pstmt->setInt(5, mydoc["UpdateUser"]["idJoueur"].GetInt());

	result = pstmt->executeQuery();
}

void DeleteUser(char msg[]) {

	Document mydoc;
	mydoc.Parse(msg);

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

	con->setSchema("sensorpong");

	pstmt = con->prepareStatement("DELETE sensorpong.joueur, sensorpong.partie FROM sensorpong.joueur INNER JOIN sensorpong.partie ON partie.Joueur_idJoueur = idJoueur WHERE idJoueur = ?;");

	pstmt->setInt(1, mydoc["DeleteUser"]["idJoueur"].GetInt());

	result = pstmt->executeQuery();

}

string GameStart(char msg[]) {

	string json = "{\"GameStart\":";
	Document mydoc;
	mydoc.Parse(msg);

	int nbrBalle = mydoc["GameStart"]["nbrBalle"].GetInt();
	int zone_envoie = mydoc["GameStart"]["zone envoie"].GetInt();
	int zone_retour = mydoc["GameStart"]["zone retour"].GetInt();

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

	con->setSchema("sensorpong");

	pstmt = con->prepareStatement("SELECT frequence,vitesse,MAX(Date) FROM sensorpong.joueur INNER JOIN sensorpong.partie WHERE Joueur_idJoueur = idJoueur AND idJoueur= ?;");

	pstmt->setInt(1, mydoc["GameStart"]["idJoueur"].GetInt());

	result = pstmt->executeQuery();

	while (result->next()) {

		string frequence = result->getString(1).c_str();
		string vitesse = result->getString(2).c_str();


		json += "{\"nbrBalle\": " + to_string(nbrBalle) + ", \"zone envoie\": " + to_string(zone_envoie) + ", \"zone retour\": " + to_string(zone_retour) + ", \"frequence\": \"" + frequence + "\", \"vitesse\": \"" + vitesse + "\"}";

	}
	json += "}";
	return json;
}

void enregistrerPartie(char msg[]) {
	Document mydoc;
	mydoc.Parse(msg);

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

	con->setSchema("sensorpong");

	pstmt = con->prepareStatement("INSERT INTO sensorpong.partie(nbrBalle,frequence,vitesse,zone_envoie,zone_retour,taux_de_reussite,Date,Joueur_idJoueur,Entraineur_idEntraineur) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?)");

	pstmt->setInt(1, mydoc["EnregistrerPartie"]["nbrBalle"].GetInt());
	pstmt->setString(2, mydoc["EnregistrerPartie"]["frequence"].GetString());
	pstmt->setString(3, mydoc["EnregistrerPartie"]["vitesse"].GetString());
	pstmt->setInt(4, mydoc["EnregistrerPartie"]["zone envoie"].GetInt());
	pstmt->setInt(5, mydoc["EnregistrerPartie"]["zone retour"].GetInt());
	pstmt->setDouble(6, mydoc["EnregistrerPartie"]["taux de reussite"].GetDouble());
	pstmt->setString(7, mydoc["EnregistrerPartie"]["Date"].GetString());
	pstmt->setInt(8, mydoc["EnregistrerPartie"]["idJoueur"].GetInt());
	pstmt->setInt(9, mydoc["EnregistrerPartie"]["idEntraineur"].GetInt());

	result = pstmt->executeQuery();
}
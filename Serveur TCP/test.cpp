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

string test(char msg[]) {

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

	Document mydoc;
	mydoc.Parse(msg);

	pstmt = con->prepareStatement("SELECT idJoueur, email, nom, prenom, mdp FROM sensorpong.joueur WHERE email = ? &&  mdp = ?;");

	pstmt->setString(1, mydoc["ConnexionUser"]["email"].GetString());
	pstmt->setString(2, mydoc["ConnexionUser"]["mdp"].GetString());

	result = pstmt->executeQuery();

	while (result->next()) {

		int idJoueur = result->getInt(1);
		string email = result->getString(2).c_str();
		string nom = result->getString(3).c_str();
		string prenom = result->getString(4).c_str();
		string mdp = result->getString(5).c_str();

		string msg2 = "{\"idJoueur\": " + to_string(idJoueur) + ", \"email\": \"" + email + "\", \"nom\": \"" + nom + "\", \"prenom\": \"" + prenom + "\", \"mdp\": \"" + mdp + "\"}";

				//cout << msg2 << endl;
				return msg2;
	}
}


string test2(char msg[]) {

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

	Document mydoc;
	mydoc.Parse(msg);

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

		string msg2 = "{\"idEntraieur\": " + to_string(idEntraieur) + ", \"email\": \"" + email + "\", \"nom\": \"" + nom + "\", \"prenom\": \"" + prenom + "\", \"mdp\": \"" + mdp + "\"}";

		//cout << msg2 << endl;
		return msg2;
	}
}
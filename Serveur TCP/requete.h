#ifndef REQUETE_H_INCLUDED
#define REQUETE_H_INCLUDED

using namespace std;

void creationUser(char msg[]);

string connexionUser(char msg[]);

string connexionAdmin(char msg[]);

string ListeJoueurs(char msg[]);

string HistoriqueComplet(char msg[]);

string HistoriqueJoueurC(char msg[]);

string HistoriqueJoueur(char msg[]);

void UpdateUser(char msg[]);

void DeleteUser(char msg[]);

string GameStart(char msg[]);

void enregistrerPartie(char msg[]);

/*

string GameParam(char msg[]);

string AppParam(char msg[]);

*/


#endif // REQUETE_H_INCLUDED

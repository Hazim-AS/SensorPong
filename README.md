# SensorPong

- Taux Partie = (Coup Reussi/nbrBalle)*100

Taches :

	Hazim : 
	- Créer un serveur sur le rasberry permettant de communiquer avec l'appli Android
	- Créer un client MySQL permettant de communiquer avec la BDD
	- Concevoir une BDD avec les differentes tables et requetes ainsi que les statistiques pour chacun des joueurs
	- Créer une liaison serie entre la Rasberry et l'arduino qui permettera a La Rasberry :
		L'envoi en temps réel de la vitesse, fréquence et oscillation 
		De recuperer les valeurs des differents capteurs et les lires

		Table BDD :
		- Entraineur
		- Joueur
		- Partie
		- Joueur_has_Partie

		Requetes BDD :
		- création d'un Joueur : INSERT INTO sensorpong.joueur (email,nom,prenom,mdp,Entraineur_idEntraineur) VALUES ('francis@gmail.com','dupont','francis','lo87',1); 
		- connexion au compte : SELECT * FROM sensorpong.joueur INNER JOIN sensorpong.entraineur WHERE joueur.email='kylian.alger-leonard@lycee-jeanrostand.fr' && joueur.mdp='1478';
		- Enregistrer la partie d'un joueur apres la fin de la partie : INSERT INTO
		- Historique complet des Joueurs: SELECT
		- Historique complet d'un Joueur : SELECT
		- Historique des 10 dernieres partie d'un Joueur en fonction de la configuration : SELECT
		- Effacer un compte et tout ces réglages : DELETE


	Kylian :


	Kais :


Liens : 

	Physique :
	
		OFD :
		- https://www.dsprelated.com/showarticle/1046.php
	
		Capteur Infrarouge :
		- https://www.securitasdirect.fr/mag-securite/systeme-d-alarme/composants/alarme-coeur-du-systeme/quoi-sert-un-detecteur-infrarouge
		- https://www.verisure.fr/guide-securite/systeme-d-alarme/composants-alarme/detecteur-de-mouvement/fonctionnement-capteur-infrarouge
	
		Capteur FSR :
		- https://www.gotronic.fr/pj2-24574-1381.pdf
		- https://wiki.mchobby.be/index.php?title=Senseur_FSR
		- https://www.mataucarre.fr/index.php/2017/05/03/capteur-de-force-fsr02-senseur-fsr-arduino/

	CSV :
	- https://www.youtube.com/watch?v=i-TqNzUryn8&ab_channel=BrianFraser
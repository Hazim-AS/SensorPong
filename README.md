# SensorPong

- Taux Partie = (Coup Reussi/Coup Total)*100

Taches :

	Hazim : 
	- Créer un serveur sur le rasberry permettant de communiquer avec l'appli Android
	- Créer un client MySQL permettant de communiquer avec la BDD
	- Concevoir une BDD avec les differentes tables et requetes ainsi que les statistiques pour chacun des joueurs
	- Créer une liaison serie entre la Rasberry et l'arduino qui permettera a La Rasberry :
		L'envoi en temps réel de la vitesse, fréquence et oscillation 
		De recuperer les valeurs des differents capteurs et les lires

		Table BDD :
		- Compte
		- Historique
		- Reglage

		Requetes BDD :
		- création de compte : INSERT INTO sensorpong.compte (`nom`, `mdp`, `statut`) VALUES ('Hazim', '1234', 'Admin');
		- connexion au compte : SELECT * FROM sensorpong.compte WHERE nom = 'Hazim' AND mdp = '1234'
		- Enregistrer dans l'historique la partie d'un joueur : 
		- Enregistrer les reglages d'une partie d'un joueur : 
		- Modifier les reglages de la partie d'un Joueur : UPDATE sensorpong.reglage INNER JOIN sensorpong.compte ON Compte_idcompte = compte.idcompte SET balle = '3', Fréquence = '7', Vitesse = '8', zone_envoie = '1-2', zone_retour = '5-6' WHERE compte.nom = 'Antoine'
		- Enregistrer la partie d'un joueur apres la fin de la partie : 
		- Historique complet des Joueurs: SELECT * FROM sensorpong.historique;
		- Historique complet d'un Joueur : SELECT * FROM sensorpong.compte INNER JOIN sensorpong.historique on compte.idcompte = historique.Compte_idcompte where nom = 'Antoine';
		- Historique des 10 dernieres partie d'un Joueur :
		- Historique des 10 dernieres partie d'un Joueur en fonction de la configuration :

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
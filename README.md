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
		- création de compte : INSERT INTO compte (`nom`, `mdp`, `statut`) VALUES ('Hazim', '123', 'Joueur');
		- connexion au compte : SELECT nom,mdp FROM compte WHERE nom = 'Hazim' AND mdp = '1234'
		- Reglage de la partie : 
		- Historique complet des Joueurs:
		- Historique complet d'un Joueur :
		- Historique des 10 dernieres partie d'un Joueur :
		- Historique des 10 dernieres partie d'un Joueur en fonction la vitesse:
		- Historique :
		- Historique :

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
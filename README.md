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

- création d'un Joueur : 
INSERT INTO sensorpong.joueur (email,nom,prenom,mdp,Entraineur_idEntraineur) 
VALUES ('francis@gmail.com','dupont','francis','lo87',1);

- connexion au compte de l'entraineur :
SELECT * 
FROM sensorpong.entraineur 
WHERE email='ahmedsalih.hazim@gmail.com' && mdp='1234';

- connexion au compte du joueur: 
SELECT * 
FROM sensorpong.joueur 
WHERE email='kylian.alger-leonard@lycee-jeanrostand.fr' AND mdp='1478';

- Recuperer vitesse et fréquence des balles de la derniere partie : 
SELECT frequence,vitesse,MAX(Date) 
FROM sensorpong.joueur INNER JOIN sensorpong.partie 
WHERE Joueur_idJoueur = idJoueur AND nom='Beddar' AND prenom='Kais';

- Enregistrer la partie d'un joueur apres la fin de la partie : 
INSERT INTO sensorpong.partie(nbrBalle,frequence,vitesse,zone_envoie,zone_retour,taux_de_reussite,Date,Joueur_idJoueur,Entraineur_idEntraineur)
VALUES(10,5,2,'1-2','',50,'2022-03-16 17:30:54',1,1) 

- Historique complet des Joueurs: 
SELECT nom, prenom, nbrBalle, frequence, vitesse, zone_envoie, zone_retour, taux_de_reussite, Date 
FROM sensorpong.joueur INNER JOIN sensorpong.partie 
WHERE Joueur_idJoueur = idJoueur ORDER BY Date DESC;

- Historique complet d'un Joueur : 
SELECT nom, prenom, nbrBalle, frequence, vitesse, zone_envoie, zone_retour, taux_de_reussite, Date 
FROM sensorpong.joueur INNER JOIN sensorpong.partie
WHERE Joueur_idJoueur = idJoueur && nom='Alger' && prenom='Kylian' ORDER BY Date DESC;

- Historique des 10 dernieres partie d'un Joueur en fonction de la configuration : SELECT nom, prenom, nbrBalle, frequence, vitesse, zone_envoie, zone_retour, taux_de_reussite, Date 
FROM sensorpong.joueur 
INNER JOIN sensorpong.partie WHERE Joueur_idJoueur = idJoueur AND nom='Alger' AND prenom='Kylian' AND nbrBalle >= 0 AND nbrBalle <= 50 AND frequence>=4 AND frequence<=4 AND vitesse>=0 AND vitesse<=10 AND zone_envoie LIKE '%3%' AND zone_retour LIKE '%7%' AND taux_de_reussite >= 0 AND taux_de_reussite <= 100 
ORDER BY Date DESC LIMIT 10;

- Effacer un compte et tout ces réglages : 
DELETE * 



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
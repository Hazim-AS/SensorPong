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
VALUES (@mail,@nom,@prenom,@mdp,@idEntraineur);

- connexion au compte de l'entraîneur :
SELECT * 
FROM sensorpong.entraineur 
WHERE email=@mail && mdp=@mdp;

- connexion au compte du joueur: 
SELECT * 
FROM sensorpong.joueur 
WHERE email=@mail && mdp=@mdp

- Récupérer vitesse et fréquence des balles de la dernière partie : 
SELECT frequence,vitesse,MAX(Date) 
FROM sensorpong.joueur INNER JOIN sensorpong.partie 
WHERE Joueur_idJoueur = idJoueur AND idJoueur=@idJoueur;

- Enregistrer la partie d'un joueur apres la fin de la partie : 
INSERT INTO sensorpong.partie(nbrBalle,frequence,vitesse,zone_envoie,zone_retour,taux_de_reussite,Date,Joueur_idJoueur,Entraineur_idEntraineur)
VALUES(@nbrBalle,@frequence,@vitesse,@zone_envoie,@zone_retour,@taux_de_reussite,@Date,@idJoueur,@idEntraineur)

- Historique complet des Joueurs: 
SELECT nom, prenom, nbrBalle, frequence, vitesse, zone_envoie, zone_retour, taux_de_reussite, Date 
FROM sensorpong.joueur INNER JOIN sensorpong.partie 
WHERE Joueur_idJoueur = idJoueur ORDER BY Date DESC;

- Historique complet d'un Joueur : 
SELECT nom, prenom, nbrBalle, frequence, vitesse, zone_envoie, zone_retour, taux_de_reussite, Date 
FROM sensorpong.joueur INNER JOIN sensorpong.partie
WHERE Joueur_idJoueur = idJoueur && nom='Alger' && prenom='Kylian' ORDER BY Date DESC;

- Historique des 10 dernières partie d'un Joueur en fonction de la configuration : SELECT nom, prenom, nbrBalle, frequence, vitesse, zone_envoie, zone_retour, taux_de_reussite, Date 
FROM sensorpong.joueur 
INNER JOIN sensorpong.partie WHERE Joueur_idJoueur = idJoueur AND idJoueur=@idJoueur AND nbrBalle >= @nbrBalleMin AND nbrBalle <= @nbrBalleMax AND frequence>= @freqMin AND frequence<= @freqMax AND vitesse>=@vitMin AND vitesse<=@vitMax AND zone_envoie LIKE  CONCAT('%',@zoneEnvoie, '%') AND zone_retour LIKE CONCAT('%',@zoneRetour, '%') AND taux_de_reussite >= @tauxMin AND taux_de_reussite <= @tauxMax 
ORDER BY Date DESC LIMIT 10;

- Effacer un joueur : 
DELETE FROM sensorpong.joueur WHERE idJoueur=@idJoueur;

-Effacer les parties du joueurs :
DELETE FROM sensorpong.partie WHERE Joueur_idJoueur=@idJoueur;





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
-- MySQL dump 10.13  Distrib 8.0.28, for Win64 (x86_64)
--
-- Host: localhost    Database: sensorpong
-- ------------------------------------------------------
-- Server version	5.7.31

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `entraineur`
--

DROP TABLE IF EXISTS `entraineur`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `entraineur` (
  `idEntraineur` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(45) DEFAULT NULL,
  `nom` varchar(45) DEFAULT NULL,
  `prenom` varchar(45) DEFAULT NULL,
  `mdp` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idEntraineur`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `entraineur`
--

LOCK TABLES `entraineur` WRITE;
/*!40000 ALTER TABLE `entraineur` DISABLE KEYS */;
INSERT INTO `entraineur` VALUES (1,'ahmedsalih.hazim@gmail.com','Ahmed Salih','Hazim','1234');
/*!40000 ALTER TABLE `entraineur` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `joueur`
--

DROP TABLE IF EXISTS `joueur`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `joueur` (
  `idJoueur` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(45) DEFAULT NULL,
  `nom` varchar(45) DEFAULT NULL,
  `prenom` varchar(45) DEFAULT NULL,
  `mdp` varchar(45) DEFAULT NULL,
  `Entraineur_idEntraineur` int(11) NOT NULL,
  PRIMARY KEY (`idJoueur`,`Entraineur_idEntraineur`),
  KEY `fk_Joueur_Entraineur1_idx` (`Entraineur_idEntraineur`),
  CONSTRAINT `fk_Joueur_Entraineur1` FOREIGN KEY (`Entraineur_idEntraineur`) REFERENCES `entraineur` (`idEntraineur`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `joueur`
--

LOCK TABLES `joueur` WRITE;
/*!40000 ALTER TABLE `joueur` DISABLE KEYS */;
INSERT INTO `joueur` VALUES (1,'kylian.alger-leonard@lycee-jeanrostand.fr ','Alger','Kylian','1478',1),(2,'kais@gmail.com','Beddar','Kais','2589',1),(3,'dupond@gmail.com','Dupond','Francis','2589',1);
/*!40000 ALTER TABLE `joueur` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `partie`
--

DROP TABLE IF EXISTS `partie`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `partie` (
  `idPartie` int(11) NOT NULL AUTO_INCREMENT,
  `nbrBalle` int(11) DEFAULT NULL,
  `frequence` int(11) DEFAULT NULL,
  `vitesse` int(11) DEFAULT NULL,
  `zone_envoie` varchar(45) DEFAULT NULL,
  `zone_retour` varchar(45) DEFAULT NULL,
  `taux_de_reussite` float DEFAULT NULL,
  `Date` datetime DEFAULT NULL,
  `Joueur_idJoueur` int(11) NOT NULL,
  `Entraineur_idEntraineur` int(11) NOT NULL,
  PRIMARY KEY (`idPartie`,`Joueur_idJoueur`,`Entraineur_idEntraineur`),
  KEY `fk_Partie_Joueur_idx` (`Joueur_idJoueur`),
  KEY `fk_Partie_Entraineur1_idx` (`Entraineur_idEntraineur`),
  CONSTRAINT `fk_Partie_Entraineur1` FOREIGN KEY (`Entraineur_idEntraineur`) REFERENCES `entraineur` (`idEntraineur`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_Partie_Joueur` FOREIGN KEY (`Joueur_idJoueur`) REFERENCES `joueur` (`idJoueur`) ON DELETE NO ACTION ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=23 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `partie`
--

LOCK TABLES `partie` WRITE;
/*!40000 ALTER TABLE `partie` DISABLE KEYS */;
INSERT INTO `partie` VALUES (1,10,6,7,'1-2','5-6',60,'2022-03-15 10:04:06',1,1),(2,6,8,10,'3-4','7-8',66.67,'2022-03-15 11:45:47',2,1),(3,15,7,8,'3','8',100,'2022-03-15 16:00:00',2,1),(4,10,2,4,'4','7',50,'2022-03-15 17:52:45',1,1),(5,20,8,9,'2-3','6-7',65,'2022-03-16 10:15:02',1,1),(6,25,3,4,'1-2-3','5-6',70,'2022-03-16 10:20:50',2,1),(7,12,4,6,'2-3-4','5-6-7',50,'2022-03-16 10:30:45',1,1),(8,17,8,7,'3','8',100,'2022-03-16 11:00:15',2,1),(9,18,7,4,'1-3','6-7-8',44.44,'2022-03-16 11:17:10',1,1),(10,15,5,6,'2-4','6-8',46.67,'2022-03-16 11:45:36',2,1),(11,22,1,7,'4','8',50,'2022-03-16 11:59:21',1,1),(12,14,2,7,'2','6',21.14,'2022-03-16 12:14:58',2,1),(13,10,9,2,'1','5',70,'2022-03-16 12:19:14',1,1),(14,15,10,1,'1-4','8',73.33,'2022-03-16 12:30:14',2,1),(15,5,3,6,'2-4','6',100,'2022-03-16 14:58:15',1,1),(16,10,10,8,'1-2','5-6',40,'2022-03-16 15:05:12',2,1),(17,15,10,10,'2-3','5-7',73.33,'2022-03-16 15:20:52',1,1),(18,14,4,10,'1-3','6-7',64.28,'2022-03-16 15:30:24',1,1),(19,25,5,7,'2-4','5-8',72,'2022-03-16 15:45:42',1,1),(20,20,8,8,'3-4','7-8',65,'2022-03-16 16:00:02',1,1),(21,14,5,7,'2-3','6-8',50,'2022-03-16 17:05:27',3,1),(22,10,4,5,'1-4','5-6',80,'2022-03-16 17:08:38',3,1);
/*!40000 ALTER TABLE `partie` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-03-18 10:18:37

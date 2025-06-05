/* Script généré automatiquement par Katyusha MCD v0.4.6 pour mysql */


/* Table : Evenements */   

CREATE TABLE Evenements (
    id INTEGER PRIMARY KEY AUTO_INCREMENT, 
  date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    type VARCHAR(255) NOT NULL, 
    id_Machine INTEGER NOT NULL
) ;


/* Table : Image */

CREATE TABLE Image (
    id INTEGER PRIMARY KEY AUTO_INCREMENT, 
     date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    nom VARCHAR(255) NOT NULL, 
    type VARCHAR(255) NOT NULL, 
    id_Evenements INTEGER NOT NULL
) ;


/* Table : Contexte */

CREATE TABLE Contexte (
    id INTEGER PRIMARY KEY AUTO_INCREMENT, 
   date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    tempAmb FLOAT NOT NULL, 
    humidite INTEGER NOT NULL, 
    tension1 FLOAT, 
    tension2 FLOAT, 
    tension3 FLOAT, 
    intensite1 FLOAT, 
    intensite2 FLOAT, 
    intensite3 FLOAT, 
    cosPhi1 FLOAT, 
    cosPh2 FLOAT, 
    cosPhi3 FLOAT,
    id_Machine INTEGER NOT NULL
) ;


/* Table : Vibrations */

CREATE TABLE Vibrations (
    id INTEGER PRIMARY KEY AUTO_INCREMENT, 
     date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    axeX VARCHAR(255) NOT NULL, 
    axeY VARCHAR(255) NOT NULL, 
    axeZ VARCHAR(255) NOT NULL, 
      id_Machine INTEGER NOT NULL
) ;


/* Table : SeuilTemp */

CREATE TABLE SeuilTemp (
    id INTEGER PRIMARY KEY AUTO_INCREMENT, 
    tempMax FLOAT NOT NULL, 
    tempMoy FLOAT NOT NULL,
    id_Machine INTEGER NOT NULL 
) ;


/* Table : SeuilVibra */

CREATE TABLE SeuilVibra (
    id INTEGER PRIMARY KEY AUTO_INCREMENT, 
    vibraMaxX FLOAT NOT NULL, 
    vibraMaxY FLOAT NOT NULL, 
    vibraMaxZ FLOAT NOT NULL,
    id_Machine INTEGER NOT NULL
) ;


/* Table : Machine */

CREATE TABLE Machine (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    type VARCHAR(255) NOT NULL, 
    apprentissageTermineTemp BOOLEAN NOT NULL, 
    apprentissageTermineVibra BOOLEAN NOT NULL
) ;


/* Table : Temperature */

CREATE TABLE Temperature (
    id INTEGER PRIMARY KEY AUTO_INCREMENT,
    date DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP, 
     tempMoy FLOAT NOT NULL, 
    tempMax FLOAT NOT NULL, 
    id_Machine INTEGER NOT NULL
) ;


/* Table : Authentification */

CREATE TABLE Authentification (
    id_login INTEGER PRIMARY KEY AUTO_INCREMENT, 
    mdp VARCHAR(255) NOT NULL DEFAULT 'not null'
) ;





ALTER TABLE Vibrations ADD CONSTRAINT FK_Machine_id_Machine_Vibrations FOREIGN KEY (id_Machine) REFERENCES Machine(id) ;

ALTER TABLE Temperature ADD CONSTRAINT FK_Machine_id_Machine_Temperature FOREIGN KEY (id_Machine) REFERENCES Machine(id) ;

ALTER TABLE SeuilTemp ADD CONSTRAINT FK_Machine_id_Machine_SeuilTemp FOREIGN KEY (id_Machine) REFERENCES Machine(id) ;

ALTER TABLE SeuilVibra ADD CONSTRAINT FK_Machine_id_Machine_SeuilVibra FOREIGN KEY (id_Machine) REFERENCES Machine(id) ;

ALTER TABLE Image ADD CONSTRAINT FK_Evenements_id_Evenements_Image FOREIGN KEY (id_Evenements) REFERENCES Evenements(id) ;

ALTER TABLE Evenements ADD CONSTRAINT FK_Machine_id_Machine_Evenements FOREIGN KEY (id_Machine) REFERENCES Machine(id) ;

ALTER TABLE Contexte ADD CONSTRAINT FK_Machine_id_Machine_Contexte FOREIGN KEY (id_Machine) REFERENCES Machine(id) ;



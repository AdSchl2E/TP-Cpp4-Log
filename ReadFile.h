/*************************************************************************
                           ReadFile  -  Lecture d'un fichier log et récupération des infos
                             -------------------
    début                : 15/01/2024
    copyright            : (C) 2024 par MANTZARIDES Guillaume et FELZINES Joris
    e-mail               : guillaume.mantzarides@insa-lyon.fr, joris.felzines@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <ReadFile> (fichier ReadFile.h) ----------------
#if ! defined (ReadFile_H)
#define ReadFile_H

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef struct
{
    string ip = "0.0.0.0";
    string userNameLog;
    string nameUser;
    string date;
    string hour;
    string gmtModif;
    string request;
    string urlTarget;
    string extension = "";
    string protocolV;
    string status;
    string dataSize;
    string domain = "";
    string urlReferer;
    string idCli;

} LogData;
//------------------------------------------------------------------------
// Rôle de la classe <ReadFile>
// La classe ReadFile permet de lire un fichier de log apache et de récupérer les informations
// de chaque ligne dans une structure LogData.
//------------------------------------------------------------------------

class ReadFile
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    string GetIp () const;
    // Mode d'emploi :
    // Renvoie l'IP du client émetteur de la requête

    string GetUserNameLog () const;
    // Mode d'emploi :
    // Renvoie le nom d'utilisateur du visiteur

    string GetNameUser () const;
    // Mode d'emploi :
    // Renvoie l'alias du visiteur

    string GetDate () const;
    // Mode d'emploi :
    // Renvoie la date sous la forme DD/MMM/YYYY

    string GetHour () const;
    // Mode d'emploi :
    // Renvoie l'heure sous la forme HH:MM:SS

    string GetGmtModif () const;
    // Mode d'emploi :
    // Renvoie la différence en rapport avec GMT (+XXXX)

    string GetRequest () const;
    // Mode d'emploi :
    // Renvoie le type de requête exécutéé (GET, POST...)

    string GetUrlTarget () const;
    // Mode d'emploi :
    // Renvoie l'URL du document demandé

    string GetExtension () const;
    // Mode d'emploi :
    // Renvoie l'extension du document demandé

    string GetProtocolV () const;
    // Mode d'emploi :
    // Renvoie la version du protocole 

    string GetStatus () const;
    // Mode d'emploi :
    // Renvoie le code retour de la réponse du serveur

    string GetDataSize () const;
    // Mode d'emploi :
    // Renvoie la taille en octets de la réponse

    string GetDomain () const;
    // Mode d'emploi :
    // Renvoie le domaine du referer

    string GetUrlReferer () const;
    // Mode d'emploi :
    // Renvoie l'URL actuelle du referer, donc là où le client se trouve lorsqu'il effectue la requête

    string GetIdCli () const;
    // Mode d'emploi :
    // Renvoie l'identification du navigateur du client

    int GetFileError () const;
    // Mode d'emploi :
    // Renvoie l'attribut fileError pour connaître l'état d'ouverture

    bool GetNextLogLine ();
    // Mode d'emploi :
    // Lis la prochaine ligne d'un fichier de log apache et met à jour la struct data

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

    ReadFile (string fileName, string urlLocale);
    // Mode d'emploi :
    // Crée un objet ReadFile qui permet de lire un fichier de log apache et de récupérer les informations
    // Contrat :
    // Le fichier doit être un fichier de log apache

    virtual ~ReadFile ( );
    // Mode d'emploi :
    // Détruit l'objet ReadFile
    // Contrat :
    // L'objet ReadFile doit être initialisé

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    LogData data;
    string fileName;
    string localURL;
    ifstream rFlux;
    int fileError = 0;
};

//-------------------------------- Autres définitions dépendantes de <ReadFile>

#endif // ReadFile_H


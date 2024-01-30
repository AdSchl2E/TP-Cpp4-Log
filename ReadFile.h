/*************************************************************************
                           ReadFile  -  classe de lecture fichier log
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <ReadFile> (fichier ReadFile.h) ----------------
#if ! defined ( ReadFile_H )
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
//
//
//------------------------------------------------------------------------

class ReadFile
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
// type Méthode ( liste des paramètres );
// Mode d'emploi :
//
// Contrat :
//
    string getIp () const;
    // Mode d'emploi :
    // renvoie l'IP du client émetteur de la requête

    string getUserNameLog () const;
    // Mode d'emploi :
    // renvoie le nom d'utilisateur du visiteur

    string getNameUser () const;
    // Mode d'emploi :
    // renvoie l'alias du visiteur

    string getDate () const;
    // Mode d'emploi :
    // renvoie la date sous la forme DD/MMM/YYYY

    string getHour () const;
    // Mode d'emploi :
    // renvoie l'heure sous la forme HH:MM:SS

    string getGmtModif () const;
    // Mode d'emploi :
    // renvoie la différence en rapport avec GMT (+XXXX)

    string getRequest () const;
    // Mode d'emploi :
    // renvoie le type de requête exécutéé (GET, POST...)

    string getUrlTarget () const;
    // Mode d'emploi :
    // renvoie l'URL du document demandé

    string getExtension () const;
    // Mode d'emploi :
    // renvoie l'extension du document demandé

    string getProtocolV () const;
    // Mode d'emploi :
    // renvoie la version du protocole 

    string getStatus () const;
    // Mode d'emploi :
    // renvoie le code retour de la réponse du serveur

    string getDataSize () const;
    // Mode d'emploi :
    // renvoie la taille en octets de la réponse

    string getDomain () const;
    // Mode d'emploi :
    // renvoie le domaine du referer

    string getUrlReferer () const;
    // Mode d'emploi :
    // renvoie l'URL actuelle du referer, donc là où le client se trouve lorsqu'il effectue la requête

    string getIdCli () const;
    // Mode d'emploi :
    // renvoie l'identification du navigateur du client

    bool getNextLogLine ();
    // Mode d'emploi :
    // Lis la prochaine ligne d'un fichier de log apache et met à jour la struct data

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
    ReadFile ( const ReadFile & unReadFile );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    ReadFile (string nomFic, string url = "intranet-if.insa-lyon.fr");
    // Mode d'emploi :
    // Par défaut urlLocale vaut "intranet-if.insa-lyon.fr"
    // Contrat :
    // 

    virtual ~ReadFile ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    LogData data;
    string nomFic;
    string urlLocale;
    ifstream rFlux;
};

//-------------------------------- Autres définitions dépendantes de <ReadFile>

#endif // ReadFile_H


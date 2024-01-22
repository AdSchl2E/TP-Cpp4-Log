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
    // renvoie la donnée concernée de la ligne de log actuelle

    string getUserNameLog () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

    string getNameUser () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

    string getDate () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

    string getHour () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

    string getGmtModif () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

    string getRequest () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

    string getUrlTarget () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

    string getExtension () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

    string getProtocolV () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

    string getStatus () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

    string getDataSize () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

    string getDomain () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

    string getUrlReferer () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

    string getIdCli () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle

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
    //
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


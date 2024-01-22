/*************************************************************************
                           ReadFile  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <ReadFile> (fichier ReadFile.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
// using namespace std;
// #include <iostream>

//------------------------------------------------------ Include personnel
#include "ReadFile.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
    string getIp () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.ip;
    }
    string getUserNameLog () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.userNameLog;
    }
    string getNameUser () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.nameUser;
    }
    string getDate () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.date;
    }
    string getHour () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.hour;
    }
    string getGmtModif () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.gmtModif;
    }
    string getRequest () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.request;
    }
    string getUrlTarget () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.urltarget;
    }
    string getProtocolV () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.protocolV;
    }
    string getStatus () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.status;
    }
    string getDataSize () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.dataSize;
    }
    string getDomain () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.domain;
    }
    string getUrlReferer () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.urlReferer;
    }
    string getIdCli () const;
    // Mode d'emploi :
    // renvoie la donnée concernée de la ligne de log actuelle
    {
        return data.idCli;
    }
    string getNextLogLine ();
    // Mode d'emploi :
    // Lis la prochaine ligne d'un fichier de log apache et met à jour la struct data
    {
        return data.nextLogLine;
    }
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
ReadFile & ReadFile::operator = ( const ReadFile & unReadFile )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
ReadFile::ReadFile ( const ReadFile & unReadFile )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <ReadFile>" << endl;
#endif
} //----- Fin de ReadFile (constructeur de copie)


ReadFile::ReadFile (string nomFic)
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au constructeur de <ReadFile>" << endl;
    #endif
    rFlux(nomFic.c_str());
    string ligne;
    while (getline(rFlux, ligne))
    {

    }
} //----- Fin de ReadFile


ReadFile::~ReadFile ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <ReadFile>" << endl;
#endif
} //----- Fin de ~ReadFile


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées


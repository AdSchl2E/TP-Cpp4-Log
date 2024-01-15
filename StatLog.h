/*************************************************************************
                           StatLog  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <StatLog> (fichier StatLog.h) ----------------
#if ! defined ( StatLog_H )
#define StatLog_H

//--------------------------------------------------- Interfaces utilisées
#include <map>
#include <list>
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <StatLog>
//
//
//------------------------------------------------------------------------

class StatLog
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

//-------------------------------------------- Constructeurs - destructeur
    StatLog ( const StatLog & unStatLog );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    StatLog ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~StatLog ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    list < string > listeNode;
    map < string, map < string, int > > graph;
};

//-------------------------------- Autres définitions dépendantes de <StatLog>

#endif // StatLog_H


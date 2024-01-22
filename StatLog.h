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
#include ReadFile.h
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

    void makeMapLine(bool extFilter, int startHeure = -1);

    void makeMap(bool extFilter, int startHeure = -1);

    void makeTop10();

    void makeDotFile();



//------------------------------------------------- Surcharge d'opérateurs
    StatLog & operator = ( const StatLog & unStatLog );
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

    StatLog (ReadFile file);
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
    bool compare ( pair < string, int > & a, pair < string, int > & b );
//----------------------------------------------------- Attributs protégés
    list < string > listeNode;
    map < string *, map < string *, int > > graph;
};

//-------------------------------- Autres définitions dépendantes de <StatLog>

#endif // StatLog_H

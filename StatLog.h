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

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <StatLog>
//
//
//------------------------------------------------------------------------

class StatLog : public Ancetre
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void makeMapLine(struct ...);

    void makeMap();

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

};

//-------------------------------- Autres définitions dépendantes de <StatLog>

#endif // StatLog_H


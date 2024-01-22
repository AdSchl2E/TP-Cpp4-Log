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
    // Mode d'emploi : On appelle la fonction pour ajouter une ligne au graph à partir des infos de
    // l'objet ReadFile avec les différents méthodes get de l'objet ReadFile file. On peut filtrer 
    // les extensions et les heures à partir des paramètres.
    //
    // Contrat : La méthode ne va pas récupérer les infos de la ligne suivante pour la suite
    // La méthode vérifie si la requête est valide (code 400 ou 500) et les filtres avant d'inserer

    void makeMap(bool extFilter, int startHeure = -1);
    // Mode d'emploi : On appelle la fonction pour créer le graphe complet à partir des infos du fichier log.
    // On peut filtrer les extensions et les heures à partir des paramètres.
    //
    // Contrat : la méthoder récupère la ligne suivante
    // Il faut que l'objet ReadFile file soit initialisé et passer dans le constructeur de StatLog

    void makeTop10();
    // Mode d'emploi :
    //
    // Contrat :
    //

    void makeDotFile();
    // Mode d'emploi :
    //
    // Contrat :
    //



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

//----------------------------------------------------- Attributs protégés
    list < string > listeNode;
    map < string, map < string, int > > graph;
};

//-------------------------------- Autres définitions dépendantes de <StatLog>

#endif // StatLog_H

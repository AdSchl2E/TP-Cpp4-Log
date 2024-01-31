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
#include <vector>
#include <algorithm>
#include <string>
#include "ReadFile.h"
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

    void makeMapLine(ReadFile & file, bool extFilter, int startHeure);
    // Mode d'emploi : On appelle la fonction pour ajouter une ligne au graph à partir des infos de
    // l'objet ReadFile avec les différents méthodes get de l'objet ReadFile file. On peut filtrer 
    // les extensions et les heures à partir des paramètres.
    //
    // Contrat : La méthode ne va pas récupérer les infos de la ligne suivante pour la suite
    // La méthode vérifie si la requête est valide (code 400 ou 500) et les filtres avant d'inserer

    void makeMap(ReadFile & file, bool extFilter, int startHeure);
    // Mode d'emploi : On appelle la fonction pour créer le graphe complet à partir des infos du fichier log.
    // On peut filtrer les extensions et les heures à partir des paramètres.
    //
    // Contrat : la méthoder récupère la ligne suivante
    // Il faut que l'objet ReadFile file soit initialisé et passer dans le constructeur de StatLog

    void makeTop10();
    // Mode d'emploi :
    // On appelle la fonction pour créer le top 10 des pages les plus visitées
    // Contrat :
    // Il faut que l'objet ReadFile file soit initialisé et passer dans le constructeur de StatLog

    void makeDotFile( string dotFile );
    // Mode d'emploi :
    // On appelle la fonction pour créer le fichier dot
    // Contrat :
    // Il faut que l'objet ReadFile file soit initialisé et passer dans le constructeur de StatLog

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

    StatLog (ReadFile & file, int startHeure, bool extFilter);
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
    static bool compare ( pair < string, int > & a, pair < string, int > & b );
    // Mode d'emploi :
    // Compare deux pairs de string et int
    // Contrat :
    //

    int convertHourInt(const string & heureString);
    // Mode d'emploi :
    // Convertit une heure au format hh:mm:ss en un entier au format hhmmss
    // Contrat :
    //

    string adresseSansPrefixe(const string* adresse);
    // Mode d'emploi :
    // Enlève le préfixe 0x de l'adresse
    // Contrat :
    //
//----------------------------------------------------- Attributs protégés
    list < string > listeNode;
    map < string *, map < string *, int > > graph;
};

//-------------------------------- Autres définitions dépendantes de <StatLog>

#endif // StatLog_H

/*************************************************************************
                           StatLog  -  Analyse de logs Apache
                             -------------------
    début                : 15/01/2024
    copyright            : (C) 2024 par SCHLEE Adam et CHAPARD Clément : B3309
    e-mail               : adam.schlee@insa-lyon.fr, clement.chapard@insa-lyon.fr
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
// La classe StatLog permet de créer un graphe à partir d'un fichier log
// et de le manipuler pour créer un fichier dot et un top 10 des pages les plus visitées
//------------------------------------------------------------------------

class StatLog
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    void makeMapLine(ReadFile & file, bool extFilter, int startHeure, string baseURL);
    // Mode d'emploi : On appelle la fonction pour ajouter une ligne au graph à partir des infos de
    // l'objet ReadFile avec les différents méthodes get de l'objet ReadFile file. On peut filtrer 
    // les extensions et les heures à partir des paramètres.
    //
    // Contrat : La méthode ne va pas récupérer les infos de la ligne suivante pour la suite
    // La méthode vérifie si la requête est valide (code 400 ou 500) et les filtres avant d'inserer

    void makeMap(ReadFile & file, bool extFilter, int startHeure, string baseURL);
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

//-------------------------------------------- Constructeurs - destructeur

    StatLog (ReadFile & file, int startHeure, bool extFilter, string baseURL);
    // Mode d'emploi :
    // On appelle le constructeur pour créer un objet StatLog à partir d'un objet ReadFile
    // On peut filtrer les extensions et les heures à partir des paramètres.
    // Contrat :
    // Il faut que l'objet ReadFile file soit initialisé et passer dans le constructeur de StatLog

    virtual ~StatLog ( );
    // Mode d'emploi :
    // On appelle le destructeur pour détruire l'objet StatLog
    // Contrat :
    // Il faut que l'objet StatLog soit initialisé

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    static bool compare ( pair < string, int > & a, pair < string, int > & b );
    // Mode d'emploi :
    // Compare deux pairs de string et int
    // Contrat :
    // Les deux pairs doivent être initialisés

    int convertHourInt(const string & heureString);
    // Mode d'emploi :
    // Convertit une heure au format hh:mm:ss en un entier au format hhmmss
    // Contrat :
    // L'heure doit être au format hh:mm:ss

    string removeBaseURL(string & URL, string & baseURL);
    
//----------------------------------------------------- Attributs protégés
    list < string > listeNode;
    map < string *, map < string *, int > > graph;
};

#endif // StatLog_H

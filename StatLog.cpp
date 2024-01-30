/*************************************************************************
                           StatLog  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <StatLog> (fichier StatLog.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <algorithm>


//------------------------------------------------------ Include personnel
#include "StatLog.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void StatLog::makeTop10 ( void )
// Algorithme :
//
{
    vector < pair < string, int > > hitsByCible;

    for ( map < string *, map < string *, int > >::iterator it = graph.begin ( ) ; it != graph.end ( ) ; ++it  )
    {
        for ( map < string *, int >::iterator it2 = it -> second.begin ( ) ; it2 != it -> second.end ( ) ; ++it2  )
        {
            hitsByCible.push_back( make_pair ( it2 -> first, it2 -> second ) );
        }
    }

    sort ( hitsByCible.begin(), hitsByCible.end(), compare );

    int i = 1;

    while ( i < hitsByCible.size() + 1 && i <= 10 )
    {
        cout << hitsByCible[hitsByCible.size() - i].first << " (" << hitsByCible[hitsByCible.size() - i].second << " hits)" << endl;
        i++;
    }
} //----- makeTop10

int convertHourInt(const string& heureString) {
    // Utilisation d'un flux de chaînes pour extraire les parties de l'heure
    istringstream ss(heureString);

    int heures, minutes, secondes;
    char delimiter;

    // Extraction des parties de l'heure
    if (ss >> heures >> delimiter >> minutes >> delimiter >> secondes) {
        // Calcul de l'entier HHMMSS
        int heureInt = heures * 10000 + minutes * 100 + secondes;

        return heureInt;
    } else {
        // Gestion d'une entrée invalide
        cerr << "Format d'heure invalide : " << heureString << endl;
        return -1; // Vous pouvez choisir une valeur de retour appropriée
    }
} //----- convertHourInt

void StatLog::makeMapLine(ReadFile file, bool extFilter, int startHeure)
// Algorithme :
//
{
    vector <string> badExtensions = {".js", ".css", ".jpg", ".gif", ".png", ".ico", ".ics", ".doc", ".docx", ".pdf", ".xml", ".zip", ".txt"};

    if (startHeure != -1){
        int intHeure = convertHourInt(file.getHour());
        if (intHeure > startHeure || (startHeure > 230000 && startHeure + 10000 - 240000 > intHeure)){
            return;
        }   
    }

    else if (extFilter && find(badExtensions.begin(), badExtensions.end(), getExtension()) != badExtensions.end()){
        return; 
    }

    else if (getStatus() == 400 || getStatus() == 500){
        return;
    }

    string source = getUrlReferer();
    string destination = getUrlTarget();
    listeNode.pop_back(source);
    listeNode.pop_back(destination);


    if (graph.find(source) == graph.end()){
        map <string, int> newMap;
        graph.insert(pair<string, map<string, int>>(source, newMap));
    }
    
    if (graph[source].find(destination) == graph[source].end()){
        graph[source].insert(pair<string, int>(destination, 1));
    }
    else{
        graph[source][destination]++;
    }
    
    return;
}

void StatLog::MakeMap(bool extFilter, int startHeure)
// Algorithme :
//
{

    while (file.getNextLogLine()){

        makeMapLine(extFilter, startHeure);

    }

    return;
}

void StatLog::makeDotFile()
// Algorithme :
//
{
    ofstream fout("test.dot");

    if( fout )    
    {
        fout << "digraph {" << endl;
        int i = 0;
        for( vector < string >::iterator it = listeNode.begin(); it != listeNode.end(); it++)
        {
            fout << *it << " [label=\"" << *it << "\"];" << endl;
        }

        for ( map < string, map < string, int > >::iterator it = graph.begin ( ) ; it != graph.end ( ) ; ++it  )
        {
            for ( map < string, int >::iterator it2 = it -> second.begin ( ) ; it2 != it -> second.end ( ) ; ++it2  )
            {
                fout << it -> first << " -> " << it2 -> first << " [label=\"" << it2 -> second << "\"];" << endl;
            }
        }
        fout << "}" << endl;
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}
//------------------------------------------------- Surcharge d'opérateurs
StatLog & StatLog::operator = ( const StatLog & unStatLog )
// Algorithme :
//
{

} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
StatLog::StatLog ( const StatLog & unStatLog )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <StatLog>" << endl;
#endif
} //----- Fin de StatLog (constructeur de copie)


StatLog::StatLog (ReadFile file, int startHeure, bool extFilter)
// Algorithme :
//
{
makeMap(file, extFilter, startHeure);
listeNode.sort();
listeNode.unique();

#ifdef MAP
    cout << "Appel au constructeur de <StatLog>" << endl;
#endif
} //----- Fin de StatLog


StatLog::~StatLog ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <StatLog>" << endl;
#endif
} //----- Fin de ~StatLog



//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

bool StatLog::compare ( pair < string, int > & a, pair < string, int > & b ) {
    return a.second < b.second;
}

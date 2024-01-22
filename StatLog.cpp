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
#include <vector>

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

    for ( map < string, map < string, int > >::iterator it = graph.begin ( ) ; it != graph.end ( ) ; ++it  )
    {
        for ( map < string, int >::iterator it2 = it -> second.begin ( ) ; it2 != it -> second.end ( ) ; ++it2  )
        {
            hitsByCible.push_back( make_pair ( it2 -> first, it2 -> second ) );
        }
    }

    sort ( hitsByCible.begin(), hitsByCible.end(), compare );

    int i = 1;

    while (i < hitsByCible.size() + 1 && i <= 10)
    {
        cout << hitsByCible[hitsByCible.size() - i].first << " (" << hitsByCible[hitsByCible.size() - i].second << " hits)" << endl;
        i++;
    }
} //----- makeTop10

void StatLog::makeMapLine(bool extFilter, int startHeure)
{
    vector <string> badExtensions = {".js", ".css", ".jpg", ".gif", ".png", ".ico", ".ics", ".doc", ".docx", ".pdf", ".xml", ".zip", ".txt"};

    if (startHeure != -1){
        int intHeure = int(getHeure())*10000 + int(getMinute())*100 + int(getSeconde());
        if (intHeure > startHeure || (startHeure > 230000 && startHeure + 10000 - 240000 > intHeure)){
            return;
        }   
    }

    else if (extFilter && find(badExtensions.begin(), badExtensions.end(), getExtension()) != badExtensions.end()){
        return; 
    }

    else if (getCode() == 400 || getCode == 500){
        return;
    }

    string source = getSource();
    string destination = getDestination();

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

void StatLog::makeMap(bool extFilter, int startHeure){
    while (file.getNextLogLine()){
        makeMapLine(extFilter, startHeure);
    }
    return;
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


StatLog::StatLog ( )
// Algorithme :
//
{
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

StatLog::bool compare ( pair < string, int > & a, pair < string, int > & b ) {
    return a.second < b.second;
}

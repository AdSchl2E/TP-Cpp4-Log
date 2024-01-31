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
#include <iomanip>


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
    int sumHits = 0;

    for ( map < string *, map < string *, int > >::iterator it = graph.begin ( ) ; it != graph.end ( ) ; ++it  ){

        sumHits = 0;

        for ( map < string *, int >::iterator it2 = it -> second.begin ( ) ; it2 != it -> second.end ( ) ; ++it2  ){

            sumHits += it2 -> second;
        }

        hitsByCible.push_back ( pair < string, int > ( *(it -> first), sumHits ) );
    }

    sort ( hitsByCible.begin(), hitsByCible.end(), compare );
    int i = 1;

    while ( i < hitsByCible.size() + 1 && i <= 10 ){

        cout << hitsByCible[hitsByCible.size() - i].first << " (" << hitsByCible[hitsByCible.size() - i].second << " hits)" << endl;
        i++;
    }
} //----- makeTop10

int StatLog::convertHourInt(const string & heureString) 
// format hh:mm:ss
{ 
    int heure = 0;

    heure += (heureString[0] - '0') * 100000;
    heure += (heureString[1] - '0') * 10000;
    heure += (heureString[3] - '0') * 1000;
    heure += (heureString[4] - '0') * 100;
    heure += (heureString[6] - '0') * 10;
    heure += (heureString[7] - '0');

    return heure; // format hhmmss
} //----- convertHourInt

void StatLog::makeMapLine(ReadFile & file, bool extFilter, int startHeure)
// Algorithme :
//
{
    vector <string> badExtensions = {".js", ".css", ".jpg", ".gif", ".png", ".ico", ".ics", ".doc", ".docx", ".pdf", ".xml", ".zip", ".txt"};
    bool acceptThisLine = true;

    if (startHeure != -1){

        string strHeure = file.getHour();
        int intHeure = convertHourInt(strHeure);

        if ((intHeure >= startHeure && intHeure < startHeure + 10000 ) || (startHeure >= 230000 && startHeure % 240000 + 10000 > intHeure)){
            
            acceptThisLine = false;
        }   
    }

    if (extFilter && find(badExtensions.begin(), badExtensions.end(), file.getExtension()) != badExtensions.end()){
        
        acceptThisLine = false; 
    }

    if (file.getStatus() == "400" || file.getStatus() == "500"){

        acceptThisLine = false;
    }

    if (acceptThisLine){

        string source = file.getUrlReferer();
        string destination = file.getUrlTarget();
        
        if (find(listeNode.begin(), listeNode.end(), source) == listeNode.end()){

            listeNode.push_back(source);
        }

        if (find(listeNode.begin(), listeNode.end(), destination) == listeNode.end()){

            listeNode.push_back(destination);
        }

        list < string >::iterator itSourceFound = find(listeNode.begin(), listeNode.end(), source);
        list < string >::iterator itDestFound = find(listeNode.begin(), listeNode.end(), destination);

        string* adresseSource = &(*itSourceFound);
        string* adresseDest = &(*itDestFound);

        if (graph.find(adresseDest) == graph.end()){       

            map <string *, int> newMap;
            graph.insert(pair<string *, map<string *, int>>(adresseDest, newMap));
        }
        
        if (graph[adresseDest].find(adresseSource) == graph[adresseDest].end()){        

            graph[adresseDest].insert(pair<string *, int>(adresseSource, 1));

        }else{

            graph[adresseDest][adresseSource]++;
        }

    }
    
}

void StatLog::makeMap(ReadFile & file, bool extFilter, int startHeure)
// Algorithme :
//
{
    while (file.getNextLogLine()){

        makeMapLine(file, extFilter, startHeure);
    }
}

void StatLog::makeDotFile( string dotFile )
// Algorithme :
//
{
    ofstream fout(dotFile.c_str());

    if( fout )    
    {
        fout << "digraph {" << endl;
        int i = 0;
        for( list < string >::iterator it = listeNode.begin(); it != listeNode.end(); it++)
        {
            fout << "\"" << &(*it) << "\" [label=\"" << *it << "\"];" << endl;
        }



        for ( map < string *, map < string *, int > >::iterator it = graph.begin ( ) ; it != graph.end ( ) ; ++it  )
        {
            for ( map < string *, int >::iterator it2 = it -> second.begin ( ) ; it2 != it -> second.end ( ) ; ++it2  )
            {
                fout << "\"" << it2 -> first << "\" -> \"" << it -> first << "\" [label=\"" << it2 -> second << "\"];" << endl;
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



//-------------------------------------------- Constructeurs - destructeur
StatLog::StatLog ( const StatLog & unStatLog )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <StatLog>" << endl;
#endif
} //----- Fin de StatLog (constructeur de copie)


StatLog::StatLog (ReadFile & file, int startHeure, bool extFilter)
// Algorithme :
//
{
makeMap(file, extFilter, startHeure);
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


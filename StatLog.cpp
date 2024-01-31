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
    cout << "on entre dans le makeTop10" << endl;
    int sumHits = 0;

    for ( map < string *, map < string *, int > >::iterator it = graph.begin ( ) ; it != graph.end ( ) ; ++it  )
    {
        sumHits = 0;
        cout << "on est dans le for" << endl;
        for ( map < string *, int >::iterator it2 = it -> second.begin ( ) ; it2 != it -> second.end ( ) ; ++it2  )
        {
            sumHits += it2 -> second;
        }

        hitsByCible.push_back ( pair < string, int > ( *(it -> first), sumHits ) );
    }

    cout << "on a fait le for" << endl;
    sort ( hitsByCible.begin(), hitsByCible.end(), compare );
    cout << "on a fait le sort" << endl;
    int i = 1;

    while ( i < hitsByCible.size() + 1 && i <= 10 )
    {
        cout << hitsByCible[hitsByCible.size() - i].first << " (" << hitsByCible[hitsByCible.size() - i].second << " hits)" << endl;
        i++;
    }
    cout << "on a fait le while" << endl;
} //----- makeTop10

int StatLog::convertHourInt(const string & heureString) { // format hh:mm:ss
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

    if (startHeure != -1){
        string strHeure = file.getHour();
        int intHeure = convertHourInt(strHeure);
        if (intHeure > startHeure || (startHeure > 230000 && startHeure + 10000 - 240000 > intHeure)){
            return; // Aled
        }   
    }

    else if (extFilter && find(badExtensions.begin(), badExtensions.end(), file.getExtension()) != badExtensions.end()){
        return; 
    }

    else if (file.getStatus() == "400" || file.getStatus() == "500"){
        return;
    }

    string source = file.getUrlReferer();
    string destination = file.getUrlTarget();
    
    // if source and destination are not in listeNode, add them
    if (find(listeNode.begin(), listeNode.end(), source) == listeNode.end()){
        listeNode.push_back(source);
    }
    if (find(listeNode.begin(), listeNode.end(), destination) == listeNode.end()){
        listeNode.push_back(destination);
    }

    cout << "La source qu'on regarde actuellement ================= " << source << endl;
    cout << "La destination qu'on regarde actuellement ================= " << destination << endl;
    
    list < string >::iterator itSourceFound = find(listeNode.begin(), listeNode.end(), source);
    list < string >::iterator itDestFound = find(listeNode.begin(), listeNode.end(), destination);

    cout << "listeNode : " << endl;
    for (list < string >::iterator it = listeNode.begin(); it != listeNode.end(); it++){
        cout << *it << endl;
    }
    cout << "adresse de " << source << " : " << &(*itSourceFound) << endl;
    cout << "adresse de " << destination << " : " << &(*itDestFound) << endl;

    string* adresseSource = &(*itSourceFound);
    string* adresseDest = &(*itDestFound);

    if (graph.find(adresseDest) == graph.end()){        // Il a pas trouvé l'adresseDest dans le graph

        cout << " --------------- L'adresse de la dest n'est pas dans le graph : " << adresseDest << endl;
        map <string *, int> newMap;
        graph.insert(pair<string *, map<string *, int>>(adresseDest, newMap));
    }
    
    if (graph[adresseDest].find(adresseSource) == graph[adresseDest].end()){         // Il a pas trouvé la destination dans l'adresseDest

        cout << "Il est là" << adresseDest << endl;

        graph[adresseDest].insert(pair<string *, int>(adresseSource, 1));
    }
    else
    {
        cout << "La mort ?" << endl;

        graph[adresseDest][adresseSource]++;
    }

    for ( map < string *, map < string *, int > >::iterator it = graph.begin ( ) ; it != graph.end ( ) ; ++it  )
    {
        cout << "______________________________________" << endl;
        for ( map < string *, int >::iterator it2 = it -> second.begin ( ) ; it2 != it -> second.end ( ) ; ++it2  )
        {
            cout << it -> first << "(" << *it->first << ") -> " << it2 -> first << "(" << *it2->first << ")  : " << it2 -> second << endl;
        }
    }

    cout << "==========================================================" << endl;
    return;
}

void StatLog::makeMap(ReadFile & file, bool extFilter, int startHeure)
// Algorithme :
//
{
    cout << "aled" << endl;
    while (file.getNextLogLine()){
        cout << "aled2" << endl;
        makeMapLine(file, extFilter, startHeure);
        cout << "aled3" << endl;
    }
    cout << "aled4" << endl;
    return;
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
cout << "Enfait makemap c'est fini" << endl;
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

string StatLog::adresseSansPrefixe(const string* adresse) {
    const char hex_digits[] = "0123456789ABCDEF";
    uintptr_t adresseInt = reinterpret_cast<uintptr_t>(adresse);

    std::string adresseStr;
    adresseStr.reserve(sizeof(uintptr_t) * 2);

    for (int i = sizeof(uintptr_t) * 2 - 1; i >= 0; --i) {
        int index = (adresseInt >> (i * 4)) & 0xF;
        adresseStr += hex_digits[index];
    }

    return adresseStr;
}

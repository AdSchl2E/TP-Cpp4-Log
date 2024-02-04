/*************************************************************************
                           StatLog  -  Analyse de logs Apache
                             -------------------
    début                : 15/01/2024
    copyright            : (C) 2024 par SCHLEE Adam et CHAPARD Clément : B3309
    e-mail               : adam.schlee@insa-lyon.fr, clement.chapard@insa-lyon.fr
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

void StatLog::DisplayTop10 ( void )
// Algorithme :
// On crée un vecteur de pair de string et int pour stocker les hits par cible
// On parcourt le graph et on ajoute les hits de chaque cible au vecteur
// On trie le vecteur par ordre décroissant
// On affiche les 10 premiers éléments du vecteur
{
    vector < pair < string, int > > hitsByCibleList;
    int sumHits = 0;

    for ( map < string *, map < string *, int > >::iterator it = graph.begin ( ) ; it != graph.end ( ) ; ++it  )
    {
        sumHits = 0;

        for ( map < string *, int >::iterator it2 = it -> second.begin ( ) ; it2 != it -> second.end ( ) ; ++it2  )
        {
            sumHits += it2 -> second;
        }

        hitsByCibleList.push_back ( pair < string, int > ( *(it -> first), sumHits ) );
    }

    sort ( hitsByCibleList.begin(), hitsByCibleList.end(), compare );
    unsigned int i = 1;

    cout << "------------------------ Top 10 -------------------------" << endl;
    while ( i < hitsByCibleList.size() + 1 && i <= 10 )
    {
        if ( i == 1 )
        {
            cout << right << setw(40) << hitsByCibleList[hitsByCibleList.size() - i].first << left << "" << " (" << hitsByCibleList[hitsByCibleList.size() - i].second << " hits)" << endl;
        }
        else
        {
        cout << right << setw(40) << hitsByCibleList[hitsByCibleList.size() - i].first << left << "" << " (" << hitsByCibleList[hitsByCibleList.size() - i].second << " hits)" << endl;
        }
        i++;
    }
    cout << "---------------------------------------------------------" << endl;
} //----- DisplayTop10

void StatLog::MakeDotFile( string dotFile )
// Algorithme :
// On crée le fichier dot à partir du graph
// On écrit les noeuds et les arcs dans le fichier
{
    ofstream fout(dotFile.c_str());

    if( fout )    
    {
        fout << "digraph {" << endl;
        fout << "node [shape=record];" << endl;
        for( list < string >::iterator it = nodeList.begin(); it != nodeList.end(); it++)
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
        cout << "Error : Impossible to open the file " << dotFile << endl;
    }
} //----- MakeDotFile

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

StatLog::StatLog (ReadFile & file, int startHour, bool extFilterOption, string localURL, bool redirectOption, bool verboseOption)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <StatLog>" << endl;
#endif

    makeMap(file, extFilterOption, startHour, localURL, redirectOption, verboseOption);

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

int StatLog::convertHourToInt(const string & hourString) const
// Algorithme :
// On convertit l'heure en string en int pour pouvoir la comparer
// On prend les caractères de l'hourString un par un et on les convertit en int
// On les multiplie par la puissance de 10 correspondante et on les ajoute à l'heure
// On renvoie l'heure en int au format hhmmss
// Contrat :
// L'heure doit être au format hh:mm:ss
{ 
    int hour = 0;

    hour += (hourString[0] - '0') * 100000;
    hour += (hourString[1] - '0') * 10000;
    hour += (hourString[3] - '0') * 1000;
    hour += (hourString[4] - '0') * 100;
    hour += (hourString[6] - '0') * 10;
    hour += (hourString[7] - '0');

    return hour;
} //----- convertHourToInt

void StatLog::makeMapLine(ReadFile & file, bool extFilterOption, int startHour, string localURL, bool redirectOption, bool verboseOption)
// Algorithme :
// On récupère les infos de la ligne du fichier de log et on les ajoute au graph
// On vérifie si la requête est valide (code 400 ou 500) et les filtres avant d'inserer dans le graph
{
    vector < string > badExtensionsList = {".js", ".css", ".jpg", ".gif", ".png", ".ico", ".ics", ".doc", ".docx", ".pdf", ".xml", ".zip", ".txt"};
    bool acceptThisLine = true;
    static int lineNumber = 0;

    lineNumber++;

    if (startHour != -1)
    {
        int intHeure = convertHourToInt(file.GetHour());

        if ((intHeure >= startHour && intHeure < startHour + 10000 ) || (startHour >= 230000 && startHour % 240000 + 10000 > intHeure))
        {  
            acceptThisLine = false;
        }   
    }

    if ( acceptThisLine != false && extFilterOption && find ( badExtensionsList.begin(), badExtensionsList.end(), file.GetExtension()) != badExtensionsList.end() )
    {
        acceptThisLine = false; 
    }
    else if ( file.GetStatus() == "400" || file.GetStatus() == "500" )
    {
        acceptThisLine = false;
    }

    if ( acceptThisLine )
    {
        string source = file.GetDomain() + file.GetUrlReferer();
        string target = file.GetUrlTarget();

        if (localURL != "")
        {
            source = removeBaseURL(source, localURL);
            target = removeBaseURL(target, localURL);
        }

        if ( ( redirectOption && source == "-" ) || source != "-" )
        {
            if (find(nodeList.begin(), nodeList.end(), source) == nodeList.end())
            {
                nodeList.push_back(source);
            }

            if (find(nodeList.begin(), nodeList.end(), target) == nodeList.end())
            {
                nodeList.push_back(target);
            }

            list < string >::iterator itSourceFound = find(nodeList.begin(), nodeList.end(), source);
            list < string >::iterator itTargetFound = find(nodeList.begin(), nodeList.end(), target);

            string* sourceAdress = &(*itSourceFound);
            string* targetAdress = &(*itTargetFound);

            if (graph.find(targetAdress) == graph.end())
            {       
                map <string *, int> newMap;
                graph.insert(pair<string *, map<string *, int>>(targetAdress, newMap));
            }
            
            if (graph[targetAdress].find(sourceAdress) == graph[targetAdress].end())
            {        
                graph[targetAdress].insert(pair<string *, int>(sourceAdress, 1));
            }
            else
            {
                graph[targetAdress][sourceAdress]++;
            }
        }

        if ( verboseOption )
        {   
            if ( localURL != "" )
            {
                cout << setw(50) << left << source << setw(25) << " -> " << target << endl;
            }
            else
            {
                cout << setw(50) << file.GetDomain() << file.GetUrlReferer() << setw(25) << " -> " << file.GetUrlTarget() << endl;
            }
        }
    }
} //----- makeMapLine

void StatLog::makeMap ( ReadFile & file, bool extFilterOption, int startHour, string localURL, bool redirectOption, bool verboseOption)
// Algorithme :
// On appelle la fonction pour créer le graphe complet à partir des infos du fichier log.
{
    while (file.GetNextLogLine())
    {
        makeMapLine(file, extFilterOption, startHour, localURL, redirectOption, verboseOption);
    }
}

bool StatLog::compare ( pair < string, int > & a, pair < string, int > & b )
// Algorithme :
// On compare deux pairs de string et int
{
    return a.second < b.second;
} //----- compare

string StatLog::removeBaseURL ( string & URL, string & localURL ) 
// Algorithme :
// On supprime la localURL de l'URL
// On renvoie l'URL sans la localURL
{
    if (URL.find(localURL) == 0) 
    {
        URL.erase(0, localURL.length());
    }
    return URL;
}


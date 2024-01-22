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

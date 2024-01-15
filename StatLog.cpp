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
    for ( map < string, map < string, int > >::iterator it = graph.begin ( ) ; it != graph.end ( ) ; ++it  )
    {
        cout << it -> first << endl;

        for ( map < string, int >::iterator it2 = it -> second.begin ( ) ; it2 != it -> second.end ( ) ; ++it2  )
        {
            cout << ">>>" << it2 -> first << endl;
            cout << ">>>" << it2 -> second << endl;
        }
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


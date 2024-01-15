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
    map < string, int > hitsByCible;
    
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

void StatLog::makeMapLine(bool extFilter, int startHeure)
{
    if (startHeure != -1){
        int intHeure = int(getHeure) + int(getMinute) + int(getSeconde);
        if (intHeure > startHeure || (startHeure > 230000 && startHeure + 10000 - 240000 > intHeure)){
            if (extFilter){

            }
        }
        
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


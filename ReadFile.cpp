/*************************************************************************
                           ReadFile  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <ReadFile> (fichier ReadFile.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "ReadFile.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type ReadFile::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


//------------------------------------------------- Surcharge d'opérateurs
ReadFile & ReadFile::operator = ( const ReadFile & unReadFile )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
ReadFile::ReadFile ( const ReadFile & unReadFile )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <ReadFile>" << endl;
#endif
} //----- Fin de ReadFile (constructeur de copie)


ReadFile::ReadFile ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <ReadFile>" << endl;
#endif
} //----- Fin de ReadFile


ReadFile::~ReadFile ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <ReadFile>" << endl;
#endif
} //----- Fin de ~ReadFile


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées


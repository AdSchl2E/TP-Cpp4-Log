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
// using namespace std;
// #include <iostream>

//------------------------------------------------------ Include personnel
#include "ReadFile.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string ReadFile::getIp () const
{
    return data.ip;
}

string ReadFile::getUserNameLog () const
{
    return data.userNameLog;
}

string ReadFile::getNameUser () const
{
    return data.nameUser;
}

string ReadFile::getDate () const
{
    return data.date;
}

string ReadFile::getHour () const
{
    return data.hour;
}

string ReadFile::getGmtModif () const
{
    return data.gmtModif;
}

string ReadFile::getRequest () const
{
    return data.request;
}

string ReadFile::getUrlTarget () const
{
    return data.urlTarget;
}

string ReadFile::getExtension () const
{
    return data.extension;
}

string ReadFile::getProtocolV () const
{
    return data.protocolV;
}

string ReadFile::getStatus () const
{
    return data.status;
}

string ReadFile::getDataSize () const
{
    return data.dataSize;
}

string ReadFile::getDomain () const
{
    return data.domain;
}

string ReadFile::getUrlReferer () const
{
    return data.urlReferer;
}

string ReadFile::getIdCli () const
{
    return data.idCli;
}

bool ReadFile::getNextLogLine ()
{
    string ligne;
    getline(rFlux, ligne);
    if (rFlux)
    {
        int start;
        int end;
        
        end = ligne.find(' ');
        data.ip = ligne.substr(0, end);

        start = end+1;
        end = ligne.find(' ', start);
        data.userNameLog = ligne.substr(start, end-start);

        start = end+1;
        end = ligne.find(' ', start);
        data.nameUser = ligne.substr(start, end-start);

        start = end+2;
        end = start+11;
        data.date = ligne.substr(start, end-start);

        start = end+1;
        end = start+8;
        data.hour = ligne.substr(start, end-start);

        start = end+1;
        end = start+5;
        data.gmtModif = ligne.substr(start, end-start);

        start = end+3;
        end = ligne.find(' ', start);
        data.request = ligne.substr(start, end-start);

        start = end+1;
        int tmp_start = start;
        end = ligne.find(' ', start);
        data.urlTarget = ligne.substr(start, end-start);

        start = end+1;
        end = ligne.find('"', start);
        data.protocolV = ligne.substr(start, end-start);

        start = tmp_start;
        int end_space = ligne.find(' ', start);
        int end_dot = ligne.find('.', start);
        if (end_dot < end_space)
        {
            data.extension = ligne.substr(end_dot, end_space-end_dot);
        }

        start = end+2;
        end = ligne.find(' ', start);
        data.status = ligne.substr(start, end-start);

        start = end+1;
        end = ligne.find(' ', start);
        data.dataSize = ligne.substr(start, end-start);

        start = end+2;
        if (ligne.substr(start, 1) == "-")
        {
            data.urlReferer = "-";
        }
        else
        {
            start = ligne.find('/', start) + 2;
            int end_guill = ligne.find('"', start);
            string test_slash = ligne.substr(start, end_guill-start);
            int slash = test_slash.find('/', 0);
            if (slash == -1)
            {
                end = end_guill;
            }
            else
            {
                end = ligne.find('/', start);
            }

            string test_url = ligne.substr(start, end-start);
            if (test_url == urlLocale)
            {
                start = end;
                data.domain = urlLocale;
            }
            else
            {
                data.domain = test_url;
            }

            start = end;
            end = ligne.find('"', start);
            test_url = ligne.substr(start, end-start);
            int test = test_url.find('?');
            if (slash == -1)
            {
                data.urlReferer = "/";
            }
            else if (test == -1)
            {
                data.urlReferer = test_url;
            }
            else
            {
                data.urlReferer = test_url.substr(0, test);
            }
            start = end+3;
            end = ligne.find('"', start);
            data.idCli= ligne.substr(start, end-start);
        }
        return true;
    }
    else
    {
        return false;
    }
}


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
ReadFile::ReadFile ( const ReadFile & unReadFile )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <ReadFile>" << endl;
#endif
} //----- Fin de ReadFile (constructeur de copie)


ReadFile::ReadFile (string fichier, string url)
// Algorithme :
//
{
    #ifdef MAP
        cout << "Appel au constructeur de <ReadFile>" << endl;
    #endif
    nomFic = fichier;
    urlLocale = url;
    rFlux.open(fichier);
    if ((rFlux.rdstate() & ifstream::failbit) != 0)
    {
        cerr << "Erreur : le fichier ne peut être ouvert, vérifiez sa validité" << endl;
        fileError = 1;
    }
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

/*************************************************************************
                           ReadFile  -  Lecture d'un fichier log et récupération des infos
                             -------------------
    début                : 15/01/2024
    copyright            : (C) 2024 par MANTZARIDES Guillaume et FELZINES Joris
    e-mail               : guillaume.mantzarides@insa-lyon.fr, joris.felzines@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <ReadFile> (fichier ReadFile.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "ReadFile.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
string ReadFile::GetIp () const
{
    return data.ip;
} //----- Fin de GetIp

string ReadFile::GetUserNameLog () const
{
    return data.userNameLog;
} //----- Fin de GetUserNameLog

string ReadFile::GetNameUser () const
{
    return data.nameUser;
} //----- Fin de GetNameUser

string ReadFile::GetDate () const
{
    return data.date;
} //----- Fin de GetDate

string ReadFile::GetHour () const
{
    return data.hour;
} //----- Fin de GetHour

string ReadFile::GetGmtModif () const
{
    return data.gmtModif;
} //----- Fin de GetGmtModif

string ReadFile::GetRequest () const
{
    return data.request;
} //----- Fin de GetRequest

string ReadFile::GetUrlTarget () const
{
    return data.urlTarget;
} //----- Fin de GetUrlTarget

string ReadFile::GetExtension () const
{
    return data.extension;
} //----- Fin de GetExtension

string ReadFile::GetProtocolV () const
{
    return data.protocolV;
} //----- Fin de GetProtocolV

string ReadFile::GetStatus () const
{
    return data.status;
} //----- Fin de GetStatus

string ReadFile::GetDataSize () const
{
    return data.dataSize;
} //----- Fin de GetDataSize

string ReadFile::GetDomain () const
{
    return data.domain;
} //----- Fin de GetDomain

string ReadFile::GetUrlReferer () const
{
    return data.urlReferer;
} //----- Fin de GetUrlReferer

string ReadFile::GetIdCli () const
{
    return data.idCli;
} //----- Fin de GetIdCli

int ReadFile::GetFileError () const
{
    return fileError;
} //----- Fin de GetFileError

bool ReadFile::GetNextLogLine ()
{
    string line;
    getline(rFlux, line);

    if (rFlux)
    {
        int start;
        int end;
        
        end = line.find(' ');
        data.ip = line.substr(0, end);

        start = end+1;
        end = line.find(' ', start);
        data.userNameLog = line.substr(start, end-start); 

        start = end+1;
        end = line.find(' ', start);
        data.nameUser = line.substr(start, end-start);

        start = end+2;
        end = start+11;
        data.date = line.substr(start, end-start);

        start = end+1;
        end = start+8;
        data.hour = line.substr(start, end-start);

        start = end+1;
        end = start+5;
        data.gmtModif = line.substr(start, end-start);

        start = end+3;
        end = line.find(' ', start);
        data.request = line.substr(start, end-start);

        start = end+1;
        int tmpStart = start;
        end = line.find(' ', start);
        data.urlTarget = line.substr(start, end-start);

        start = end+1;
        end = line.find('"', start);
        data.protocolV = line.substr(start, end-start);

        start = tmpStart;
        int endSpace = line.find(' ', start);
        int endDot = line.find('.', start);

        if (endDot < endSpace)
        {
            data.extension = line.substr(endDot, endSpace-endDot);
        }

        start = end+2;
        end = line.find(' ', start);
        data.status = line.substr(start, end-start);

        start = end+1;
        end = line.find(' ', start);
        data.dataSize = line.substr(start, end-start);

        start = end+2;

        if (line.substr(start, 1) == "-")
        {
            data.urlReferer = "-";
        }
        else
        {
            start = line.find('/', start) + 2;
            int endGuill = line.find('"', start);
            string testSlash = line.substr(start, endGuill-start);
            int slash = testSlash.find('/', 0);
            
            if (slash == -1)
            {
                end = endGuill;
            }
            else
            {
                end = line.find('/', start);
            }

            string testUrl = line.substr(start, end-start);

            if (testUrl == localURL)
            {
                start = end;
                data.domain = localURL;
            }
            else
            {
                data.domain = testUrl;
            }

            start = end;
            end = line.find('"', start);
            testUrl = line.substr(start, end-start);
            int test = testUrl.find('?');

            if (slash == -1)
            {
                data.urlReferer = "/";
            }
            else if (test == -1)
            {
                data.urlReferer = testUrl;
            }
            else
            {
                data.urlReferer = testUrl.substr(0, test);
            }

            start = end+3;
            end = line.find('"', start);
            data.idCli= line.substr(start, end-start);
        }

        return true;
    }
    else
    {
        return false;
    }
} //----- Fin de GetNextLogLine
 
//-------------------------------------------- Constructeurs - destructeur

ReadFile::ReadFile (string file, string url)
// Algorithme :
// On ouvre le fichier et on vérifie qu'il est bien ouvert
{
    #ifdef MAP
        cout << "Appel au constructeur de <ReadFile>" << endl;
    #endif

    fileName = file;
    localURL = url;
    rFlux.open(file);

    if ((rFlux.rdstate() & ifstream::failbit) != 0)
    {
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


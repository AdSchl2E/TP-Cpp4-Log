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
    cout << "pk tu tarrrete la ?" << rFlux.rdstate() << endl;
    if (rFlux.rdstate() == 0 || rFlux.rdstate() == 2)   // 0 = ok, 2 = eof (apparement enft 2 c failbit mais ça tourne quand meme si on l'inclue, a voir)
    {
        int start;
        int end;
        
        end = ligne.find(' ');
        cout << "111" << endl;
        data.ip = ligne.substr(0, end);

        start = end+1;
        end = ligne.find(' ', start);
        cout << "116" << endl;
        data.userNameLog = ligne.substr(start, end-start);

        start = end+1;
        end = ligne.find(' ', start);
        cout << "121" << endl;
        data.nameUser = ligne.substr(start, end-start);

        start = end+2;
        end = start+11;
        cout << "126" << endl;
        data.date = ligne.substr(start, end-start);

        start = end+1;
        end = start+8;
        cout << "131" << endl;
        data.hour = ligne.substr(start, end-start);

        start = end+1;
        end = start+5;
        cout << "136" << endl;
        data.gmtModif = ligne.substr(start, end-start);

        start = end+3;
        end = ligne.find(' ', start);
        cout << "141" << endl;
        data.request = ligne.substr(start, end-start);

        start = end+1;
        int tmp_start = start;
        end = ligne.find(' ', start);
        cout << "146" << endl;
        data.urlTarget = ligne.substr(start, end-start);

        start = end+1;
        end = ligne.find('"', start);
        cout << "151" << endl;
        data.protocolV = ligne.substr(start, end-start);

        start = tmp_start;
        int end_space = ligne.find(' ', start);
        int end_dot = ligne.find('.', start);
        if (end_dot < end_space)
        {
            cout << "160" << endl;
            data.extension = ligne.substr(end_dot, end_space-end_dot);
        }

        start = end+2;
        end = ligne.find(' ', start);
        cout << "166" << endl;
        data.status = ligne.substr(start, end-start);

        start = end+1;
        end = ligne.find(' ', start);
        cout << "171" << endl;
        data.dataSize = ligne.substr(start, end-start);

        start = end+2;
        cout << "175" << endl;
        if (ligne.substr(start, 1) == "-")
        {
            data.urlReferer = "-";
        }
        else
        {
            start = ligne.find('/', start) + 2;
            end = ligne.find('/', start);
            cout << "184" << endl;
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
            cout << "198" << endl;
            test_url = ligne.substr(start, end-start);
            int test = test_url.find('?');
            if (test == -1)
            {
                data.urlReferer = test_url;
            }
            else
            {   
                cout << "207" << endl;
                cout << "test_url : " << test_url << endl;
                data.urlReferer = test_url.substr(start, test-start); // Erreur ici ligne 97 du gros log file (anonyme.log)
                cout << "209" << endl;
            }

            cout << "211" << endl;
            start = end+3;
            cout << "213" << endl;
            end = ligne.find('"', start);
            cout << "215" << endl;
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
    cout << "ReadFile.cpp - 237 " << rFlux.rdstate() << endl;
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

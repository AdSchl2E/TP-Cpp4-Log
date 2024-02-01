#include "ReadFile.h"
#include "StatLog.h"

int main(int argc, char* argv[]) 
{
    bool extFilter = false;
    int startHeure = -1;
    string logFile;
    string dotFile = "";
    string baseURL = "";
    bool aled = false;
    bool redirect = false;
    bool parametreDotFile;

    for (int i = 1; i < argc; i++) 
    {
        if (argv[i][0] == '-') 
        {
            switch (argv[i][1]) 
            {
                case 'e':

                    extFilter = true;
                    
                    break;

                case 't':

                    startHeure = atoi(argv[i + 1]);
                    
                    break;

                case 'g':

                    dotFile = argv[i + 1];
                    parametreDotFile = true;

                    break;

                case 'u':

                    baseURL = argv[i + 1];

                    break;

                case 'h':

                    aled = true;

                    break;

                case 'r':

                    redirect = true;
                
                    break;

                default:

                    cerr << "Erreur : L'option " << argv[i] << " n'existe pas" << endl;

                    return 1;
            }
        }
    }

    if (!aled)
    {
        if (argc > 1)
        {
            logFile = argv[argc - 1];
        }
        else
        {
            cerr << "Erreur : pas de fichier log" << endl;
            return 1;
        }

        // On affiche les paramètres
        /*
        cout << "extFilter : " << extFilter << endl;
        cout << "startHeure : " << startHeure << endl;
        cout << "logFile : " << logFile << endl;
        cout << "dotFile : " << dotFile << endl;
        cout << "baseURL : " << baseURL << endl;
        cout << "redirect : " << redirect << endl;
        */

        ReadFile File(logFile, baseURL);        // Pareil il faut une val par defaut pour baseURL qui soit compréhensible par le constructeur de ReadFile pour ne pas le prendre en compte quand il n'est pas activé

        if (startHeure != -1) 
        {
            if (startHeure < 0 || startHeure > 23)
            {
                cerr << "Erreur : " << startHeure << " heure invalide" << endl;
                return 1;
            }
            
            cout << "Warning : only hits between " << startHeure << "h and " << (startHeure + 1)%24 << "h have been taken into account" << endl;

            startHeure *= 10000;
        }

        if (extFilter) 
        {
            cout << "Warning : .js, .css, .jpg, .gif, .png, .ico, .ics, .doc, .docx, .pdf, .xml, .zip and .txt extensions have been excluded" << endl;
        }

        if (baseURL != "") 
        {
            cout << "Warning : the base URL is " << baseURL << endl;
        }

        if (redirect) 
        {
            cout << "Warning : the standard output has been redirected to a file" << endl;
        }

        StatLog Stat(File, startHeure, extFilter);  // Faudrait des valeurs par defaut pour startHeure et extFilter qui soit compréhensible par le constructeur de StatLog pour ne pas les prendre en compte quand ils ne sont pas activé

        if (parametreDotFile) 
        {
            if (dotFile == "" || dotFile == logFile) 
            {                    // A voir si c utile de faire ça
                cerr << "Erreur : pas de nom de fichier dot" << endl;
            } 
            else 
            {
                cout << "Dot-file " << dotFile << " in generation..." << endl;
                Stat.makeDotFile(dotFile);
                cout << "Dot-file " << dotFile << " generated" << endl;
            }
        }

        Stat.makeTop10();                           // Apparement on l'affiche dans tout les cas
    } 
    else 
    { // If aled
        cout << "Usage : ./analog [-e] [-t heure] [-g dotFile] [-u baseURL] [-h] [-r] <fichier.log>" << endl;
        cout << "Options :" << endl;
        cout << "-e : filtre les extensions" << endl;
        cout << "-t heure : filtre entre heure et heure + 1" << endl;
        cout << "-g dotFile : crée un fichier dot" << endl;
        cout << "-u baseURL : crée un fichier dot avec une url de base" << endl;
        cout << "-h : affiche l'aide" << endl;
        cout << "-r : redirige la sortie standard vers un fichier" << endl; // C'est quoi ??
        cout << "<fichier.log> : fichier de log à analyser" << endl;
    }
    
    return 0;
}

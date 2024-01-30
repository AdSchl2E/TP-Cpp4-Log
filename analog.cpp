#include <iostream>
#include <string>
#include <vector>
#include "ReadFile.h"
#include "StatLog.h"

using namespace std;

int main(int argc, char* argv[]) {
    // On récupère les paramètres
    bool extFilter = false;
    string startHeure = "-1";
    string logFile;
    string dotFile = "";
    string baseURL = "";
    bool aled = false;
    bool redirect = false;
    bool extWarning = false;
    bool parametreHour = false;
    bool parametreDotFile;

    // Le logfile est le dernier paramètre

    for (int i = 1; i < argc; i++) {

        if (argv[i][0] == '-') {

            switch (argv[i][1]) {

                case 'e':

                    extFilter = true;

                    if (argv[i+1][0] == '-') {

                        extWarning = true;
                    }

                    break;

                case 't':

                    startHeure = atoi(argv[i + 1]);

                    parametreHour = true;

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

                    cerr << "L'option " << argv[i] << " n'existe pas" << endl;

                    return 1;
            }
        }
    }

    if (!aled){
    vector <string> flagsWithParameters = {"-t", "-g", "-u"};

    if (argc = 2 || (argc > 2 && find(flagsWithParameters.begin(), flagsWithParameters.end(), argv[argc - 2]) != flagsWithParameters.end())) {
        logFile = argv[argc - 1];
    }
    
    else{

        cerr << "Erreur : pas de fichier log" << endl;
    }

        // On affiche les paramètres
        cout << "extFilter : " << extFilter << endl;
        cout << "startHeure : " << startHeure << endl;
        cout << "logFile : " << logFile << endl;
        cout << "dotFile : " << dotFile << endl;
        cout << "baseURL : " << baseURL << endl;
        cout << "aled : " << aled << endl;
        cout << "redirect : " << redirect << endl;

        ReadFile File("court.log", baseURL);        // Pareil il faut une val par defaut pour baseURL qui soit compréhensible par le constructeur de ReadFile pour ne pas le prendre en compte quand il n'est pas activé

        StatLog Stat(File, startHeure, extFilter);  // Faudrait des valeurs par defaut pour startHeure et extFilter qui soit compréhensible par le constructeur de StatLog pour ne pas les prendre en compte quand ils ne sont pas activé

        Stat.makeTop10();                           // Apparement on l'affiche dans tout les cas

        
        
        if (extWarning) {

            cerr << "Attention : pas de parmètre après -e" << endl;
        }
        
        if (parametreDotFile) {

            if (dotFile == "" || dotFile[0] == '-') {

                cerr << "Erreur : pas de nom de fichier dot" << endl;
                return 1;

            } else {

                Stat.makeDotFile(dotFile);
            }
        }
        else if (parametreHour) {
            if (size(startHeure) != 8) {
                cerr << "Erreur : format d'heure invalide (valeur attendu : HH:MM:SS)" << endl;
                return 1;

            } else if (atoi(startHeure[0] + startHeure[1]) > 24 || atoi(startHeure[3] + startHeure[4]) > 60 || atoi(startHeure[6] + startHeure[7]) > 60){
                cerr << "Erreur : format d'heure invalide - il faut HH < 24, MM < 60 et SS < 60" << endl;
                return 1;  
            }

        }




        

    } else { // If aled

        cout << "Usage : ./analog [-e] [-t heure] [-g dotFile] [-u baseURL] [-h] [-r] <fichier.log>" << endl;
        cout << "Options :" << endl;
        cout << "-e : filtre les extensions" << endl;
        cout << "-t heure : filtre les heures" << endl;
        cout << "-g dotFile : crée un fichier dot" << endl;
        cout << "-u baseURL : crée un fichier dot avec une url de base" << endl;
        cout << "-h : affiche l'aide" << endl;
        cout << "-r : redirige la sortie standard vers un fichier" << endl;
        cout << "<fichier.log> : fichier de log à analyser" << endl;
    }
    
    return 0;
}

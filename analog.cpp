#include <iostream>
#include <string>
#include <vector>
#include "ReadFile.h"
#include "StatLog.h"

using namespace std;

int main(int argc, char* argv[]) {
    // On récupère les paramètres
    bool extFilter = false;
    int startHeure = -1;
    string logFile;
    string dotFile = "";
    string baseURL = "";
    bool aled = false;
    bool redirect = false;

    bool parametreDotFile;

    // Le logfile est le dernier paramètre

    for (int i = 1; i < argc; i++) {

        if (argv[i][0] == '-') {

            switch (argv[i][1]) {

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

                    cerr << "L'option " << argv[i] << " n'existe pas" << endl;

                    return 1;
            }
        }
    }

    if (!aled){

        if (argc > 1){

            logFile = argv[argc - 1];
            cout << "logFile : " << logFile << endl;

        }else{

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


        //aled
        StatLog Stat(File, startHeure, extFilter);  // Faudrait des valeurs par defaut pour startHeure et extFilter qui soit compréhensible par le constructeur de StatLog pour ne pas les prendre en compte quand ils ne sont pas activé
        cout << "pas aled" << endl;
        Stat.makeTop10();                           // Apparement on l'affiche dans tout les cas
        cout << "pas aled2" << endl;
        if (parametreDotFile) {

            if (dotFile == "") {                    // A voir si c utile de faire ça

                cerr << "Erreur : pas de nom de fichier dot" << endl;

            } else {

                Stat.makeDotFile(dotFile);
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

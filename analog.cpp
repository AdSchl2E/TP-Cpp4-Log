#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    // On récupère les paramètres
    bool extFilter;
    int startHeure;
    string logFile{};
    string dotFile{};
    string baseURL{};
    bool aled;
    bool redirect;
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
                    break;
            }
        }
    }
    if (!aled){
        if (argc > 1){
            logFile = argv[argc - 1];
        }
        else{
            cout << "Erreur : pas de fichier log" << endl;
        }
    }
    

    // On affiche les paramètres
    cout << "extFilter : " << extFilter << endl;
    cout << "startHeure : " << startHeure << endl;
    cout << "logFile : " << logFile << endl;
    cout << "dotFile : " << dotFile << endl;
    cout << "baseURL : " << baseURL << endl;
    cout << "aled : " << aled << endl;
    cout << "redirect : " << redirect << endl;

    
    
    return 0;
}

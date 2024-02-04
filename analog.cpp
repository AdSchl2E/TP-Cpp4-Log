#include "ReadFile.h"
#include "StatLog.h"

int main(int argc, char* argv[]) 
{
    string logFile;
    string dotFile = "";
    string localURL = "";
    int startHour = -1;
    bool helpOption = false;
    bool extFilterOption = false;
    bool redirectOption = false;
    bool verboseOption = false;
    bool dotFileOption = false;
    
    for (int i = 1; i < argc; i++) 
    {
        if (argv[i][0] == '-') 
        {
            switch (argv[i][1]) 
            {
                case 'e':

                    extFilterOption = true;
                    
                    break;

                case 't':

                    if (argv[i + 1][0] == '-' || i == argc - 2) 
                    {
                        cerr << "Error : The option -t must be followed by an hour" << endl;
                        return 1;
                    }

                    startHour = atoi(argv[i + 1]);
                    
                    break;

                case 'g':

                    if (argv[i + 1][0] == '-' || i == argc - 2) 
                    {
                        cerr << "Error : The option -g must be followed by a file name" << endl;
                        return 1;
                    }

                    dotFile = argv[i + 1];
                    dotFileOption = true;

                    break;

                case 'u':

                    if (argv[i + 1][0] == '-' || i == argc - 2) 
                    {
                        cerr << "Error : The option -u must be followed by a local URL" << endl;
                        return 1;
                    }

                    localURL = argv[i + 1];

                    break;

                case 'h':

                    helpOption = true;

                    break;

                case 'r':

                    redirectOption = true;
                
                    break;

                case 'v':

                    verboseOption = true;

                    break;

                default:

                    cerr << "Error : The option " << argv[i] << " is not recognized" << endl;
                    return 1;
            }
        }
    }

    if (!helpOption)
    {   
        if(argc > 1 && argv[argc - 1][0] != '-')
        {
            logFile = argv[argc - 1];
        }
        else
        {
            cerr << "Error : The log file is missing" << endl;
            cerr << "Type ./analog -h for help" << endl;
            return 1;
        }

        ReadFile File(logFile, localURL);      

        if (File.GetFileError() == 1)
        {
            cerr << "Error : The file " << logFile << " does not exist or cannot be opened" << endl;
            return 1;
        }

        if (verboseOption) 
        {

            cout << "----------------------- Options ------------------------" << endl;
            cout << "option -v : Verbose mode" << endl;

            if (extFilterOption) 
            {
                cout << "option -e : .js, .css, .jpg, .gif, .png, .ico, .ics, .doc, .docx, .pdf, .xml, .zip and .txt extensions have been excluded" << endl;
            }

            if (localURL != "") 
            {
                cout << "option -u " << localURL << " : The local URL is " << localURL << endl;
            }
            else
            {
                localURL = "intranet-if.insa-lyon.fr";
                cout << "Default local URL is \"" << localURL << "\"" << endl;
            }

            if (redirectOption) 
            {
                cout << "option -r : Redirection have been taken into account" << endl;
            }

            if (dotFileOption) 
            {
                cout << "option -g " << dotFile << " : A dot-file named " << dotFile << " will be generated" << endl;
            }
        }

        if (startHour != -1) 
        {
            if (startHour < 0 || startHour > 23)
            {
                cerr << "Error : " << startHour << " is an invalid hour, it must be between 0 and 23" << endl;
                return 1;
            }
            
            if (verboseOption) 
            {
                cout << "option -t " << startHour << " : Only hits between " << startHour << "h and " << (startHour + 1)%24 << "h have been taken into account" << endl;
            }

            startHour *= 10000;
        }

        if(verboseOption) 
        {
            cout << " --------------------------------------------------------" << endl;
            cout << "File " << logFile << " is being analyzed..." << endl;
            cout << "----------------------- Process -------------------------" << endl;
        }

        StatLog Stat(File, startHour, extFilterOption, localURL, redirectOption, verboseOption); 

        if(verboseOption) 
        {
            cout << "---------------------------------------------------------" << endl;
        }

        if(dotFileOption) 
        {
            cout << "Dot-file " << dotFile << " in generation..." << endl;
            Stat.MakeDotFile(dotFile);
            cout << "Dot-file " << dotFile << " generated" << endl;
            cout << "Command to generate the graph : dot -Tpng " << dotFile << " -o out.png" << endl;
        }

        Stat.DisplayTop10();                       
    } 
    else 
    { // If helpOption
        cout << "------------------------ Help -------------------------" << endl;
        cout << "Usage : ./analog [-e] [-t hour] [-g dotFile] [-u localURL] [-h] [-r] [-v] <file.log>" << endl;
        cout << "Options :" << endl;
        cout << "-e : Excludes some extensions (.js, .css, .jpg, .gif, .png, .ico, .ics, .doc, .docx, .pdf, .xml, .zip and .txt)" << endl;
        cout << "-t hour : Only takes into account the hits between hour and hour + 1" << endl;
        cout << "-g dotFile : Generates a dot file" << endl;
        cout << "-u localURL : Allows you to specify a local URL (default: intranet-if.insa-lyon.fr)" << endl;
        cout << "-h : Displays the help" << endl;
        cout << "-r : Takes into account the redirections" << endl; // A préciser
        cout << "-v : Verbose mode" << endl;  
        cout << "<file.log> : Log file to be analyzed" << endl;
        cout << "--------------------------------------------------------" << endl;
    }
    
    return 0;
}

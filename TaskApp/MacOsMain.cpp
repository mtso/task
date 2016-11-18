// MacOsMain.cpp
// TaskApp
// CIS 22C F2016: Matthew Tso
//
// Task's command line interface for macOS platforms

#include <iostream>
#include <string>

#include "Sha1.h"
#include "Diagnostic.h"

#include "TaskConfiguration.h"

void runDiagnostic();

int main(int argc, char* argv[])
{
    cout << "task v" << taskconfig::VERSION  << endl;
    
    string input;
    bool isRunning = true;
    
    do {
        cout << "> ";
        cin >> input;
        
        using namespace taskconfig;

        switch ( toupper(input[0]) )
        {
            case COMMAND_TEST:
                runDiagnostic();
                break;
            
            case COMMAND_CREDITS:
                cout << CREDITS << endl;
                break;
                
            case COMMAND_QUIT:
                isRunning = false;
                break;
            
            default:
                break;
        }
        
    } while (isRunning);
    
    return 0;
}

void runDiagnostic()
{
    task::Diagnostic diagnostic;
    diagnostic.runAndPrintTo(std::cout);
}

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
        // Prompt caret
        cout << "> ";
        cin >> input;
        
        using namespace taskconfig;

        switch ( toupper(input[0]) )
        {
            case COMMAND_TEST_CH:
                runDiagnostic();
                break;
            
            case COMMAND_CREDITS_CH:
                cout << CREDITS << endl;
                break;
                
            case COMMAND_QUIT_CH:
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

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

unsigned long
hash_func(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;
    
    while (c = *(str++)) { // When the null terminator is assigned into c, it becomes 0
        hash += (hash << 5) + c; // hash * 33 + c
    }
    
    return hash;
}

int main(int argc, char* argv[])
{
//    // Code for testing the hash_func
//    unsigned long hash_l;
//    unsigned char* input_h = (unsigned char*)"what";
//    
//    unsigned char* inputs[5] = {
//        (unsigned char*)"",
//        (unsigned char*)"a",
//        (unsigned char*)"i cannot believe",
//        (unsigned char*)"huh what does it mean",
//        (unsigned char*)"whatevs"
//    };
//    
//    for (int i = 0; i<5; i++) {
//        hash_l = hash_func(inputs[i]);
//        cout << hash_l << endl;
//    }
    
    // Begin console process by printing version number
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

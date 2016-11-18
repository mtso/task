// Main.cpp : Defines the entry point for the console application.
// TaskApp
// CIS 22C F2016: Matthew Tso

/**
 * An example of the static library usage in a console process
 */

#include <iostream>
#include <string>

#include "Sha1.h"
#include "Diagnostic.h"

int main(int argc, char* argv[])
{

//    std::cout << "The SHA-1 hash:\n" << task::sha_1("1479442948986\"Implement BST node\"status=\"backlog\"") << std::endl;
    
    task::Diagnostic diagnostic;
    diagnostic.runAndPrintTo(std::cout);
    
    std::cout << std::endl;
    return 0;
}


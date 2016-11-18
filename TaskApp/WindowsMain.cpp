// WindowsMain.cpp
// TaskApp
// CIS 22C F2016: Adrian Marroquin
//
// WindowsMain is the entry point into Tasks's 
// interactive shell on Windows platforms.

#include <iostream>
#include <string>

#include "TaskConfiguration.h"
#include "Utilities\Sha1.h"
#include "Utilities\Diagnostic.h"

int main(int argc, char* argv[])
{
	std::cout << "task v" << taskconfig::VERSION << endl;

	task::Diagnostic diagnostic;
	diagnostic.runAndPrintTo(10, std::cout);

	system("PAUSE");
	return 0;
}


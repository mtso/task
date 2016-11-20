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

#include "ADT\Stack.h"

using namespace std;

int main(int argc, char* argv[])
{
	std::cout << "task v" << taskconfig::VERSION << endl;

	task::Diagnostic diagnostic;
	diagnostic.runAndPrintTo(10, std::cout);

	adt::Stack<int> ints;
	ints.push(4);

	cout << ints.pop() << endl;

	system("PAUSE");
	return 0;
}


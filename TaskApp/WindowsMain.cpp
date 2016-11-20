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

#include "Stack.h"
#include "Queue.h"

int main(int argc, char* argv[])
{
	std::cout << "task v" << taskconfig::VERSION << endl;

	task::Diagnostic diagnostic;
	diagnostic.runAndPrintTo(10, std::cout);

	adt::Stack<int> stack;
	stack.push(1000);
	cout << stack.pop() << endl;

	system("PAUSE");
	return 0;
}


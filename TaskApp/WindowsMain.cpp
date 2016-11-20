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

#include "TaskEntry.h"

using namespace std;

int main(int argc, char* argv[])
{
	std::cout << "task v" << taskconfig::VERSION << endl;

	task::Diagnostic diagnostic;
	diagnostic.runAndPrintTo(10, std::cout);
	cout << endl;

	task::TaskEntry new_entry = task::TaskEntry("Implement TaskEntry data model");
	cout << new_entry.getDescription() << endl;
	cout << new_entry.getId() << endl;
	cout << new_entry.getTimeCreatedMs() << endl;
	cout << new_entry.getTimeCreatedStr() << endl;

	if (new_entry.getStatus() == BACKLOG) {
		cout << "Status: Backlog" << endl;
	}

	system("PAUSE");
	return 0;
}


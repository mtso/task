// WindowsMain.cpp
// TaskApp
// CIS 22C F2016: Adrian Marroquin
//
// WindowsMain is the entry point into Tasks's 
// interactive shell on Windows platforms.

#include <iostream>
#include <string>

#include "AppConstants.h"
#include "WindowsDirectory.h"
#include "Configuration.h"
#include "Pager.h"

#include "Utilities\Sha1.h"
#include "Utilities\Diagnostic.h"

#include "TaskEntry.h"


using namespace std;

int main(int argc, char* argv[])
{
	// Output version number specified in AppConstants.h
	std::cout << "task v" << taskconfig::VERSION << endl;


	// DEMO CODE
	// Diagnostic usage
	task::Diagnostic diagnostic;
	diagnostic.runAndPrintTo(10, std::cout);
	cout << endl;


	// DEMO CODE
	// Task entry usage
	task::TaskEntry new_entry = task::TaskEntry("mryagni", "Implement TaskEntry data model");
	cout << new_entry.getDescription() << endl;
	cout << new_entry.getId() << endl;
	cout << new_entry.getTimeCreatedMs() << endl;
	cout << new_entry.getTimeCreatedStr() << endl;
	cout << new_entry.getCreator() << endl;

	if (new_entry.getStatus() == BACKLOG) {
		cout << "Status: Backlog" << endl;
	}

	cout << endl;


	// DEMO CODE
	// WindowsDirectory filename search usage
	//TCHAR* data_dir = TEXT("..\\.task");
	TCHAR* data_dir = TEXT("..\\");

	try {
		taskapp::filenamesIn(data_dir);
	}
	catch (const char* error) {
		cout << error << endl;
	}
	catch (...) {
		cout << "Could not catch error";
	}
	cout << endl;
	

	// DEMO CODE
	// Pager.h usage
	// Outputs an array of string content at a managed pace.
	const int content_length = 10;
	const int lines_per_page = 3;
	const string sample_content[content_length] = {
		"line 1: ", "line 2: ", "line 3: ", "line 4: ", "line 5: ",
		"line 6: ", "line 7: ", "line 8: ", "line 9: ", "line 10: "
	};
	app_util::page(sample_content, content_length, lines_per_page);

	system("PAUSE");
	return 0;
}


// WindowsMain.cpp
// TaskApp
// CIS 22C F2016: Adrian Marroquin
//
// WindowsMain is the entry point into Tasks's 
// interactive shell on Windows platforms.
//
//
// TODO: need to figure out TCHAR <=> string conversion
// maybe: http://stackoverflow.com/questions/22910344/c-read-a-file-line-by-line-but-line-type-is-cstring-or-tchar

// Temporary test includes
#include <fstream>

// Includes all usable Task headers.
#include "TaskLib.h"

// Includes all TaskApp utility headers
#include "AppIncludes.h"

int main(int argc, char* argv[])
{
	// Output version number specified in AppConstants.h
	cout << "task v" << taskconfig::VERSION << endl;


	// DEMO CODE
	// Diagnostic usage
	task::Diagnostic diagnostic;
	diagnostic.runAndPrintTo(10, std::cout);
	cout << endl;


	// DEMO CODE
	// Task entry usage
	task::TaskEntry new_entry = task::TaskEntry("mryagni", "Implement TaskEntry data model");
	cout << red << new_entry.getDescription() << endl;
	cout << blue << new_entry.getId() << endl;
	cout << red << new_entry.getTimeCreatedMs() << endl;
	cout << blue << new_entry.getTimeCreatedStr() << endl;
	cout << red << new_entry.getCreator() << endl;

	if (new_entry.getStatus() == BACKLOG) {
		cout << "Status: Backlog" << endl;
	}
	cout << endl;


	// TESTING CODE
	// Output entry to a demo tasklog file
	uint64_t due_1week = new_entry.getTimeCreatedMs() + 604800000;
	new_entry.setTimeDueMs(due_1week);

	string entry_status;
	switch (new_entry.getStatus()) {
	case IN_PROGRESS:
		entry_status = taskconfig::STATUS_STR_INPROGRESS;
		break;

	case COMPLETE:
		entry_status = taskconfig::STATUS_STR_COMPLETE;
		break;

	default:
		entry_status = taskconfig::STATUS_STR_BACKLOG;
		break;
	}

	// Create an entry for mryagni
	ostringstream entry_buffer;
	entry_buffer << new_entry.getId() << "\t"
		<< new_entry.getTimeCreatedMs() << "\t"
		<< new_entry.getTimeDueMs() << "\t"
		<< "\"" << new_entry.getDescription() << "\"\t" 
		<< "status=" << entry_status << "\n";

	ofstream mryagni_log;
	string data_rootdir = "..\\.task\\tasklog-";

	// Print the entry to mryagni's tasklog
	mryagni_log.open(data_rootdir + new_entry.getCreator(), ios::app);
	mryagni_log << yellow << entry_buffer.str();
	mryagni_log.close();


	// DEMO CODE
	// WindowsDirectory filename search usage
	//TCHAR* data_dir = TEXT("..\\.task");
	TCHAR* data_dir = TEXT("..\\");
	cout << data_dir;

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
	const int lines_per_page = 7;
	cout << green;
	const string sample_content[content_length] = {
		"line 1: ", "line 2: ", "line 3: ", "line 4: ", "line 5: ",
		"line 6: ", "line 7: ", "line 8: ", "line 9: ", "line 10: "
	};
	app_util::page(sample_content, content_length, lines_per_page);

	cout << white;
	system("PAUSE");
	return 0;
}

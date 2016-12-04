// WindowsMain.cpp
// TaskApp
// CIS 22C F2016: Adrian Marroquin, Matthew Tso
//
// WindowsMain is the entry point into Tasks's 
// interactive shell on Windows platforms.
//
//
// Notes:
// http://www.geeksforgeeks.org/print-bst-keys-in-the-given-range/


// Temporary test includes
#include <fstream>

// Includes all usable Task headers.
#include "TaskLib.h"
#include "Operation.h"
#include "ADT\Stack.h"
#include "TaskEntry.h"
#include "Utilities\DateTime.h"
#include "HashTable.h"
#include "EntryManager.h"
#include "WindowsDirectory.h"
#include "c_tree.h"

// Includes all TaskApp utility headers
#include "AppIncludes.h"
#include "CommandParser.h"

using namespace std;

void visit(const task::Operation& item) {
	
	switch (item.getType()) {
	case task::UPDATE_STATUS:
		cout << "update ";
		break;
	default:
		cout << "someOp ";
		break;
	}
	cout << item.getPreviousState().getId() << endl;
}

void visitTable(task::TaskEntry& entry) {

	cout << entry.getDescription() << endl;
}

int main(int argc, char* argv[])
{
	// Output version number specified in AppConstants.h
	cout << "task v" << taskapp::VERSION << endl;

	// Initialize Task's manager object.
	task::EntryManager manager;
	manager.setCurrentUser("mtso");


	// If DEBUG is defined, skip main routine to print debugging info.
#ifndef DEBUG

	// Load tasklogs
	vector<string> filenames = taskapp::filenamesIn(_TEXT("..\\.task"));
	vector<string> tasklog_filenames;
	for (unsigned int i = 0; i < filenames.size(); i++) 
	{
		// Iterate through all filenames looking for those that contain `tasklog-`
		if (filenames[i].find("tasklog-") != string::npos) 
		{
			tasklog_filenames.push_back(filenames[i]);
		}
	}
	manager.loadTasklogs(tasklog_filenames);

	//====================================================================
	// Main event loop
	//====================================================================
	
	// Event loop variables
	string input;
	taskapp::AppCommand command;
	string arguments;
	bool shouldContinue = true;
	taskapp::CommandParser parser;

	// Main event loop
	while (shouldContinue) {
		cout << "> ";
		getline(cin, input);

		command = parser.parseCommandFrom(input);
		arguments = parser.parseArgumentsFrom(input);

		string full_id;
		int run_count;

		//cout << "Command: ";
		switch (command) {
		case taskapp::CMD_LIST:
			manager.printAllTo(cout);
			break;

		case taskapp::CMD_CREATE:
			manager.createEntry(arguments);
			cout << "Created a new entry." << endl;
			break;

		case taskapp::CMD_UPDATE:
			cout << "update";
			// TODO: need to write update command
			break;

		case taskapp::CMD_DELETE:
			if (manager.getFullIdFor(arguments, full_id)) {
				
				if (manager.deleteEntry(full_id)) {
					cout << "Deleted " << full_id << endl;
				}
				else {
					cout << "Error deleting: " << full_id << endl;
				}
			}
			else {
				cout << "Could not find (or found more than) one entry that matched: " << arguments << endl;
			}
			break;

		case taskapp::CMD_HISTORY:
			manager.printHistoryTo(cout);
			break;

		case taskapp::CMD_UNDO:
			cout << "undo";
			// TODO: need to implement undo
			break;

		case taskapp::CMD_TEST:
			if (arguments.length() > 0) {
				try {
					run_count = stoi(arguments);
					manager.runDiagnosticTo(cout, run_count);
				}
				catch (std::invalid_argument error) {
					cout << "test takes a number as an argument" << endl;
				}
			}
			else {
				manager.runDiagnosticTo(cout);
			}
			break;

		case taskapp::CMD_QUIT:
			// Output files here

			shouldContinue = false;
			break;

		case taskapp::CMD_HELP:
			cout << "help" << endl;
			break;

		default:
			cout << "unrecognized command. see `help`." << endl;
			break;
		}
	}

#else

#endif
	return 0;
}

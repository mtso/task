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
#include "Utilities\StringToEnum.h"

// Includes all TaskApp utility headers
#include "AppIncludes.h"
#include "CommandParser.h"

using namespace std;

string getUsername();
void loadDataInto(task::EntryManager& manager);

int main(int argc, char* argv[])
{
	//====================================================================
	// Startup procedure
	//====================================================================

	// Output version number specified in AppConstants.h
	cout << "task v" << taskapp::VERSION << endl;

	// Initialize Task's manager object using current username.
	task::EntryManager manager(getUsername());

	loadDataInto(manager);

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

		// Container variables to use inside the switch
		string full_id;
		string raw_id;
		string raw_status;
		TaskEntryStatus new_status; // for status update
		int run_count; // for test
		vector<task::TaskEntry> search_results; // for search
		task::TaskEntry result; // for search

		switch (command) {
		case taskapp::CMD_LIST:
			manager.printAllTo(cout);
			break;

		case taskapp::CMD_CREATE:
			manager.createEntry(arguments);
			cout << "Created a new entry." << endl;
			break;

		case taskapp::CMD_UPDATE:
			raw_id = arguments.substr(0, parser.firstOccurenceOf(' ', arguments));
			raw_status = parser.parseArgumentsFrom(arguments);

			// Get status type
			try {
				new_status = task::StringToEnum::forStatus(raw_status);
			}
			catch (...) {
				cout << "could not parse status from: `" << raw_status << "`" << endl;
				break;
			}

			// If the full id is found, 
			// update the entry to the new status
			if (manager.getFullIdFor(raw_id, full_id)) {
				manager.updateEntryStatus(full_id, new_status);
				cout << "updated " << full_id.substr(0, 8) << " ->" << task::EnumToString::forStatus(new_status) << endl;
			}
			else {
				cout << "could not find (or found more than) one entry that matched: " << raw_id << endl;
			}
			break;

		case taskapp::CMD_DELETE:
			if (manager.getFullIdFor(arguments, full_id)) 
			{	
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
			manager.undoTopOperation(cout);
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

		case taskapp::CMD_SEARCH:
			search_results = manager.searchEntryDescription(arguments);
			for (uint i = 0; i < search_results.size(); i++) 
			{
				result = search_results[i];
				cout << result.getId().substr(0, 8) << " " << result.getDescription() << endl;
			}
			break;

		default:
			cout << "unrecognized command. see `help`." << endl;
			break;
		}
	}

	return 0;
}

string getUsername()
{
	// Get the username from .gitconfig
	string current_user;
	if (taskapp::getCurrentUser(current_user)) {
		cout << current_user << endl;
	}
	else {
		cout << "What is your username?\n>" << endl;
		getline(cin, current_user);
	}
	return current_user;
}

void loadDataInto(task::EntryManager& manager)
{
	// Get all the filenames inside the .task directory
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
	// Load tasklogs
	manager.loadTasklogs(tasklog_filenames);
}

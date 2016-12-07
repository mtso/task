// WindowsMain.cpp
// TaskApp
// CIS 22C F2016: Adrian Marroquin, Matthew Tso, Jinzhu Shen
//
// WindowsMain is the entry point into Tasks's 
// interactive shell on Windows platforms.
//

// Includes usable Task headers.
#include "TaskLib.h"

// Includes all TaskApp utility headers
#include "AppConfiguration.h"
#include "CommandParser.h"
#include "WindowsDirectory.h"

// Flag for continuing input loop
#define CONTINUE_APP 1

string getUsername();
void loadDataInto(task::EntryManager& manager, const TCHAR* from_directory);
int commandInput(task::EntryManager& manager);

//===============================
// EntryManager helper functions
//===============================
void parseAndExecuteList  (task::EntryManager& manager, const string& arguments);
void parseAndExecuteUpdate(task::EntryManager& manager, const string& arguments);
void parseAndExecuteTest  (task::EntryManager& manager, const string& arguments);
void parseAndExecuteDelete(task::EntryManager& manager, const string& arguments);
void parseAndExecuteSearch(task::EntryManager& manager, const string& arguments);

int main(int argc, char* argv[])
{
	// Output version number specified in AppConstants.h
	cout << "task v" << task::VERSION << endl;
	
	// Parse startup arguments
	string root_directory;
	TCHAR* root_directory_t;
	if (argc > 1 && (string)argv[1] == "--top-root") {
		root_directory = task::DEFAULT_TOP_DATA_DIR;
		root_directory_t = _TEXT(".task\\");
	}
	else {
		root_directory = task::DEFAULT_DATA_DIR;
		root_directory_t = _TEXT("..\\.task\\");
	}

	// Startup procedure
	// Initialize Task's manager object using current username.
	task::EntryManager manager(getUsername(), root_directory);

	// Load data from tasklogs using Windows API functions
	loadDataInto(manager, root_directory_t);

	// Enter main command loop
	int status = CONTINUE_APP;
	while (status == CONTINUE_APP)
	{
		status = commandInput(manager);
	}

	// Should only be EXIT_SUCCESS at this point
	return status;
}

string getUsername()
{
	// Get the username from .gitconfig
	string current_user;
	if (!taskapp::getCurrentUser(current_user)) 
	{
		// Let the user manually enter their name
		// if .gitconfig could not be found
		cout << "could not locate .gitconfig, what is your username?\n> ";
		getline(cin, current_user);
	}
	return current_user;
}

void loadDataInto(task::EntryManager& manager, const TCHAR* from_directory)
{
	// Get all the filenames inside the .task directory
	vector<string> filenames = taskapp::filenamesIn(from_directory);
	vector<string> tasklog_filenames;
	for (unsigned int i = 0; i < filenames.size(); i++)
	{
		// Iterate through all filenames looking for those that contain `tasklog-`
		if (filenames
			[i].find("tasklog-") != string::npos)
		{
			tasklog_filenames.push_back(filenames[i]);
		}
	}
	// Load tasklogs
	manager.loadTasklogs(tasklog_filenames);
}

//====================================================================
// Command input process
//====================================================================
int commandInput(task::EntryManager& manager)
{
	// Prompt command and get input
	string input;
	cout << "> ";
	getline(cin, input);

	// Parse command
	taskapp::CommandParser parser;
	taskapp::AppCommand command = parser.parseCommandFrom(input);
	string arguments = parser.parseArgumentsFrom(input);

	switch (command) {
	case taskapp::CMD_LIST:
		parseAndExecuteList(manager, arguments);
		break;

	case taskapp::CMD_CREATE:
		manager.createEntry(arguments);
		cout << "Created a new entry." << endl;
		break;

	case taskapp::CMD_UPDATE:
		parseAndExecuteUpdate(manager, arguments);
		break;

	case taskapp::CMD_DELETE:
		parseAndExecuteDelete(manager, arguments);
		break;

	case taskapp::CMD_HISTORY:
		manager.printHistoryTo(cout);
		break;

	case taskapp::CMD_UNDO:
		manager.undoTopOperation(cout);
		break;

	case taskapp::CMD_TEST:
		parseAndExecuteTest(manager, arguments);
		break;

	case taskapp::CMD_HELP:
		cout << "help" << endl;
		break;

	case taskapp::CMD_SEARCH:
		parseAndExecuteDelete(manager, arguments);
		break;

	case taskapp::CMD_QUIT:
		manager.unload(); // Output files here
		return EXIT_SUCCESS;

	default:
		cout << "unrecognized command. see `help`." << endl;
		break;
	}
	
	return CONTINUE_APP;
}

void parseAndExecuteList(task::EntryManager& manager, const string& arguments)
{
	if (arguments == "") {
		manager.printUserTasksTo(cout);
	}
	else {
		if (arguments == "all") {
			manager.printUserTasksAllTo(cout);
		}
		else if (arguments == "team") {
			manager.printAllTo(cout);
		}
	}
}

void parseAndExecuteUpdate(task::EntryManager& manager, const string& arguments)
{
	// given a full command of `update bae4 due 12-24-2016`
	// command: update
	// raw_id: bae4
	// raw_update_type: due
	// raw_update_argument: 12-24-2016

	taskapp::CommandParser parser;
	string full_id;
	string raw_id = arguments.substr(0, parser.firstOccurenceOf(' ', arguments));
	string leftovers = parser.parseArgumentsFrom(arguments);

	string raw_update_type = leftovers.substr(0, parser.firstOccurenceOf(' ', leftovers));
	string raw_update_argument = parser.parseArgumentsFrom(leftovers);

	//===============
	// Update Status
	//===============
	if (raw_update_type == "status") {

		TaskEntryStatus new_status;

		// Get status type
		try {
			new_status = task::StringToEnum::forStatus(raw_update_argument);
		}
		catch (...) {
			cout << "could not parse status from: `" << raw_update_argument << "`" << endl;
			return;
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
	}

	//=================
	// Update Due Date
	//=================
	else if (raw_update_type == "due") {
		uint64_t input_date;
		try {
			input_date = task::rawDateToMs(raw_update_argument);
		}
		catch (...) {
			cout << "Due date should be formatted like: mm-dd-yyyy." << endl;
			return;
		}

		uint64_t date = task::rawDateToMs(raw_update_argument);
		
		if (manager.getFullIdFor(raw_id, full_id)) {
			manager.updateEntryDueDate(full_id, input_date);
			cout << "updated " << full_id.substr(0, 8) << " ->" << task::msToString(date).substr(0, 10) << endl;
		}
		else {
			cout << "could not find (or found more than) one entry that matched: " << raw_id << endl;
		}
	}

	//====================
	// Update Description
	//====================
	else if (raw_update_type == "description") {
		cout << "Description update has not been implemented yet." << endl;
		if (manager.getFullIdFor(raw_id, full_id)) {
			manager.updateEntryDescription(full_id, raw_update_argument);
			cout << "updated " << full_id.substr(0, 8) << " ->\"" << raw_update_argument << "\"" << endl;
		}
		else {
			cout << "could not find (or found more than) one entry that matched: " << raw_id << endl;
		}
	}

}

void parseAndExecuteTest(task::EntryManager& manager, const string& arguments)
{
	taskapp::CommandParser parser;
	if (arguments == "state") {
		manager.printCurrentStateTo(cout);
	}
	else if (arguments == "wipeout") {
		manager.clear();
	}
	else if (arguments.substr(0, parser.firstOccurenceOf(' ', arguments)) == "fill") {

		string count_argument = parser.parseArgumentsFrom(arguments);

		if (count_argument.length() > 0) {
			try {
				manager.fill(stoi(count_argument));
			}
			catch (std::invalid_argument error) {
				cout << "test fill takes a number as an argument" << endl;
			}
		}
		else {
			manager.fill(10);
		}
	}
	else if (arguments.length() > 0) {
		try {
			int run_count = stoi(arguments);
			manager.runDiagnosticTo(cout, run_count);
		}
		catch (std::invalid_argument error) {
			cout << "test takes a number as an argument" << endl;
		}
	}
	else {
		manager.runDiagnosticTo(cout); // default 1000 times
	}
}

void parseAndExecuteDelete(task::EntryManager& manager, const string& arguments)
{
	string full_id;
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
}

void parseAndExecuteSearch(task::EntryManager& manager, const string& arguments)
{
	task::TaskEntry result;
	vector<task::TaskEntry> search_results = manager.searchEntryDescription(arguments);
	for (uint i = 0; i < search_results.size(); i++)
	{
		result = search_results[i];
		cout << yellow << result.getId().substr(0, 8) << white << " " << result.getDescription() << endl;
	}
}
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

	ifstream config;
	config.open("~\\.gitconfig");
	string c_line;
	while (getline(config, c_line)) {
		cout << c_line << endl;
	}
	system("pause");



	//task::HashTable<string, task::TaskEntry*> table; // = task::HashTable<string, task::TaskEntry*>();
	//c_tree<uint64_t, task::TaskEntry*> tree;
	//task::TaskEntry** found_entries = nullptr;
	//uint64_t* found_keys = nullptr;
	//task::TaskEntry* demo_entry = new task::TaskEntry("demo", "demo entry");
	//tree.insert(demo_entry->getTimeCreatedMs(), &demo_entry);
	//table.insert(demo_entry->getId(), demo_entry);
	//if (tree.find(demo_entry->getTimeCreatedMs(), &found_keys, &found_entries))
	//{
	//	cout << (*found_entries)->getDescription() << endl;
	//}
	//cout << table.getValue(demo_entry->getId())->getDescription() << endl;

	task::EntryManager manager;
	

	//uint m = 0;
	//cout << m << endl;

	// If DEBUG is defined, skip main routine to print debugging info.
#ifndef DEBUG

	// Load tasklogs
	vector<string> filenames = taskapp::filenamesIn(_TEXT("..\\.task"));
	vector<string> tasklog_filenames;

	for (unsigned int i = 0; i < filenames.size(); i++) {
		if (filenames[i].find("tasklog-") != string::npos) {
			//cout << filenames[i] << endl;
			tasklog_filenames.push_back(filenames[i]);
		}
	}
	manager.loadTasklogs(tasklog_filenames);
	manager.printAllTo(cout);
	manager.createEntry("what in the worlds");
	cout << endl << endl << "===================" << endl << endl;
	manager.printAllTo(cout);


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

		cout << "Command: ";
		switch (command) {
		case taskapp::CMD_LIST:
			cout << "list";
			break;
		case taskapp::CMD_CREATE:
			cout << "create";
			break;
		case taskapp::CMD_UPDATE:
			cout << "update";
			break;
		case taskapp::CMD_DELETE:
			cout << "delete";
			break;
		case taskapp::CMD_HISTORY:
			cout << "history";
			break;
		case taskapp::CMD_UNDO:
			cout << "undo";
			break;
		case taskapp::CMD_TEST:
			cout << "test";
			break;
		case taskapp::CMD_QUIT:
			cout << "quit";
			shouldContinue = false;
			break;
		case taskapp::CMD_HELP:
			cout << "help";
			break;
		default:
			cout << "unrecognized command";
			break;
		}
		cout << ". Arguments: " << arguments << "." << endl;
	}

#else
	adt::Stack<task::Operation> history;
	
	
	task::TaskEntry entry_1 = task::TaskEntry("mryagni", "waddup waddup");
	entry_1.setTimeDueMs(entry_1.getTimeCreatedMs() + task::weekToMs(1));

	history.push(task::Operation(task::UPDATE_STATUS, entry_1));
	entry_1.setStatus(IN_PROGRESS);

	history.traverse(visit);



	task::HashTable<string, task::TaskEntry> entries;
	entries.insert(entry_1.getId(), entry_1);

	entries.traverse(visitTable);





	//// DEMO CODE
	//// Diagnostic usage
	//task::Diagnostic diagnostic;
	//diagnostic.runAndPrintTo(10, std::cout);
	//cout << endl;


	//// DEMO CODE
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
	entry_buffer << new_entry.getId() << ","
		<< new_entry.getTimeCreatedMs() << ","
		<< new_entry.getTimeDueMs() << ","
		<< "\"" << new_entry.getDescription() << "\"," 
		<< entry_status << "\n";

	ofstream mryagni_log;
	string data_rootdir = "..\\.task\\tasklog-";

	// Print the entry to mryagni's tasklog
	mryagni_log.open(data_rootdir + new_entry.getCreator(), ios::app);
	mryagni_log << yellow << entry_buffer.str();
	mryagni_log.close();


	//// DEMO CODE
	//// WindowsDirectory filename search usage
	//TCHAR* data_dir = TEXT("..\\.task");
	////string data_dir = "..\\";

	////cout << data_dir;

	try {
		vector<wstring> files;

		if (taskapp::ListFiles(L"..\\.task", L"tasklog-*", files)) {
			for (vector<wstring>::iterator it = files.begin();
				it != files.end();
				++it) {
				wcout << it->c_str() << endl;
			}
		}
	}
	catch (const char* error) {
		cout << error << endl;
	}
	catch (...) {
		cout << "Could not catch error";
	}
	cout << endl;
	//
	// 
	//// DEMO CODE
	//// Pager.h usage
	//// Outputs an array of string content at a managed pace.
	//const int content_length = 10;
	//const int lines_per_page = 7;
	//cout << green;
	//const string sample_content[content_length] = {
	//	"line 1: ", "line 2: ", "line 3: ", "line 4: ", "line 5: ",
	//	"line 6: ", "line 7: ", "line 8: ", "line 9: ", "line 10: "
	//};
	//app_util::page(sample_content, content_length, lines_per_page);

	cout << white;
	system("PAUSE");

#endif
	return 0;
}

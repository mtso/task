// EntryManager.h
// Task
// CIS 22C F2016: Matthew Tso, Xin He, Jinzhu Shen

#ifndef TASK_ENTRYMANAGER_H
#define TASK_ENTRYMANAGER_H

#include <vector>
#include "HashTable.h"
#include "c_tree.h"
#include "TaskEntry.h"
#include "Operation.h"
#include "ADT\Stack.h"
#include "FileStore.h"
#include "Utilities\DateTime.h"
#include "Utilities\EnumToString.h"
#include "Utilities\Diagnostic.h"
#include "Configuration.h"

//#include "Utilities\ConsoleColor.h"

#ifdef _WIN32
#include "windows.h"
#endif

namespace task 
{
	class EntryManager 
	{
	private:
		// Used to differentiate tasklog file for input/output
		string current_user;

		// Used to determine where the .task folder is located (top-level or ..\\ one level over)
		string root_directory;

		// The HashTable
		HashTable<string, TaskEntry> table;

		// The BST sorted by creation time 64bit int
		c_tree<uint64_t, TaskEntry> tree_time_created;

		// Stores user operations of each session in Last In First Out fashion
		adt::Stack<Operation> history;

		// Outputs the operation history by traversing the stack
		friend void printHistory(const Operation& operation);

		// Outputs the table order by traversing the HashTable
		friend void printTable(TaskEntry& entry);

		// Outputs the entries in hash table order to a file named "hashtable_output.txt"
		friend void saveHashTable(TaskEntry& entry);

		// Inserts a TaskEntry object into the table and tree
		void insertEntry(const TaskEntry& entry);

		// Prints an entry's unique id, creator's username, due date time, and description to an output stream
		void printEntryTo(ostream& output, const TaskEntry* entry);

		// Used to throw exceptions if the search terms come up empty
		class NotFoundException {
		private:
			string description;
		public:
			NotFoundException(const string& other_description = "EntryManager could not match the search arguments with an entry.")
				: description(other_description) {}
		};

	public:
		// Default constructor, no longer used
		EntryManager();

		// Constructor accepting username and root directory argument
		EntryManager(const string& user, const string& directory);

		// Sets the username
		void setCurrentUser(const string& user);

		void setRootDirectory(const string& directory);

		//===============================
		// Task output listing functions
		////===============================

		// Prints all entries from all users
		void printAllTo(ostream& output);

		// Prints just the user's backlog and in-progress tasks to output
		// by tree order
		void printUserTasksTo(ostream& output);
		
		// Prints all of the user's tasks by tree order
		void printUserTasksAllTo(ostream& output);

		// Outputs by HashTable order
		void printTableTo(ostream& output);

		// Outputs an indented tree representation of the BST
		void printTreeTo(ostream& output);
		
		// Prints a list of the operation history to cout.
		void printHistoryTo(ostream& output);

		// Creates a new entry from the description
		// with a default of backlog status and no due date time
		// and then calls insertEntry to add to table and tree
		void createEntry(const string& description);

		// Searches the description of all entries with a search term
		// by traversing the BST
		vector<TaskEntry> searchEntryDescription(const string& search_term);

		// Returns an entry by full id
		TaskEntry getEntryById(const string& id);

		// Attempts to match a fragment of an id to a full id
		// Will return false if no entries are found
		// OR more than one entry is matched
		bool getFullIdFor(const string& id, string& found_id);

		// Deletes and entry by id from table and tree
		bool deleteEntry(const string& id);

		// Updates an entry's status, records the operation to the history
		bool updateEntryStatus(const string& id, const TaskEntryStatus& new_status);

		// Updates an entry's description, records the operation to the history
		bool updateEntryDescription(const string& id, const string& new_description);
        
		// Updates an entry's due date, records the operation to the history
		bool updateEntryDueDate(const string& id, uint64_t new_time_due);

		// Runs the diagnostic of table and tree and prints it to an output stream
		void runDiagnosticTo(ostream& output, const int& run_count = 1000);

		// Prints the current stats of the hash table
		void printCurrentStateTo(ostream& output);

		// outputs the user's tasks to his/her tasklog file
		// Deletion of other user's entries does not get saved to their tasklogs
		// outputs a hashtable_output.txt file of the HashTable order
		void unload();

		// Pops the top operation from the history stack
		// and reverts the TaskEntry to its previous state
		void undoTopOperation(ostream& output);

		// Loads entries from a vector of filenames on startup
		void loadTasklogs(vector<string> filenames);

		// !DANGER!
		// Deletes all entries
		void clear();

		// Adds dummy entries into the table and tree for demo
		void fill(const int& count);
	};
}

#endif

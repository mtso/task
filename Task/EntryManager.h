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

#include "Utilities\ConsoleColor.h"

#ifdef _WIN32
#include "windows.h"
#endif

namespace task 
{
	class EntryManager 
	{
	private:
		string current_user;

		string root_directory;

		HashTable<string, TaskEntry> table;

		c_tree<uint64_t, TaskEntry> tree_time_created;

		adt::Stack<Operation> history;

		friend void printHistory(const Operation& operation);

		friend void printTable(TaskEntry& entry);

		class NotFoundException {
		private:
			string description;
		public:
			NotFoundException( const string& other_description = "EntryManager could not match the search arguments with an entry." )
				: description(other_description) {}
		};

		//
		void insertEntry(const TaskEntry& entry);

		void printEntryTo(ostream& output, const TaskEntry* entry);

	public:
		EntryManager();

		EntryManager(const string& user, const string& directory);

		void setCurrentUser(const string& user);

		void setRootDirectory(const string& directory);

		// Task output listing functions

		void printAllTo(ostream& output);

		void printUserTasksTo(ostream& output);

		void printUserTasksAllTo(ostream& output);

		void printTableTo(ostream& output);
		
		/**
		 * Prints a list of the operation history to cout.
		 */
		void printHistoryTo(ostream& output);

		void createEntry(const string& description);

		vector<TaskEntry> searchEntryDescription(const string& search_term);

		TaskEntry getEntryById(const string& id);

		bool getFullIdFor(const string& id, string& found_id);

		bool deleteEntry(const string& id);

		bool updateEntryStatus(const string& id, const TaskEntryStatus& new_status);

		bool updateEntryDescription(const string& id, const string& new_description);
        
		bool updateEntryDueDate(const string& id, uint64_t new_time_due);

		//bool updateEntryDueAdd(const string& id, const string& add_time);

		void runDiagnosticTo(ostream& output, const int& run_count = 1000);

		void printCurrentStateTo(ostream& output);

		// used upon quitting the app
		void unload();

		void undoTopOperation(ostream& output);

		void loadTasklogs(vector<string> filenames);

		// !DANGER!
		void clear();

		void fill(const int& count);
	};
}

#endif

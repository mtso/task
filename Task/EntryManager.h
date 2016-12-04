// EntryManager.h
// Task
// CIS 22C F2016: Matthew Tso

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


#include "windows.h"

namespace task {

	class EntryManager {

	private:
		string current_user;

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

	public:
		EntryManager();

		EntryManager(const string& user);

		void setCurrentUser(const string& user);

		void printAllTo(ostream& output);

		void printTableTo(ostream& output);
		
		void printHistoryTo(ostream& output);

		void createEntry(const string& description);

		vector<TaskEntry> searchEntryDescription(const string& search_term);

		TaskEntry getEntryById(const string& id);

		bool getFullIdFor(const string& id, string& found_id);

		bool deleteEntry(const string& id);

		bool updateEntryStatus(const string& id, const TaskEntryStatus& new_status);

		//void updateEntryDescription(const string& id, const string& new_description);

		//void updateEntryDue(const string& id, const string& new_time);

		void runDiagnosticTo(ostream& output, const int& run_count = 1000);

		//// used upon quitting the app
		//void unload();

		void undoTopOperation(ostream& output);

		void loadTasklogs(vector<string> filenames);
	};
}

#endif
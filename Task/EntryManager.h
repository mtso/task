// EntryManager.h
// Task
// CIS 22C F2016: Matthew Tso

#ifndef TASK_ENTRYMANAGER_H
#define TASK_ENTRYMANAGER_H

#include <vector>
#include "HashTable.h"
#include "c_tree.h"
#include "TaskEntry.h"
#include "OperationManager.h"
#include "FileStore.h"
#include "Utilities\DateTime.h"

#include "windows.h"

namespace task {

	class EntryManager {

	private:
		string current_user;

		HashTable<string, TaskEntry> table;

		c_tree<uint64_t, TaskEntry> tree_time_created;

		adt::Stack<Operation> history;

		friend void visitHistory(const Operation& operation);

		class NotFoundException {
		private:
			string description;
		public:
			NotFoundException( const string& other_description = "EntryManager could not match the search arguments with an entry." )
				: description(other_description) {}
		};

	public:
		EntryManager();
		EntryManager(const string& user);

		void setCurrentUser(const string& user);

		void printAllTo(ostream& output);
		
		void printHistoryTo(ostream& output);

		void createEntry(const string& description);

		vector<TaskEntry> searchEntryDescription(const string& search_term);

		TaskEntry getEntryById(const string& id);

		void deleteEntry(const string& id);

		//void updateEntryStatus(const string& id, const TaskEntryStatus& new_status);

		//void updateEntryDescription(const string& id, const string& new_description);

		//void updateEntryDue(const string& id, const string& new_time);

		//void runDiagnosticTo(ostream& output);

		//void loadEntry(
		//	const string& user,
		//	const string& id,
		//	const uint64_t& time_created,
		//	const uint64_t& time_due,
		//	const string& description,
		//	const TaskEntryStatus& status
		//	);

		//// used upon quitting the app
		//void unload();

		void loadTasklogs(vector<string> filenames);
	};
}

#endif
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

namespace task {

	class EntryManager {

	private:

		HashTable<string, TaskEntry*> table;

		c_tree<uint64_t, TaskEntry*> tree_time_created;

		//OperationManager operationManager;

		adt::Stack<Operation> history;

	public:
		EntryManager();



		void printAllTo(ostream& output);

		void createEntry(const string& description, int & dueIn);

		TaskEntry searchEntry(const string& description);

		void deleteEntry(const string& id);

		void updateEntryStatus(const string& id, const TaskEntryStatus& new_status);

		void updateEntryDescription(const string& id, const string& new_description);

		void updateEntryDue(const string& id, const string& new_time);

		void runDiagnosticTo(ostream& output);

		void loadEntry(
			const string& user,
			const string& id,
			const uint64_t& time_created,
			const uint64_t& time_due,
			const string& description,
			const TaskEntryStatus& status
			);

		// used upon quitting the app
		void unload();

		void loadTasklogs(vector<string> filenames);
	};
}

#endif
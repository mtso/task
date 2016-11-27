// EntryManager.h
// Task
// CIS 22C F2016: Matthew Tso

#ifndef TASK_ENTRYMANAGER_H
#define TASK_ENTRYMANAGER_H

#ifndef TASK_HASHTABLE_H
#include "HashTable.h"
#endif

#include "c_tree.h"
#include "TaskEntry.h"
#include "OperationManager.h"

namespace task {

	class EntryManager {

	private:

		HashTable<string, TaskEntry*> table;

		c_tree<uint64_t, TaskEntry*> tree;

		OperationManager operationManager;

	public:
		void printAllTo(ostream& output);

		void createEntry(const string& description);

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
	};
}

#endif
#include "TaskInferface.h"

namespace interface
{
	/*EntryManager
		--
		- table: HashTable<string, TaskEntry*>
		-tree : HashTable<unsigned long long, TaskEntry*>
		-history : OperationManager
		--
		+ void printAllTo(ostream& output);
	+void createEntry(const string& description);
	+void deleteEntry(const string& id);
	+void updateEntryStatus(const string& id, const TaskEntryStatus& new_status);
	+void updateEntryDescription(const string& id, const string& new_description);
	+void updateEntryDue(const string& id, const string& new_time);
	+void runDiagnosticTo(ostream& output);
	+void loadEntry(
		const string& user,
		const string& id,
		const uint64_t& time_created,
		const uint64_t& time_due,
		const string& description,
		const TaskEntryStatus& status
		);
	+void unload();*/

	void TaskRunner(task::TaskEntry entry, std::string command, std::string argument)
	{
		if (command == "create") {}
		if (command == "delete") {}
		if (command == "update_status") {}
		if (command == "update_desc") {}
		if (command == "update_due") {}
		if (command == "test") {}
		if (command == "load") {}
	}
}
// EntryManager.cpp
// Task
// CIS 22C F2016: Matthew Tso, Xin He

#include "EntryManager.h"

using namespace task;

EntryManager::EntryManager()
	: table(HashTable<string, TaskEntry>())
	, tree_time_created(c_tree<uint64_t, TaskEntry>())
	, history (adt::Stack<Operation>())
{
}

void EntryManager::loadTasklogs(vector<string> filenames)
{
	FileStore fileio;
	string filepath;
	vector<TaskEntry> entries;
	TaskEntry* entry;

	// Iterate through filenames
	for (uint i = 0; i < filenames.size(); i++) 
	{
		filepath = "..\\.task\\" + filenames[i];

		// Return if the filepath was invalid
		if (!fileio.load(filepath, entries)) { continue; }
			
		// Iterate through the entries loaded from fileio
		for (uint count = 0; count < entries.size(); count++) 
		{
			entry = new task::TaskEntry(entries[count]);

			table.insert(entry->getId(), *entry);
			tree_time_created.insert(entry->getTimeCreatedMs(), entry);
		}
	}
}

void EntryManager::printAllTo(ostream& output)
{
	TaskEntry* value;
	for (uint64_t* key = tree_time_created.first_data(&value); key != NULL; key = tree_time_created.next_data(&value))
	{
		output << "task " << value->getId() << endl;
		output << "Due: " << value->getTimeDueStr() << endl << endl;
		output << "\t" << value->getDescription() << endl << endl;
	}
}

void task::visitHistory(const Operation& operation)
{
	cout << operation.getType() << "\t" << operation.getPreviousState().getDescription() << endl;
}

void EntryManager::printHistoryTo(ostream& output)
{
	history.traverse(visitHistory);
}

void EntryManager::createEntry(const string& description)
{
	//assign system time to create time
	ULARGE_INTEGER int_time;
	SYSTEMTIME sys_time;
	GetSystemTime(&sys_time);
	FILETIME file_time;
	SystemTimeToFileTime(&sys_time, &file_time);
	int_time.LowPart = file_time.dwLowDateTime;
	int_time.HighPart = file_time.dwHighDateTime;
	uint64_t createTime = (uint64_t)int_time.QuadPart;

	//TaskEntry value("", description, createTime);
	TaskEntryStatus new_status = BACKLOG;
	TaskEntry* new_entry = new TaskEntry("mtso", description, createTime, createTime, new_status);

	//tree_time_created.insert(createTime, &value);
	history.push(Operation(CREATE, *new_entry));
	tree_time_created.insert(createTime, new_entry);
	table.insert(new_entry->getId(), *new_entry);
}

vector<TaskEntry> EntryManager::searchEntry(const string& search_term)
{
	vector<TaskEntry> found;
	TaskEntry* value;
	for (uint64_t* key = tree_time_created.first_data(&value); key != NULL; key = tree_time_created.next_data(&value))
	{
		if (value->getDescription().find(search_term) != string::npos)
		{
			found.push_back(*value);
		}
	}
	return found;
}

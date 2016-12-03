// EntryManager.cpp
// Task
// CIS 22C F2016: Matthew Tso, Xin He

#include "EntryManager.h"

namespace task {

	EntryManager::EntryManager()
	{
		table = HashTable<string, TaskEntry*>();
		tree_time_created = c_tree<uint64_t, TaskEntry*>();
		history = adt::Stack<Operation>();
	}

	void EntryManager::loadTasklogs(vector<string> filenames)
	{
		FileStore fileio;
		string filepath;
		vector<TaskEntry> entries;
		TaskEntry* entry;

		// Iterate through filenames
		for (uint i = 0; i < filenames.size(); i++) {
			filepath = "..\\.task\\" + filenames[i];

			// Return if the filepath was invalid
			if (!fileio.load(filepath, entries)) { continue; }
			
			// Iterate through the entries loaded from fileio
			for (uint count = 0; count < entries.size(); count++) 
			{
				entry = new task::TaskEntry(entries[count]);

				table.insert(entry->getId(), entry);
				tree_time_created.insert(entry->getTimeCreatedMs(), &entry);
			}
		}
	}



}
// EntryManager.h
// Task
// CIS 22C F2016: Matthew Tso, Xin He

#include "EntryManager.h"

namespace task {

	EntryManager::EntryManager()
	{
		table = HashTable<string, TaskEntry*>();
		tree = c_tree<uint64_t, TaskEntry*>();
		history = adt::Stack<Operation>();
	}

	void EntryManager::loadTasklogs(vector<string> filenames)
	{
		FileStore fileio;
		string filepath;
		vector<TaskEntry> entries;
		TaskEntry* entry;

		for (int i = 0; i < filenames.size(); i++) {
			filepath = "..\\.task\\" + filenames[i];

			fileio.load(filepath, entries);
			for (int e = 0; e < entries.size(); e++) {

				entry = &entries[e];
				table.insert(entry->getId(), entry);
				//tree.insert(entry->getTimeCreatedMs(), entry);
			}
		}
	}
}
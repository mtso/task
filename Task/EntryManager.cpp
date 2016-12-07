// EntryManager.cpp
// Task
// CIS 22C F2016: Matthew Tso, Xin He, Jinzhu Shen

#include "EntryManager.h"

using namespace task;

EntryManager::EntryManager()
	: table(HashTable<string, TaskEntry>())
	, tree_time_created(c_tree<uint64_t, TaskEntry>())
	, history (adt::Stack<Operation>())
	, current_user("")
	, root_directory("")
{
}

EntryManager::EntryManager(const string& user, const string& directory)
	: table(HashTable<string, TaskEntry>())
	, tree_time_created(c_tree<uint64_t, TaskEntry>())
	, history(adt::Stack<Operation>())
	, current_user(user)
	, root_directory(directory)
{
}

void EntryManager::setCurrentUser(const string& user)
{
	current_user = user;
}

void EntryManager::setRootDirectory(const string& directory)
{
	root_directory = directory;
}

void EntryManager::insertEntry(const TaskEntry& new_entry)
{
	TaskEntry* entry = new task::TaskEntry(new_entry);
	table.insert(entry->getId(), *entry);
	tree_time_created.insert(entry->getTimeCreatedMs(), entry);
}

void EntryManager::loadTasklogs(vector<string> filenames)
{
	FileStore fileio;
	string filepath;
	vector<TaskEntry> entries;

	// Iterate through filenames
	for (uint i = 0; i < filenames.size(); i++) 
	{
		filepath = root_directory + filenames[i];

		// Return if the filepath was invalid
		if (!fileio.load(filepath, entries)) { continue; }
		
		// Iterate through the entries loaded from fileio
		for (uint count = 0; count < entries.size(); count++) 
		{
			insertEntry(entries[count]);
		}
	}
}

void EntryManager::printEntryTo(ostream& output, const TaskEntry* entry)
{
#ifdef _WIN32
	output << yellow;
#endif
	output << "task " << entry->getId() << endl;
#ifdef _WIN32
	output << white;
#endif
	output << "User:\t" << entry->getCreator() << endl;
	output << "Status:\t" << EnumToString::forStatus(entry->getStatus()) << endl;
	output << "Due:\t" << entry->getTimeDueStrShort() << endl << endl;
	output << "\t" << entry->getDescription() << endl << endl;
}

void EntryManager::printAllTo(ostream& output)
{
	TaskEntry* value;
	for (uint64_t* key = tree_time_created.first_data(&value); key != NULL; key = tree_time_created.next_data(&value))
	{
		printEntryTo(output, value);
	}
}


void EntryManager::printUserTasksTo(ostream& output)
{
	TaskEntry* value;
	for (uint64_t* key = tree_time_created.first_data(&value); key != NULL; key = tree_time_created.next_data(&value))
	{
		if (value->getCreator() == current_user && 
			value->getStatus() == BACKLOG || 
			value->getStatus() == IN_PROGRESS )
		{
			printEntryTo(output, value);
		}
	}
}

void EntryManager::printUserTasksAllTo(ostream& output)
{
	TaskEntry* value;
	for (uint64_t* key = tree_time_created.first_data(&value); key != NULL; key = tree_time_created.next_data(&value))
	{
		if (value->getCreator() == current_user)
		{
			printEntryTo(output, value);
		}
	}
}

void task::printTable(TaskEntry& entry)
{
	cout << "task " << entry.getId() << endl;
	cout << "User:\t" << entry.getCreator() << endl;
	cout << "Status:\t" << EnumToString::forStatus(entry.getStatus()) << endl;
	cout << "Due:\t" << entry.getTimeDueStr() << endl << endl;
	cout << "\t" << entry.getDescription() << endl << endl;
}
void EntryManager::printTableTo(ostream& output)
{
	table.traverse(printTable);
}

void task::printHistory(const Operation& operation)
{
	cout << EnumToString::forOperationType( operation.getType() ) << "\t" << operation.getPreviousState().getId().substr(0, 8) << " ";

	switch (operation.getType()) {
	case UPDATE_STATUS:
		cout << EnumToString::forStatus(operation.getPreviousState().getStatus()) << " -> ";
		break;

	default:
		break;
	}
	cout << endl;
}

void EntryManager::printHistoryTo(ostream& output)
{
	if (history.isEmpty()) {
		output << "no operations have been recorded this run." << endl;
	}
	else {
		history.traverse(printHistory);
	}
}

void EntryManager::createEntry(const string& description)
{
	//TaskEntry value("", description, createTime);
	TaskEntryStatus new_status = BACKLOG;
	TaskEntry* new_entry = new TaskEntry(current_user, description); // , createTime, createTime + 64000, new_status);

	//tree_time_created.insert(createTime, &value);
	history.push(Operation(OP_CREATE, *new_entry));
	tree_time_created.insert(new_entry->getTimeCreatedMs(), new_entry);
	table.insert(new_entry->getId(), *new_entry);
}

vector<TaskEntry> EntryManager::searchEntryDescription(const string& search_term)
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

TaskEntry EntryManager::getEntryById(const string& id)
{
	try {
		return table.getValue(id);
	}
	catch (HashList<string, TaskEntry>::NotFoundException error) {
		throw error;
	}
}

bool EntryManager::getFullIdFor(const string& id, string& found_id)
{
	adt::Stack<string> entries;
	TaskEntry* value;
	string full_id;
	for (uint64_t* key = tree_time_created.first_data(&value); key != NULL; key = tree_time_created.next_data(&value))
	{
		full_id = value->getId();

		if (full_id.find(id) == 0) // Match in first position
		{
			entries.push(full_id);
		}
	}
	
	// Only return true if one was found
	if (entries.getLength() == 1) {
		found_id = entries.pop();
		return true;
	}
	else { return false; }
}

bool EntryManager::deleteEntry(const string& id)
{
	TaskEntry to_delete;
	try{
		to_delete = table.getRawValue(id);
	}
	catch (HashList<string, TaskEntry>::NotFoundException error) {
		return false;
	}

	history.push(Operation(OP_DELETE, to_delete));
	tree_time_created.remove(to_delete.getTimeCreatedMs());
	table.remove(to_delete.getId());
	return true;
}

bool EntryManager::updateEntryStatus(const string& id, const TaskEntryStatus& new_status)
{
	TaskEntry* to_update;
	
	// Find entry
	try {
		to_update = & table.getRawValue(id);		
	}
	catch (HashList<string, TaskEntry>::NotFoundException error) { return false; }

	// Update entry in tree
	TaskEntry* found_value;
	uint64_t * found_key;
	if (tree_time_created.find(to_update->getTimeCreatedMs(), &found_key, &found_value)) {
		found_value->setStatus(new_status);
	}
	else { return false; }

	// Add to history after finding the entry in the table
	// and updating the clone in the tree.
	history.push(Operation(UPDATE_STATUS, *to_update));

	// Update entry in table
	to_update->setStatus(new_status);

	return true;
}

bool EntryManager::updateEntryDescription(const string& id, const string& new_description)
{
    TaskEntry* to_update;

    // Find entry
    try {
        to_update = & table.getRawValue(id);
    }
    catch (HashList<string, TaskEntry>::NotFoundException error) { return false; }

    // Update entry in tree
    TaskEntry* found_value;
    uint64_t * found_key;
    if (tree_time_created.find(to_update->getTimeCreatedMs(), &found_key, &found_value)) {
        found_value->setDescription(new_description);
    }
    else { return false; }

    // Add to history after finding the entry in the table
    // and updating the clone in the tree.
    history.push(Operation(UDPATE_DESCRIPTION, *to_update));

    // Update entry in table
    to_update->setDescription(new_description);

    return true;
}

bool EntryManager::updateEntryDueDate(const string& id, uint64_t new_time_due)
{
    TaskEntry* to_update;

    // Find entry
    try {
        to_update = &table.getRawValue(id);
    }
    catch (HashList<string, TaskEntry>::NotFoundException error) { return false; }

    // Update entry in tree
    TaskEntry* found_value;
    uint64_t * found_key;
    if (tree_time_created.find(to_update->getTimeCreatedMs(), &found_key, &found_value)) {
        found_value->setTimeDueMs(new_time_due);
    }
    else { return false; }

    // Add to history after finding the entry in the table
    // and updating the clone in the tree.
    history.push(Operation(UPDATE_TIMEDUE, *to_update));

    // Update entry in table
    to_update->setTimeDueMs(new_time_due);

    return true;
}

void EntryManager::undoTopOperation(ostream& output)
{
	if (history.isEmpty()) {
		output << "no operations to undo." << endl;
		return;
	}

	Operation top = history.pop();
	TaskEntry previous = top.getPreviousState();

	switch (top.getType())
	{
	case UPDATE_STATUS:
		updateEntryStatus(previous.getId(), previous.getStatus()); // Update to previous status
		history.pop(); // Pop the extra update operation
		output << "undid " << EnumToString::forOperationType( top.getType() ) << " " 
			<< previous.getId().substr(0, 8) << endl;
		break;

	case OP_CREATE:
		if (deleteEntry(previous.getId())) 
		{
			history.pop(); // Pop the extra update operation
			output << "undid " << EnumToString::forOperationType(top.getType()) << " "
				<< previous.getId().substr(0, 8) << endl;
		}
		else {
			output << "something bad happened (attempted to undo a new entry but could not find it)." << endl;
		}
		break;

	case OP_DELETE:
		insertEntry(previous);
		output << "undid " << EnumToString::forOperationType(top.getType()) << " "
			<< previous.getId().substr(0, 8) << endl;
		break;

	default:
		break;
	}
}

void EntryManager::unload()
{
	TaskEntry* value;
	vector<TaskEntry> entries;
	string filepath = root_directory + DEFAULT_TASKLOG_PREFIX + current_user;

	for (uint64_t* key = tree_time_created.first_data(&value); key != NULL; key = tree_time_created.next_data(&value))
	{
		if (value->getCreator() == current_user)
		{
			entries.push_back(*value);
		}
	}
	FileStore fileio;
	fileio.store(filepath, entries);
}


void EntryManager::runDiagnosticTo(ostream& output, const int& run_count)
{
	Diagnostic test;
	test.setTable(&table);
	test.setTree(&tree_time_created);
	test.runAndPrintTo(run_count, output);
	cout << "Average table accesses:\t" << test.getAverageTableAccesses() << endl;
}

void EntryManager::printCurrentStateTo(ostream& output)
{
	output << "Number of items:\t" << table.count() << endl;
	output << "HashTable load factor:\t" << table.getLoadFactor() << endl;
	output << "HashTable table size:\t" << table.getTableSize() << endl;
	output << "HashTable longest list:\t" << table.countLongestList() << endl;
}
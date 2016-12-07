// Diagnostic.cpp
// Task/Utilities
// CIS 22C F2016: Matthew Tso

#include "Diagnostic.h"

namespace task {

	Diagnostic::Diagnostic()
		: tree(nullptr)
		, table(nullptr)
	{
		start_time = end_time = delta_ms = 0;
		isRunning = false;
	}

	Diagnostic::Diagnostic(c_tree<uint64_t, TaskEntry>* tree_ptr, HashTable<string, TaskEntry>* table_ptr)
		: tree(tree_ptr)
		, table(table_ptr)
	{
		start_time = end_time = delta_ms = 0;
		isRunning = false;
	}

	void Diagnostic::run(const int& run_count)
	{
		ostringstream blackhole;
		runAndPrintTo(run_count, blackhole);
	}

	ostream& Diagnostic::runAndPrintTo(const int& run_count, ostream& output)
	{
		output << "Starting diagnostic routine, please wait..." << endl;
		if (table->isEmpty() && tree->is_empty()) {
			output << "HashTable and BinarySearchTree are empty" << endl;
			return output;
		}

		logStartTime();

		// Test table
		output << "Testing " << run_count << " HashTable accesses...";
		countTableAccess(run_count);
		output << " Passed." << endl;

		// Test tree
		output << "Testing " << run_count << " BinarySearchTree accesses...";
		countTreeAccess(run_count);
		output << " Passed." << endl;
        
		logEndTime();
		calculateDelta();
        
        // Display time result in ms. Print '<1' if duration is under 1 ms
		output << "Total execution time: ";
		(delta_ms < 1) ? (output << "<1") : (output << delta_ms);
		output << " ms" << endl;
        
		// Output data
		output << endl;
		output << "Number of entries:\t" << table->count() << endl;
		output << "Table size:\t\t" << table->getTableSize() << endl;
		output << "Longest list:\t\t" << table->countLongestList() << endl;
		output << "Table load factor:\t" << table->getLoadFactor() << endl;
		output << "Average table accesses:\t" << average_accesses_table << endl;
		output << "Max table accesses:\t" << max_accesses_table << endl;
		output << "Min table accesses:\t" << min_accesses_table << endl;
		output << "Average tree accesses:\t" << average_accesses_tree << endl;
		output << "Max tree accesses:\t" << max_accesses_tree << endl;
		output << "Min tree accesses:\t" << min_accesses_tree << endl;
		output << endl;

		// Clear variables
		start_time = end_time = delta_ms = 0;

		return output;
	}

	void Diagnostic::setTree( c_tree<uint64_t, TaskEntry>* input_tree)
	{
		tree = input_tree;
	}

	void Diagnostic::setTable( HashTable<string, TaskEntry>* input_table)
	{
		table = input_table;
	}
    
    void Diagnostic::testSha1(const int& run_count) const
    {
        string hash;
        string test_entry = "1479442948986\"Implement BST node\"status=\"backlog\"";
        for (int i = 0; i < run_count; ++i) {
            hash = task::sha_1(test_entry);
        }
    }

	void Diagnostic::logStartTime()
	{
		isRunning = true;
		using namespace chrono;
		high_resolution_clock::duration current_time = high_resolution_clock::now().time_since_epoch();
		start_time = duration_cast<milliseconds>(current_time).count();
	}

	void Diagnostic::logEndTime()
	{
		using namespace chrono;
		high_resolution_clock::duration current_time = high_resolution_clock::now().time_since_epoch();
		end_time = duration_cast<milliseconds>(current_time).count();
		isRunning = false;
	}

	void Diagnostic::calculateDelta()
	{
		if (!isRunning) {
			delta_ms = end_time - start_time;
		}
	}

	vector<string> Diagnostic::getAllIds()
	{
		vector<string> ids;
		TaskEntry* value;
		for (uint64_t* key = tree->first_data(&value); key != NULL; key = tree->next_data(&value))
		{
			ids.push_back(value->getId());
		}
		return ids;
	}

	vector<uint64_t> Diagnostic::getAllTimes()
	{
		vector<uint64_t> keys;
		TaskEntry* value;
		for (uint64_t* key = tree->first_data(&value); key != NULL; key = tree->next_data(&value))
		{
			keys.push_back(value->getTimeCreatedMs());
		}
		return keys;
	}

	void Diagnostic::countTableAccess(const int& run_count)
	{
		vector<string> ids = getAllIds();
		TaskEntry* value;
		unsigned int total_accesses = 0;
		unsigned int min_accesses = UINT32_MAX;
		unsigned int max_accesses = 0;
		unsigned int entry_count = table->count();
		int compare_count;
		int random_index;

		srand(time(NULL));
		for (int i = 0; i < run_count; i++) {
			random_index = rand() % ids.size();
			
			compare_count = table->getAccessCountOf(ids[random_index]);
			total_accesses += compare_count;

			min_accesses = min((unsigned int)compare_count, min_accesses);
			max_accesses = max((unsigned int)compare_count, max_accesses);
		}

		average_accesses_table = (double)total_accesses / (double)run_count;
		max_accesses_table = max_accesses;
		min_accesses_table = min_accesses;
	}

	void Diagnostic::countTreeAccess(const int& run_count)
	{
		vector<uint64_t> keys = getAllTimes();
		TaskEntry* value;
		unsigned int total_accesses = 0;
		unsigned int min_accesses = UINT32_MAX;
		unsigned int max_accesses = 0;
		int compare_count;
		bool found;
		int random_index;

		srand(time(NULL));

		for (int i = 0; i < run_count; i++) {
			random_index = rand() % keys.size();
			found = tree->find(keys[random_index], nullptr, nullptr, &compare_count);
			if (!found) { continue; }

			total_accesses += compare_count;
			min_accesses = min((unsigned int)compare_count, min_accesses);
			max_accesses = max((unsigned int)compare_count, max_accesses);
		}

		average_accesses_tree = (double)total_accesses / (double)run_count;
		max_accesses_tree = max_accesses;
		min_accesses_tree = min_accesses;
	}

	double Diagnostic::getAverageTableAccesses() const
	{
		return average_accesses_table;
	}

	double Diagnostic::getAverageTreeAccesses() const
	{
		return average_accesses_tree;
	}
}

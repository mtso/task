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
		logStartTime();

        // Test SHA-1 hash function
		output << "Testing SHA-1 hash " << run_count << " times..." << endl;
		testSha1(run_count);

		// Test table
		output << "Testing HashTable accesses..." << endl;
		countTableAccess();
        
		logEndTime();
		calculateDelta();
        
        // Display time result in ms. Print '<1' if duration is under 1 ms
		output << "Total execution time: ";
		(delta_ms < 1) ? (output << "<1") : (output << delta_ms);
		output << " ms" << endl;
        
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

	void Diagnostic::countTableAccess()
	{
		TaskEntry* value;
		unsigned int total_accesses = 0;
		unsigned int min_accesses = 0;
		unsigned int max_accesses = 0;
		unsigned int entry_count = table->count();
		int current_count;

		for (uint64_t* key = tree->first_data(&value); key != NULL; key = tree->next_data(&value))
		{
			current_count = table->getAccessCountOf(value->getId());
			total_accesses += current_count;

			min_accesses = min((unsigned int)current_count, min_accesses);
			max_accesses = max((unsigned int)current_count, max_accesses);
		}

		average_accesses = (double)total_accesses / (double)entry_count;
	}

	double Diagnostic::getAverageTableAccesses() const
	{
		return average_accesses;
	}
}

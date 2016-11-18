// Diagnostic.cpp
// Task
// CIS 22C F2016: Matthew Tso

#include "Diagnostic.h"

namespace task {

	void Diagnostic::run()
	{
		throw "Diagnostic::run() has not been implemented yet";
	}

	ostream& Diagnostic::runAndPrintTo(ostream& output_stream)
	{
        using namespace std::chrono;
        
        int test_run_count = 10000; // Number of times each test is run

        // Capture start time
        system_clock::duration start_time = system_clock::now().time_since_epoch();
        uint64_t start_time_ms = duration_cast<milliseconds>(start_time).count();
        
        output_stream << "Starting diagnostic routine, please wait..." << endl;
        
        
        // Test SHA-1 hash function
        output_stream << "Testing SHA-1 hash " << test_run_count << " times..." << endl;
        testSha1(test_run_count);
        
        
        // Capture end time
        system_clock::duration end_time = system_clock::now().time_since_epoch();
        uint64_t end_time_ms = duration_cast<milliseconds>(end_time).count();
        
        // Calculate execution time
        uint64_t delta_ms = end_time_ms - start_time_ms;
        
        // Display time result in ms. Print '<1' if duration is under 1 ms
        output_stream << "Total execution time: ";
        (delta_ms < 1) ? (output_stream << "<1") : (output_stream << delta_ms);
        output_stream << " ms" << endl;
        
		return output_stream;
	}
    
    void Diagnostic::testSha1(const int& run_count) const
    {
        string hash;
        string test_entry = "1479442948986\"Implement BST node\"status=\"backlog\"";
        for (int i = 0; i < run_count; ++i) {
            hash = task::sha_1(test_entry);
        }
    }
}

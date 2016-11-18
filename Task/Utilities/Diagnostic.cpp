// Diagnostic.cpp
// Task
// CIS 22C F2016: Matthew Tso

#include "Diagnostic.h"

namespace task {

	Diagnostic::Diagnostic()
	{
		start_time = end_time = delta_ms = 0;
		isRunning = false;
		test_run_count = 100000;
	}

	void Diagnostic::run()
	{
		ostringstream blackhole;
		runAndPrintTo(blackhole);
	}

	ostream& Diagnostic::runAndPrintTo(ostream& output_stream)
	{
        output_stream << "Starting diagnostic routine, please wait..." << endl;
		logStartTime();

        // Test SHA-1 hash function
        output_stream << "Testing SHA-1 hash " << test_run_count << " times..." << endl;
        testSha1(test_run_count);
        
		logEndTime();
		calculateDelta();
        
        // Display time result in ms. Print '<1' if duration is under 1 ms
        output_stream << "Total execution time: ";
        (delta_ms < 1) ? (output_stream << "<1") : (output_stream << delta_ms);
        output_stream << " ms" << endl;
        
		// Clear variables
		start_time = end_time = delta_ms = 0;

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

	void Diagnostic::logStartTime()
	{
		isRunning = true;
		using namespace chrono;
		system_clock::duration current_time = system_clock::now().time_since_epoch();
		start_time = duration_cast<milliseconds>(current_time).count();
	}

	void Diagnostic::logEndTime()
	{
		using namespace chrono;
		system_clock::duration current_time = system_clock::now().time_since_epoch();
		end_time = duration_cast<milliseconds>(current_time).count();
		isRunning = false;
	}

	void Diagnostic::calculateDelta()
	{
		if (!isRunning) {
			delta_ms = end_time - start_time;
		}
	}
}

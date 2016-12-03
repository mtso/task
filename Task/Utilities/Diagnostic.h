// Diagnostic.h
// Task/Utilities
// CIS 22C F2016: Matthew Tso

#ifndef TASK_DIAGNOSTIC_H
#define TASK_DIAGNOSTIC_H

#include <chrono>
#include <iostream>
#include <sstream>
using namespace std;

// Include BST and Hash table headers here
// #include "..\BinarySearchTree.h"
// #include "..\HashTable.h"
#include "Sha1.h"

namespace task {

	/**
	 * Diagnostic is a publicly usable class in the Task library
	 * that tests the efficiency of Task's internals.
	 */
	class Diagnostic
	{
	private:
		uint64_t start_time;
		uint64_t end_time;
		uint64_t delta_ms;

		bool isRunning;

		double speed;
		double bst_efficiency;
		double load_factor;
		int access_count;
        
        void testSha1(const int& run_count) const;

		void logStartTime();
		void logEndTime();
		void calculateDelta();

	public:
		Diagnostic();

		/**
		 * Runs test on the Task library for efficieny.
		 *
		 */
		void run(const int& run_count);

		/**
		 * Run the tests and output each step
		 * to a specified output stream.
		 * Designed to be used like: cout << diagnostic.run(cout) << endl;
		 */
		ostream& runAndPrintTo(const int& run_count, ostream& output_stream);
	};
}

#endif
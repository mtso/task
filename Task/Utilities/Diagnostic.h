// Diagnostic.h
// Task/Utilities
// CIS 22C F2016: Matthew Tso

#ifndef TASK_DIAGNOSTIC_H
#define TASK_DIAGNOSTIC_H

#include <chrono>
#include <iostream>
#include <sstream>
using namespace std;

#include "MinMax.h"

// Include BST and Hash table headers here
#include "..\c_tree.h"
#include "..\HashTable.h"
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

		double load_factor;
		int access_count;

		double average_accesses;

		c_tree<uint64_t, TaskEntry>* tree;
		HashTable<string, TaskEntry>* table;

        void testSha1(const int& run_count) const;

		void logStartTime();
		void logEndTime();
		void calculateDelta();

		void countTableAccess();

	public:
		Diagnostic();

		Diagnostic(c_tree<uint64_t, TaskEntry>* tree_ptr, HashTable<string, TaskEntry>* table_ptr);

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
		ostream& runAndPrintTo(const int& run_count, ostream& output);

		void setTree(c_tree<uint64_t, TaskEntry>* input_tree);

		void setTable(HashTable<string, TaskEntry>* input_table);

		double getAverageTableAccesses() const;
	};
}

#endif
// Diagnostic.h
// Task
// CIS 22C F2016: Matthew Tso

#include <chrono>
#include <iostream>

using namespace std;

// Include BST and Hash table headers here
// #include "BinarySearchTree.h"
// #include "HashTable.h"

namespace task {

	/**
	 * Diagnostic is a publicly usable class in the Task library
	 * that tests the efficiency of Task's internals.
	 */
	class Diagnostic
	{
	private:
		double speed;
		double bst_efficiency;
		double load_factor;
		int access_count;

	public:
		/**
		 * Runs test on the Task library for efficieny.
		 *
		 */
		void run();

		/**
		 * Run the tests and output each step
		 * to a specified output stream.
		 * Designed to be used like: cout << diagnostic.run(cout) << endl;
		 */
		ostream& runAndPrintTo(ostream& output_stream);
	};
}
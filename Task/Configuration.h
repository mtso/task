// Configuration.h
// Task
// CIS 22C F2016: Matthew Tso

// Defines constants used throughout the task library.

#ifndef TASK_CONFIGURATION_H
#define TASK_CONFIGURATION_H

#include <string>
using namespace std;

namespace task {

	static const char* VERSION = "0.1.0";

	// Default file names
	static const char* DEFAULT_DATA_DIR = "..\\.task\\";
	static const char* DEFAULT_TOP_DATA_DIR = ".task\\";

	static const string DEFAULT_TASKLOG_PREFIX = "tasklog-";

	// The character that separates data in tasklog entries
	//const char TASKLOG_DELIMITER = ',';
}

#endif
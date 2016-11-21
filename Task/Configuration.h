// Configuration.h
// Task
// CIS 22C F2016: Matthew Tso

// Defines constants used in task.

#ifndef TASK_CONFIGURATION_H
#define TASK_CONFIGURATION_H

#include <string>
using namespace std;

namespace task {

	// Default file names
	const char* DEFAULT_DATA_DIR = "\\.task";
//#define DEFAULT_DATA_DIR = "..\\.task"; // TODO: Default assumes we are in Debug folder

	const string DEFAULT_TASKLOG_PREFIX = "tasklog-";
}

#endif
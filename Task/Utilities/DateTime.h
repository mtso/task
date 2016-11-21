// DateTime.h
// Task/Utilities
// CIS 22C F2016: Matthew Tso

#ifndef TASK_DATETIME_H
#define TASK_DATETIME_H

#include <chrono>
#include <stdint.h>

namespace task {

	uint64_t weekToMs(const int& weeks);
}

#endif
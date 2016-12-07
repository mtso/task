// DateTime.h
// Task/Utilities
// CIS 22C F2016: Matthew Tso

#ifndef TASK_DATETIME_H
#define TASK_DATETIME_H

#include <chrono>
#include <stdint.h>
#include <string>
using namespace std;

namespace task {

	uint64_t weekToMs(const int& weeks);

	uint64_t dayToMs(const int& days);

	uint64_t hourToMs(const int& hours);

	uint64_t minuteToMs(const int& minutes);

	uint64_t rawDateToMs(const string& raw_input);

	string msToString(const uint64_t& milliseconds);
}

#endif
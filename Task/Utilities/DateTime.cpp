// DateTime.cpp
// Task/Utilities
// CIS 22C F2016: Matthew Tso

#include "DateTime.h"

namespace task {

	uint64_t weekToMs(const int& weeks)
	{
		uint64_t ms_in_week = 604800000;
		return (uint64_t)weeks * ms_in_week;
	}
}
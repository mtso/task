// StringToEnum.cpp
// Task
// CIS 22C F2016: Matthew Tso

#include "StringToEnum.h"

namespace task {

	TaskEntryStatus StringToEnum::forStatus(const string& raw)
	{
		if (raw == "backlog") {
			return BACKLOG;
		}
		else if (raw == "in-progress") {
			return IN_PROGRESS;
		}
		else if (raw == "complete") {
			return COMPLETE;
		}
		else {
			throw "invalid string passed as status";
		}
	}
}
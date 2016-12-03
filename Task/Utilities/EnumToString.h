// EnumToString.h
// Task
// CIS 22C F2016: Matthew Tso

#ifndef TASK_ENUMTOSTRING_H
#define TASK_ENUMTOSTRING_H

#include <string>
using namespace std;

#include "..\\OperationType.h"
#include "..\\TaskEntryStatus.h"
#include "StringConstants.h"

namespace task {
	
	class EnumToString {
	public:

		static string stringForOperationType(const OperationType& type);
		static string stringForStatus(const TaskEntryStatus& status);
	};

}

#endif
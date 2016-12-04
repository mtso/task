// StringToEnum.h
// Task
// CIS 22C F2016: Matthew Tso

#ifndef TASK_STRINGTOENUM_H
#define TASK_STRINGTOENUM_H

#include <string>
using namespace std;

#include "..\\OperationType.h"
#include "..\\TaskEntryStatus.h"
#include "StringConstants.h"

namespace task {

	class StringToEnum {
	public:

		//static string forOperationType(const OperationType& type);
		static TaskEntryStatus forStatus(const string& raw);
	};

}

#endif
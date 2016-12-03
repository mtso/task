// EnumToString.h
// Task
// CIS 22C F2016: Matthew Tso

#include <string>
using namespace std;

#include "..\\OperationType.h"
#include "..\\TaskEntryStatus.h"
#include "StringConstants.h"

namespace task {
	
	string stringForOperationType(const OperationType& type);
	string stringForStatus(const TaskEntryStatus& status);
}
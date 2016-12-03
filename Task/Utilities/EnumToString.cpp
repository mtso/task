// EnumToString.cpp
// Task
// CIS 22C F2016: Matthew Tso

#include "EnumToString.h"

namespace task {

	string EnumToString::forOperationType(const OperationType& type)
	{
		switch (type)
		{
		case OP_CREATE:
			return STRING_CREATE;

		case OP_DELETE:
			return STRING_DELETE;

		case UPDATE_STATUS:
			return STRING_UPDATE_STATUS;

		case UDPATE_DESCRIPTION:
			return STRING_UDPATE_DESCRIPTION;

		case UPDATE_TIMEDUE:
			return STRING_UPDATE_TIMEDUE;

		default:
			throw "Invalid OperationType passed to stringForOperationType()";
		}
	}

	string EnumToString::forStatus(const TaskEntryStatus& status)
	{
		switch (status)
		{
		case BACKLOG:
			return STRING_BACKLOG;

		case IN_PROGRESS:
			return STRING_INPROGRESS;

		case COMPLETE:
			return STRING_COMPLETE;

		default:
			throw "Invalid TaskEntryStatus passed to stringForStatus()";
		}
	}
}
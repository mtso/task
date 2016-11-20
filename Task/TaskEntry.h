// TaskEntry.h
// Task
// CIS 22C F2016:

#include <stdint.h>
#include <string>
using namespace std;

#include "TaskEntryStatus.h"

namespace task
{

	class TaskEntry
	{
	private:
		// 40 hex character id
		string hash;
		uint64_t date_created;
		uint64_t date_due;
		string description;
		TaskEntryStatus status;

	public:
	};
}
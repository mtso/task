

#ifndef TASK_OPERATION_H
#define TASK_OPERATION_H

#include "OperationType.h"
#include "TaskEntry.h"
#include <string>
using namespace std;

namespace task {
	class Operation
	{
	private:
		OperationType type;
		string id;
		TaskEntry previous_state;

	public:
		//Operation(const OperationType& new_type, const string& new_id, const string& new_previous_value);

		Operation(const OperationType& new_type, const TaskEntry& entry);

		OperationType getType() const;
		string getId() const;
		TaskEntry getPreviousState() const;

		bool operator==(const Operation& right) const;
	};
}
#endif
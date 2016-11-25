

#ifndef TASK_OPERATION_H
#define TASK_OPERATION_H

#include "OperationType.h"
#include <string>
using namespace std;

namespace task {
	class Operation
	{
	private:
		OperationType type;
		string id;
		string previous_value;

	public:
		Operation(const OperationType& new_type, const string& new_id, const string& new_previous_value);
		OperationType getType() const;
		string getId() const;
		string getPreviousValue() const;
	};
}
#endif
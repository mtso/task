

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
	public:
		Operation(const OperationType& new_type, const string& new_id);
		OperationType getType() const;
		string getId() const;
	};
}
#endif
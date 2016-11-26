
#include "Operation.h"

namespace task {

	Operation::Operation(const OperationType& new_type, const TaskEntry& entry)
		: type(new_type)
		, previous_state(entry)
		, id(entry.getId())
	{
	}

	OperationType Operation::getType() const
	{
		return type;
	}

	string Operation::getId() const
	{
		return id;
	}

	TaskEntry Operation::getPreviousState() const
	{
		return previous_state;
	}

	bool Operation::operator==(const Operation& right) const
	{
		return id == right.id;
	}
}
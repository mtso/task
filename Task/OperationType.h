
#ifndef TASK_OPERATIONTYPE_H
#define TASK_OPERATIONTYPE_H

namespace task {
	enum OperationType {
		OP_CREATE,
		OP_DELETE,
		UPDATE_STATUS,
		UDPATE_DESCRIPTION,
		UPDATE_TIMEDUE
	};
}

#endif
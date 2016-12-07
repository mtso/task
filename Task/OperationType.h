// OperationType.h
// Task
// CIS 22C F2016: Matthew Tso, Jinzhu Shen
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
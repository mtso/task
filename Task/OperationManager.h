
#ifndef TASK_OPERATIONMANAGER_H
#define TASK_OPERATIONMANAGER_H

#include "Operation.h"
#include "ADT\Stack.h"

namespace task {
	class OperationManager {
	private:
		adt::Stack<Operation> history;

	public:
		void printHistoryTo(ostream& output);

		void recordOperation(const OperationType& type, const string& id);

		void undoOperation();
	};
}

#endif
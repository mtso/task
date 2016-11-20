// Queue.cpp
// Lab 2b: Queue ADT
// CIS 22C F2016: Adrian Marroquin, Matthew Tso

#ifndef ADT_QUEUE_CPP
#define ADT_QUEUE_CPP

#include "Queue.h"

namespace adt {

	T_DATA
	Queue<DataType>::~Queue()
	{
	}

	T_DATA
	bool Queue<DataType>::isEmpty()
	{
		return List<DataType>::isEmpty();
	}

	T_DATA
	int Queue<DataType>::getLength()
	{
		return List<DataType>::getLength();
	}

	T_DATA
	bool Queue<DataType>::enqueue(const DataType& item)
	{
		return addLast(item);
	}

	T_DATA
	DataType Queue<DataType>::dequeue()
	{
		DataType returnItem = head->getData();
		List<DataType>::removeFirst();
		return returnItem;
	}
}

#endif
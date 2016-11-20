// Stack.cpp
// Lab 2: Stack ADT
// CIS 22C F2016: Adrian Marroquin, Matthew Tso

#ifndef ADT_STACK_CPP
#define ADT_STACK_CPP

#include "Stack.h"

namespace adt {

	template <typename DataType>
	Stack<DataType>::~Stack()
	{
		// Do we need to explicitly call?
	}

	template <typename DataType>
	bool Stack<DataType>::isEmpty() const
	{
		// Return superclass's isEmpty function.
		return List<DataType>::isEmpty();
	}

	template <typename DataType>
	int Stack<DataType>::getLength() const
	{
		// Return superclass's getLength function.
		return List<DataType>::getLength();
	}

	template <typename DataType>
	void Stack<DataType>::clear()
	{
		List<DataType>::clear();
	}

	template <typename DataType>
	bool Stack<DataType>::push(const DataType& item)
	{
		return addFirst(item);
	}

	template <typename DataType>
	DataType Stack<DataType>::pop()
	{
		DataType value = head->getData();
		List<DataType>::removeFirst();
		return value;
	}

	template <typename DataType>
	DataType Stack<DataType>::peek()
	{
		return head->getData();
	}
}
#endif